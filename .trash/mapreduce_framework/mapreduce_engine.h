#pragma once

#include "interfaces.h"
#include <iostream>
#include <vector>
#include <string>
#include <thread>
#include <mutex>
#include <memory>
#include <unordered_map>
#include <queue>
#include <condition_variable>
#include <functional>
#include <chrono>
#include <atomic>
#include <algorithm>

namespace MapReduceFramework {

    class MapReduceEngine {
    private:
        struct WorkItem {
            MapInput data;
            int item_id;
            
            WorkItem() = default;
            WorkItem(const MapInput& d, int id) : data(d), item_id(id) {}
        };
        
        struct ReducerBucket {
            std::unordered_map<MapKey, std::vector<MapValue>> data;
            std::mutex bucket_mutex;
        };
        
        // Configuration
        MapReduceConfig config;
        
        // User-defined processing components
        std::unique_ptr<IMapper> mapper;
        std::unique_ptr<IReducer> reducer;
        std::unique_ptr<IResultHandler> result_handler;
        
        // Thread-safe data structures
        std::queue<WorkItem> work_queue;
        std::mutex work_queue_mutex;
        std::condition_variable work_available;
        std::atomic<bool> no_more_work{false};
        std::atomic<int> active_mappers{0};
        
        std::vector<std::unique_ptr<ReducerBucket>> reducer_buckets;
        std::unordered_map<ReduceKey, ReduceValue> final_results;
        std::mutex final_results_mutex;
        
        // Statistics
        std::atomic<size_t> items_processed{0};
        std::atomic<size_t> pairs_generated{0};
        
        // Hash function for distributing keys to reducers
        size_t hash_key(const MapKey& key) const {
            std::hash<MapKey> hasher;
            return hasher(key) % config.num_reducers;
        }
        
        // Mapper worker thread with improved synchronization
        void mapper_worker(int mapper_id) {
            if (config.verbose) {
                std::cout << "[Mapper " << mapper_id << "] Started\n";
            }
            
            active_mappers++;
            
            while (true) {
                WorkItem work_item;
                bool got_work = false;
                
                // Get next work item from queue
                {
                    std::unique_lock<std::mutex> lock(work_queue_mutex);
                    
                    // Wait for work or completion signal
                    work_available.wait(lock, [this] { 
                        return !work_queue.empty() || no_more_work; 
                    });
                    
                    if (!work_queue.empty()) {
                        work_item = work_queue.front();
                        work_queue.pop();
                        got_work = true;
                    } else if (no_more_work) {
                        break;
                    }
                }
                
                if (!got_work) continue;
                
                if (config.verbose) {
                    std::cout << "[Mapper " << mapper_id << "] Processing item " 
                              << work_item.item_id << "\n";
                }
                
                try {
                    // Apply mapper function
                    auto map_results = mapper->map(work_item.data);
                    pairs_generated += map_results.size();
                    
                    // Distribute results to reducer buckets based on hash
                    for (const auto& result : map_results) {
                        size_t bucket_index = hash_key(result.key);
                        std::lock_guard<std::mutex> lock(reducer_buckets[bucket_index]->bucket_mutex);
                        reducer_buckets[bucket_index]->data[result.key].push_back(result.value);
                    }
                    
                    items_processed++;
                    
                } catch (const std::exception& e) {
                    std::cerr << "[Mapper " << mapper_id << "] Error processing item " 
                              << work_item.item_id << ": " << e.what() << "\n";
                }
            }
            
            active_mappers--;
            if (config.verbose) {
                std::cout << "[Mapper " << mapper_id << "] Finished\n";
            }
        }
        
        // Reducer worker thread
        void reducer_worker(int reducer_id) {
            if (config.verbose) {
                std::cout << "[Reducer " << reducer_id << "] Started\n";
            }
            
            // Process results in this reducer's bucket
            std::unordered_map<ReduceKey, ReduceValue> local_results;
            
            try {
                std::lock_guard<std::mutex> lock(reducer_buckets[reducer_id]->bucket_mutex);
                for (const auto& pair : reducer_buckets[reducer_id]->data) {
                    auto reduced = reducer->reduce(pair.first, pair.second);
                    local_results[reduced.key] = reduced.value;
                }
            } catch (const std::exception& e) {
                std::cerr << "[Reducer " << reducer_id << "] Error: " << e.what() << "\n";
                return;
            }
            
            // Merge with final results
            {
                std::lock_guard<std::mutex> lock(final_results_mutex);
                for (const auto& pair : local_results) {
                    final_results[pair.first] = pair.second;
                }
            }
            
            if (config.verbose) {
                std::cout << "[Reducer " << reducer_id << "] Finished (processed " 
                          << local_results.size() << " keys)\n";
            }
        }

    public:
        MapReduceEngine(const MapReduceConfig& cfg = MapReduceConfig()) : config(cfg) {
            reducer_buckets.resize(config.num_reducers);
            for (int i = 0; i < config.num_reducers; ++i) {
                reducer_buckets[i] = std::make_unique<ReducerBucket>();
            }
        }
        
        // Set the mapper implementation
        void set_mapper(std::unique_ptr<IMapper> m) {
            mapper = std::move(m);
        }
        
        // Set the reducer implementation
        void set_reducer(std::unique_ptr<IReducer> r) {
            reducer = std::move(r);
        }
        
        // Set custom result handler
        void set_result_handler(std::unique_ptr<IResultHandler> handler) {
            result_handler = std::move(handler);
        }
        
        // Execute MapReduce on input data with pipeline processing
        void execute(const std::vector<MapInput>& input_data) {
            if (!mapper || !reducer) {
                throw std::runtime_error("Mapper and Reducer must be set before execution");
            }
            
            auto start_time = std::chrono::high_resolution_clock::now();
            
            // Reset state for new execution
            reset_state();
            
            if (config.verbose) {
                std::cout << "\n=== MAPREDUCE EXECUTION STARTED ===\n";
                std::cout << "Mapper: " << mapper->get_description() << "\n";
                std::cout << "Reducer: " << reducer->get_description() << "\n";
                std::cout << "Configuration: " << config.num_mappers << " mappers, " 
                          << config.num_reducers << " reducers\n";
                std::cout << "Input items: " << input_data.size() << "\n\n";
            }
            
            // Fill work queue
            for (size_t i = 0; i < input_data.size(); ++i) {
                work_queue.push(WorkItem(input_data[i], static_cast<int>(i)));
            }
            
            // Start mapper threads
            std::vector<std::thread> mapper_threads;
            for (int i = 0; i < config.num_mappers; ++i) {
                mapper_threads.emplace_back(&MapReduceEngine::mapper_worker, this, i);
            }
            
            // Signal no more work will be added and notify all mappers
            no_more_work = true;
            work_available.notify_all();
            
            // Wait for all mappers to finish
            for (auto& thread : mapper_threads) {
                thread.join();
            }
            
            if (config.verbose) {
                std::cout << "\n[Pipeline] Map phase completed. Starting reduce phase...\n";
            }
            
            // Start reducer threads after mappers finish
            std::vector<std::thread> reducer_threads;
            for (int i = 0; i < config.num_reducers; ++i) {
                reducer_threads.emplace_back(&MapReduceEngine::reducer_worker, this, i);
            }
            
            // Wait for all reducers to finish
            for (auto& thread : reducer_threads) {
                thread.join();
            }
            
            auto end_time = std::chrono::high_resolution_clock::now();
            auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time);
            
            // Print execution statistics
            if (config.verbose) {
                std::cout << "\n=== EXECUTION COMPLETED ===\n";
                std::cout << "Total execution time: " << duration.count() << " ms\n";
                std::cout << "Items processed: " << items_processed.load() << "\n";
                std::cout << "Key-value pairs generated: " << pairs_generated.load() << "\n";
                std::cout << "Final results: " << final_results.size() << " unique keys\n";
            }
            
            // Handle output using custom handler or default
            if (result_handler) {
                result_handler->handle_results(final_results, config);
            } else {
                print_default_results();
            }
        }
        
        // Get results for programmatic use
        const std::unordered_map<ReduceKey, ReduceValue>& get_results() const {
            return final_results;
        }
        
        // Update configuration
        void update_config(const MapReduceConfig& new_config) {
            config = new_config;
            // Resize reducer buckets if needed
            if (reducer_buckets.size() != static_cast<size_t>(config.num_reducers)) {
                reducer_buckets.clear();
                reducer_buckets.resize(config.num_reducers);
                for (int i = 0; i < config.num_reducers; ++i) {
                    reducer_buckets[i] = std::make_unique<ReducerBucket>();
                }
            }
        }

    private:
        void reset_state() {
            no_more_work = false;
            active_mappers = 0;
            items_processed = 0;
            pairs_generated = 0;
            final_results.clear();
            
            // Clear work queue
            std::queue<WorkItem> empty_queue;
            work_queue.swap(empty_queue);
            
            // Clear reducer buckets
            for (auto& bucket : reducer_buckets) {
                std::lock_guard<std::mutex> lock(bucket->bucket_mutex);
                bucket->data.clear();
            }
        }
        
        void print_default_results() {
            std::cout << "\n=== MAPREDUCE RESULTS ===\n";
            std::cout << "Total unique keys: " << final_results.size() << "\n\n";
            
            // Sort results by key for consistent output
            std::vector<std::pair<ReduceKey, ReduceValue>> sorted_results(
                final_results.begin(), final_results.end());
            std::sort(sorted_results.begin(), sorted_results.end());
            
            for (const auto& pair : sorted_results) {
                std::cout << "'" << pair.first << "' -> '" << pair.second << "'\n";
            }
        }
    };

} // namespace MapReduceFramework
