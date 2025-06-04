#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <thread>
#include <mutex>
#include <queue>
#include <unordered_map>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <condition_variable>
#include <filesystem>
#include <chrono>
#include <atomic>
#include <cstdlib>
#include <memory>

namespace MapReduceFramework {

    // Configuration for MapReduce execution
    struct Config {
        int num_mappers = 4;
        int num_reducers = 2;
        std::string mapper_executable;
        std::string reducer_executable;
        std::string input_dir;
        std::string output_dir = "output";
        std::string intermediate_dir = "intermediate";
        bool verbose = true;
        
        // Memory management settings for large datasets
        size_t max_chunk_size = 1000000;  // Lines per chunk for external sorting
        size_t max_memory_mb = 1024;      // Maximum memory usage in MB
        bool use_streaming = true;        // Enable streaming for large datasets
        
        Config() = default;
        Config(const std::string& mapper_exec, const std::string& reducer_exec, 
               const std::string& input_directory, int mappers = 4, int reducers = 2)
            : num_mappers(mappers), num_reducers(reducers), 
              mapper_executable(mapper_exec), reducer_executable(reducer_exec),
              input_dir(input_directory) {}
    };

    // Work item for mapper threads
    struct MapperTask {
        std::string input_file;
        int task_id;
        std::string output_file;
    };

    // Work item for reducer threads
    struct ReducerTask {
        std::vector<std::string> input_files;
        int task_id;
        std::string output_file;
    };

    class MapReduceEngine {
    private:
        Config config;
        
        // Thread synchronization
        std::queue<MapperTask> mapper_queue;
        std::queue<ReducerTask> reducer_queue;
        std::mutex mapper_queue_mutex;
        std::mutex reducer_queue_mutex;
        std::condition_variable mapper_cv;
        std::condition_variable reducer_cv;
        std::atomic<bool> mappers_done{false};
        std::atomic<bool> reducers_done{false};
        std::atomic<int> active_mappers{0};
        std::atomic<int> active_reducers{0};

        // File management
        std::vector<std::string> input_files;
        std::vector<std::vector<std::string>> reducer_input_files;

        void log(const std::string& message) {
            if (config.verbose) {
                std::cout << "[MapReduce] " << message << std::endl;
            }
        }

        void setup_directories() {
            std::filesystem::create_directories(config.output_dir);
            std::filesystem::create_directories(config.intermediate_dir);
            
            // Clean intermediate directory
            for (const auto& entry : std::filesystem::directory_iterator(config.intermediate_dir)) {
                std::filesystem::remove(entry.path());
            }
        }

        void discover_input_files() {
            input_files.clear();
            
            if (std::filesystem::is_directory(config.input_dir)) {
                for (const auto& entry : std::filesystem::directory_iterator(config.input_dir)) {
                    if (entry.is_regular_file()) {
                        input_files.push_back(entry.path().string());
                    }
                }
            } else if (std::filesystem::is_regular_file(config.input_dir)) {
                input_files.push_back(config.input_dir);
            }
            
            std::sort(input_files.begin(), input_files.end());
            log("Found " + std::to_string(input_files.size()) + " input files");
        }

        void mapper_worker(int mapper_id) {
            log("Mapper " + std::to_string(mapper_id) + " started");
            active_mappers++;
            
            while (true) {
                MapperTask task;
                bool got_task = false;
                
                {
                    std::unique_lock<std::mutex> lock(mapper_queue_mutex);
                    mapper_cv.wait(lock, [this] { return !mapper_queue.empty() || mappers_done; });
                    
                    if (!mapper_queue.empty()) {
                        task = mapper_queue.front();
                        mapper_queue.pop();
                        got_task = true;
                    } else if (mappers_done) {
                        break;
                    }
                }
                
                if (got_task) {
                    execute_mapper(task, mapper_id);
                }
            }
            
            active_mappers--;
            log("Mapper " + std::to_string(mapper_id) + " finished");
        }

        void reducer_worker(int reducer_id) {
            log("Reducer " + std::to_string(reducer_id) + " started");
            active_reducers++;
            
            while (true) {
                ReducerTask task;
                bool got_task = false;
                
                {
                    std::unique_lock<std::mutex> lock(reducer_queue_mutex);
                    reducer_cv.wait(lock, [this] { return !reducer_queue.empty() || reducers_done; });
                    
                    if (!reducer_queue.empty()) {
                        task = reducer_queue.front();
                        reducer_queue.pop();
                        got_task = true;
                    } else if (reducers_done) {
                        break;
                    }
                }
                
                if (got_task) {
                    execute_reducer(task, reducer_id);
                }
            }
            
            active_reducers--;
            log("Reducer " + std::to_string(reducer_id) + " finished");
        }

        void execute_mapper(const MapperTask& task, int mapper_id) {
            log("Mapper " + std::to_string(mapper_id) + " processing: " + task.input_file);
            
            // Build command: mapper_executable < input_file > output_file
            std::string command = config.mapper_executable + " < \"" + task.input_file + "\" > \"" + task.output_file + "\"";
            
            int result = std::system(command.c_str());
            if (result != 0) {
                std::cerr << "Mapper " << mapper_id << " failed with exit code: " << result << std::endl;
            }
        }

        void execute_reducer(const ReducerTask& task, int reducer_id) {
            log("Reducer " + std::to_string(reducer_id) + " processing " + std::to_string(task.input_files.size()) + " files");
            
            // Merge all intermediate files for this reducer and sort
            std::string merged_file = config.intermediate_dir + "/merged_" + std::to_string(task.task_id) + ".txt";
            merge_and_sort_files(task.input_files, merged_file);
            
            // Build command: reducer_executable < merged_file > output_file
            std::string command = config.reducer_executable + " < \"" + merged_file + "\" > \"" + task.output_file + "\"";
            
            int result = std::system(command.c_str());
            if (result != 0) {
                std::cerr << "Reducer " << reducer_id << " failed with exit code: " << result << std::endl;
            }
            
            // Clean up merged file
            std::filesystem::remove(merged_file);
        }

        void merge_and_sort_files(const std::vector<std::string>& files, const std::string& output_file) {
            // Memory-efficient external merge sort for large datasets
            if (files.empty()) return;
            
            // First, sort each file individually if they're not already sorted
            std::vector<std::string> sorted_temp_files;
            for (size_t i = 0; i < files.size(); ++i) {
                std::string temp_sorted = config.intermediate_dir + "/temp_sorted_" + std::to_string(i) + ".txt";
                external_sort_file(files[i], temp_sorted);
                sorted_temp_files.push_back(temp_sorted);
            }
            
            // Then merge sorted files using k-way merge with minimal memory
            k_way_merge_files(sorted_temp_files, output_file);
            
            // Clean up temporary sorted files
            for (const auto& temp_file : sorted_temp_files) {
                std::filesystem::remove(temp_file);
            }
        }

        void external_sort_file(const std::string& input_file, const std::string& output_file) {
            const size_t CHUNK_SIZE = 1000000; // 1M lines per chunk - configurable based on available RAM
            std::vector<std::string> temp_chunk_files;
            
            std::ifstream infile(input_file);
            std::string line;
            std::vector<std::string> chunk;
            chunk.reserve(CHUNK_SIZE);
            
            int chunk_count = 0;
            
            // Read file in chunks, sort each chunk, and write to temp files
            while (std::getline(infile, line)) {
                if (!line.empty()) {
                    chunk.push_back(line);
                    
                    if (chunk.size() >= CHUNK_SIZE) {
                        // Sort this chunk and write to temp file
                        std::sort(chunk.begin(), chunk.end());
                        std::string chunk_file = config.intermediate_dir + "/chunk_" + std::to_string(chunk_count++) + ".txt";
                        
                        std::ofstream chunk_out(chunk_file);
                        for (const auto& chunk_line : chunk) {
                            chunk_out << chunk_line << '\n';
                        }
                        chunk_out.close();
                        temp_chunk_files.push_back(chunk_file);
                        
                        chunk.clear();
                        chunk.reserve(CHUNK_SIZE);
                    }
                }
            }
            
            // Handle remaining lines in the last chunk
            if (!chunk.empty()) {
                std::sort(chunk.begin(), chunk.end());
                std::string chunk_file = config.intermediate_dir + "/chunk_" + std::to_string(chunk_count++) + ".txt";
                
                std::ofstream chunk_out(chunk_file);
                for (const auto& chunk_line : chunk) {
                    chunk_out << chunk_line << '\n';
                }
                chunk_out.close();
                temp_chunk_files.push_back(chunk_file);
            }
            
            infile.close();
            
            // Merge sorted chunks
            if (temp_chunk_files.size() == 1) {
                // Only one chunk, just rename it
                std::filesystem::rename(temp_chunk_files[0], output_file);
            } else {
                // Merge multiple chunks
                k_way_merge_files(temp_chunk_files, output_file);
                
                // Clean up chunk files
                for (const auto& chunk_file : temp_chunk_files) {
                    std::filesystem::remove(chunk_file);
                }
            }
        }

        void k_way_merge_files(const std::vector<std::string>& sorted_files, const std::string& output_file) {
            if (sorted_files.empty()) return;
            
            if (sorted_files.size() == 1) {
                // Only one file, just copy it
                std::filesystem::copy_file(sorted_files[0], output_file);
                return;
            }
            
            // Priority queue for k-way merge
            struct FileLineEntry {
                std::string line;
                int file_index;
                std::ifstream* file_stream;
                
                bool operator>(const FileLineEntry& other) const {
                    return line > other.line; // Min-heap based on line content
                }
            };
            
            std::priority_queue<FileLineEntry, std::vector<FileLineEntry>, std::greater<FileLineEntry>> pq;
            std::vector<std::unique_ptr<std::ifstream>> file_streams;
            
            // Open all files and read first line from each
            for (size_t i = 0; i < sorted_files.size(); ++i) {
                auto file_stream = std::make_unique<std::ifstream>(sorted_files[i]);
                if (file_stream->is_open()) {
                    std::string line;
                    if (std::getline(*file_stream, line) && !line.empty()) {
                        pq.push({line, static_cast<int>(i), file_stream.get()});
                    }
                    file_streams.push_back(std::move(file_stream));
                }
            }
            
            // Merge using priority queue
            std::ofstream outfile(output_file);
            while (!pq.empty()) {
                FileLineEntry entry = pq.top();
                pq.pop();
                
                outfile << entry.line << '\n';
                
                // Read next line from the same file
                std::string next_line;
                if (std::getline(*entry.file_stream, next_line) && !next_line.empty()) {
                    pq.push({next_line, entry.file_index, entry.file_stream});
                }
            }
            
            outfile.close();
        }

        void partition_mapper_outputs() {
            // Initialize reducer input files structure
            reducer_input_files.resize(config.num_reducers);
            
            // Collect all mapper output files
            std::vector<std::string> mapper_outputs;
            for (const auto& entry : std::filesystem::directory_iterator(config.intermediate_dir)) {
                if (entry.path().filename().string().find("mapper_") == 0) {
                    mapper_outputs.push_back(entry.path().string());
                }
            }
            
            // Partition based on key hash - read each mapper output and distribute lines
            for (const auto& mapper_file : mapper_outputs) {
                std::ifstream infile(mapper_file);
                std::string line;
                
                // Create temporary files for each reducer
                std::vector<std::ofstream> reducer_files(config.num_reducers);
                for (int i = 0; i < config.num_reducers; ++i) {
                    std::string partition_file = config.intermediate_dir + "/partition_" + 
                                               std::to_string(i) + "_" + 
                                               std::filesystem::path(mapper_file).filename().string();
                    reducer_files[i].open(partition_file);
                    reducer_input_files[i].push_back(partition_file);
                }
                
                while (std::getline(infile, line)) {
                    if (!line.empty()) {
                        // Extract key for partitioning (assumes key is first word)
                        std::string key = line.substr(0, line.find('\t'));
                        if (key.empty()) key = line.substr(0, line.find(' '));
                        
                        // Hash key to determine reducer
                        std::hash<std::string> hasher;
                        int reducer_id = hasher(key) % config.num_reducers;
                        
                        reducer_files[reducer_id] << line << '\n';
                    }
                }
            }
            
            log("Partitioned mapper outputs for " + std::to_string(config.num_reducers) + " reducers");
        }

    public:
        MapReduceEngine(const Config& cfg) : config(cfg) {
            if (config.mapper_executable.empty() || config.reducer_executable.empty()) {
                throw std::runtime_error("Mapper and reducer executables must be specified");
            }
        }

        void execute() {
            auto start_time = std::chrono::high_resolution_clock::now();
            
            log("Starting MapReduce execution");
            log("Mappers: " + std::to_string(config.num_mappers) + 
                ", Reducers: " + std::to_string(config.num_reducers));
            log("Mapper executable: " + config.mapper_executable);
            log("Reducer executable: " + config.reducer_executable);
            
            // Setup
            setup_directories();
            discover_input_files();
            
            if (input_files.empty()) {
                throw std::runtime_error("No input files found in: " + config.input_dir);
            }
            
            // Phase 1: Map
            log("=== MAP PHASE ===");
            run_map_phase();
            
            // Phase 2: Shuffle/Partition
            log("=== SHUFFLE PHASE ===");
            partition_mapper_outputs();
            
            // Phase 3: Reduce
            log("=== REDUCE PHASE ===");
            run_reduce_phase();
            
            auto end_time = std::chrono::high_resolution_clock::now();
            auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time);
            
            log("MapReduce completed in " + std::to_string(duration.count()) + " ms");
            log("Output files in: " + config.output_dir);
        }

        void run_map_phase() {
            // Create mapper tasks
            for (size_t i = 0; i < input_files.size(); ++i) {
                MapperTask task;
                task.input_file = input_files[i];
                task.task_id = i;
                task.output_file = config.intermediate_dir + "/mapper_" + std::to_string(i) + ".txt";
                mapper_queue.push(task);
            }
            
            // Start mapper threads
            std::vector<std::thread> mapper_threads;
            for (int i = 0; i < config.num_mappers; ++i) {
                mapper_threads.emplace_back(&MapReduceEngine::mapper_worker, this, i);
            }
            
            // Signal no more tasks
            mappers_done = true;
            mapper_cv.notify_all();
            
            // Wait for completion
            for (auto& thread : mapper_threads) {
                thread.join();
            }
            
            log("Map phase completed");
        }

        void run_reduce_phase() {
            // Create reducer tasks
            for (int i = 0; i < config.num_reducers; ++i) {
                ReducerTask task;
                task.input_files = reducer_input_files[i];
                task.task_id = i;
                task.output_file = config.output_dir + "/part-" + std::to_string(i) + ".txt";
                reducer_queue.push(task);
            }
            
            // Start reducer threads
            std::vector<std::thread> reducer_threads;
            for (int i = 0; i < config.num_reducers; ++i) {
                reducer_threads.emplace_back(&MapReduceEngine::reducer_worker, this, i);
            }
            
            // Signal no more tasks
            reducers_done = true;
            reducer_cv.notify_all();
            
            // Wait for completion
            for (auto& thread : reducer_threads) {
                thread.join();
            }
            
            log("Reduce phase completed");
        }

        void merge_final_output(const std::string& final_output_file = "final_output.txt") {
            std::ofstream final_file(config.output_dir + "/" + final_output_file);
            
            for (int i = 0; i < config.num_reducers; ++i) {
                std::string part_file = config.output_dir + "/part-" + std::to_string(i) + ".txt";
                std::ifstream part(part_file);
                std::string line;
                
                while (std::getline(part, line)) {
                    final_file << line << '\n';
                }
            }
            
            log("Final output merged into: " + config.output_dir + "/" + final_output_file);
        }
    };

} // namespace MapReduceFramework
