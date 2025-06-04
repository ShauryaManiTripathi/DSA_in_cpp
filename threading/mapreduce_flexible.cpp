#include <iostream>
#include <vector>
#include <string>
#include <thread>
#include <mutex>
#include <memory>
#include <unordered_map>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <queue>
#include <condition_variable>
#include <filesystem>
#include <functional>
#include <chrono>
#include <atomic>

// Key-Value pair for MapReduce operations
template<typename K, typename V>
struct KeyValue {
    K key;
    V value;
    KeyValue(const K& k, const V& v) : key(k), value(v) {}
};

// Flexible MapReduce Framework
template<typename InputType, typename MapKey, typename MapValue, typename ReduceKey, typename ReduceValue>
class FlexibleMapReduce {
public:
    using MapperFunction = std::function<std::vector<KeyValue<MapKey, MapValue>>(const InputType&)>;
    using ReducerFunction = std::function<KeyValue<ReduceKey, ReduceValue>(const MapKey&, const std::vector<MapValue>&)>;
    using OutputFunction = std::function<void(const std::unordered_map<ReduceKey, ReduceValue>&, const std::string&)>;

private:
    struct WorkItem {
        InputType data;
        int item_id;
    };
    
    struct ReducerBucket {
        std::unordered_map<MapKey, std::vector<MapValue>> data;
        std::mutex bucket_mutex;
    };
    
    int num_mappers;
    int num_reducers;
    
    // Thread-safe queues and data structures
    std::queue<WorkItem> work_queue;
    std::mutex work_queue_mutex;
    std::atomic<bool> no_more_work{false};
    
    std::vector<std::unique_ptr<ReducerBucket>> reducer_buckets;
    std::unordered_map<ReduceKey, ReduceValue> final_results;
    std::mutex final_results_mutex;
    
    // User-defined functions
    MapperFunction mapper_func;
    ReducerFunction reducer_func;
    OutputFunction output_func;
    
    // Hash function for distributing keys to reducers
    size_t hash_key(const MapKey& key) const {
        std::hash<MapKey> hasher;
        return hasher(key) % num_reducers;
    }
    
    // Mapper worker thread
    void mapper_worker(int mapper_id) {
        std::cout << "Mapper " << mapper_id << " started\n";
        
        while (true) {
            WorkItem work_item;
            bool got_work = false;
            
            // Get next work item from queue
            {
                std::unique_lock<std::mutex> lock(work_queue_mutex);
                if (!work_queue.empty()) {
                    work_item = work_queue.front();
                    work_queue.pop();
                    got_work = true;
                } else if (no_more_work) {
                    break;
                }
            }
            
            if (!got_work) {
                std::this_thread::sleep_for(std::chrono::milliseconds(1));
                continue;
            }
            
            std::cout << "Mapper " << mapper_id << " processing item " << work_item.item_id << "\n";
            
            // Apply mapper function
            auto map_results = mapper_func(work_item.data);
            
            // Distribute results to reducer buckets based on hash
            for (const auto& result : map_results) {
                size_t bucket_index = hash_key(result.key);
                std::lock_guard<std::mutex> lock(reducer_buckets[bucket_index]->bucket_mutex);
                reducer_buckets[bucket_index]->data[result.key].push_back(result.value);
            }
        }
        
        std::cout << "Mapper " << mapper_id << " finished\n";
    }
    
    // Reducer worker thread
    void reducer_worker(int reducer_id) {
        std::cout << "Reducer " << reducer_id << " started\n";
        
        // Process results in this reducer's bucket
        std::unordered_map<ReduceKey, ReduceValue> local_results;
        
        {
            std::lock_guard<std::mutex> lock(reducer_buckets[reducer_id]->bucket_mutex);
            for (const auto& pair : reducer_buckets[reducer_id]->data) {
                auto reduced = reducer_func(pair.first, pair.second);
                local_results[reduced.key] = reduced.value;
            }
        }
        
        // Merge with final results
        {
            std::lock_guard<std::mutex> lock(final_results_mutex);
            for (const auto& pair : local_results) {
                final_results[pair.first] = pair.second;
            }
        }
        
        std::cout << "Reducer " << reducer_id << " finished\n";
    }

public:
    FlexibleMapReduce(int mappers = 4, int reducers = 2) 
        : num_mappers(mappers), num_reducers(reducers) {
        reducer_buckets.resize(num_reducers);
        for (int i = 0; i < num_reducers; ++i) {
            reducer_buckets[i] = std::make_unique<ReducerBucket>();
        }
    }
    
    // Set custom mapper function
    void set_mapper(MapperFunction mapper) {
        mapper_func = mapper;
    }
    
    // Set custom reducer function
    void set_reducer(ReducerFunction reducer) {
        reducer_func = reducer;
    }
    
    // Set custom output function
    void set_output_handler(OutputFunction output) {
        output_func = output;
    }
    
    // Execute MapReduce on input data
    void execute(const std::vector<InputType>& input_data, const std::string& output_file = "") {
        auto start_time = std::chrono::high_resolution_clock::now();
        
        // Reset state for new execution
        no_more_work = false;
        final_results.clear();
        for (auto& bucket : reducer_buckets) {
            bucket->data.clear();
        }
        
        std::cout << "Starting MapReduce execution\n";
        std::cout << "Mappers: " << num_mappers << ", Reducers: " << num_reducers << "\n";
        std::cout << "Input items: " << input_data.size() << "\n";
        
        // Fill work queue
        for (size_t i = 0; i < input_data.size(); ++i) {
            work_queue.push({input_data[i], static_cast<int>(i)});
        }
        
        // Signal no more work will be added
        no_more_work = true;
        
        // Start mapper threads
        std::vector<std::thread> mapper_threads;
        for (int i = 0; i < num_mappers; ++i) {
            mapper_threads.emplace_back(&FlexibleMapReduce::mapper_worker, this, i);
        }
        
        // Wait for all mappers to finish
        for (auto& thread : mapper_threads) {
            thread.join();
        }
        
        // Start reducer threads after mappers finish
        std::vector<std::thread> reducer_threads;
        for (int i = 0; i < num_reducers; ++i) {
            reducer_threads.emplace_back(&FlexibleMapReduce::reducer_worker, this, i);
        }
        
        // Wait for all reducers to finish
        for (auto& thread : reducer_threads) {
            thread.join();
        }
        
        auto end_time = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time);
        
        std::cout << "MapReduce completed in " << duration.count() << " ms\n";
        
        // Handle output
        if (output_func) {
            output_func(final_results, output_file);
        } else {
            print_default_results();
        }
    }
    
    // Default result printer
    void print_default_results() {
        std::cout << "\n=== MAPREDUCE RESULTS ===\n";
        std::cout << "Total results: " << final_results.size() << "\n\n";
        
        for (const auto& pair : final_results) {
            std::cout << "Key: " << pair.first << " -> Value: " << pair.second << "\n";
        }
    }
    
    // Get results for programmatic use
    const std::unordered_map<ReduceKey, ReduceValue>& get_results() const {
        return final_results;
    }
};

// Specialized Pattern Search using the flexible framework
class PatternSearchMapReduce {
private:
    std::string pattern;
    FlexibleMapReduce<std::string, std::string, int, std::string, int> mapreduce;

public:
    PatternSearchMapReduce(const std::string& search_pattern, int mappers = 4, int reducers = 2) 
        : pattern(search_pattern), mapreduce(mappers, reducers) {
        setup_functions();
    }
    
    void setup_functions() {
        // Custom mapper: extracts words matching pattern from text lines
        mapreduce.set_mapper([this](const std::string& line) -> std::vector<KeyValue<std::string, int>> {
            std::vector<KeyValue<std::string, int>> results;
            std::istringstream iss(line);
            std::string word;
            
            while (iss >> word) {
                // Remove punctuation
                word.erase(std::remove_if(word.begin(), word.end(), [](char c) {
                    return std::ispunct(c);
                }), word.end());
                
                if (!word.empty() && contains_pattern(word, pattern)) {
                    results.emplace_back(word, 1);
                }
            }
            return results;
        });
        
        // Custom reducer: sums up word frequencies
        mapreduce.set_reducer([](const std::string& word, const std::vector<int>& counts) -> KeyValue<std::string, int> {
            int total_count = 0;
            for (int count : counts) {
                total_count += count;
            }
            return KeyValue<std::string, int>(word, total_count);
        });
        
        // Custom output handler: saves results to file and prints summary
        mapreduce.set_output_handler([](const std::unordered_map<std::string, int>& results, const std::string& output_file) {
            std::cout << "\n=== PATTERN SEARCH RESULTS ===\n";
            std::cout << "Words found: " << results.size() << "\n";
            
            // Sort results by frequency (descending)
            std::vector<std::pair<std::string, int>> sorted_results(results.begin(), results.end());
            std::sort(sorted_results.begin(), sorted_results.end(), 
                     [](const auto& a, const auto& b) { return a.second > b.second; });
            
            // Print to console
            for (const auto& pair : sorted_results) {
                std::cout << "'" << pair.first << "': " << pair.second << " times\n";
            }
            
            // Save to file if specified
            if (!output_file.empty()) {
                std::ofstream file(output_file);
                if (file.is_open()) {
                    file << "# Pattern Search Results\n";
                    file << "# Total unique words: " << results.size() << "\n";
                    file << "# Word : Frequency\n\n";
                    
                    for (const auto& pair : sorted_results) {
                        file << pair.first << " : " << pair.second << "\n";
                    }
                    file.close();
                    std::cout << "\nResults saved to: " << output_file << "\n";
                } else {
                    std::cerr << "Error: Could not open output file: " << output_file << "\n";
                }
            }
        });
    }
    
    void search_files(const std::vector<std::string>& filenames, const std::string& output_file = "results.txt") {
        std::vector<std::string> all_lines;
        
        // Read all lines from all files
        for (const auto& filename : filenames) {
            std::ifstream file(filename);
            if (!file.is_open()) {
                std::cerr << "Warning: Could not open file: " << filename << "\n";
                continue;
            }
            
            std::string line;
            while (std::getline(file, line)) {
                if (!line.empty()) {
                    all_lines.push_back(line);
                }
            }
            file.close();
        }
        
        std::cout << "Searching for pattern '" << pattern << "' in " << filenames.size() 
                  << " files (" << all_lines.size() << " lines)\n";
        
        // Execute MapReduce
        mapreduce.execute(all_lines, output_file);
    }
    
private:
    bool contains_pattern(const std::string& word, const std::string& pattern) const {
        std::string lower_word = word;
        std::string lower_pattern = pattern;
        
        std::transform(lower_word.begin(), lower_word.end(), lower_word.begin(), ::tolower);
        std::transform(lower_pattern.begin(), lower_pattern.end(), lower_pattern.begin(), ::tolower);
        
        return lower_word.find(lower_pattern) != std::string::npos;
    }
};

// Helper function to get all files from files/ directory
std::vector<std::string> get_files_from_directory(const std::string& directory = "files/") {
    std::vector<std::string> files;
    
    if (!std::filesystem::exists(directory)) {
        std::cerr << "Directory '" << directory << "' does not exist!\n";
        return files;
    }
    
    for (const auto& entry : std::filesystem::directory_iterator(directory)) {
        if (entry.is_regular_file()) {
            files.push_back(entry.path().string());
        }
    }
    
    std::sort(files.begin(), files.end());
    return files;
}

int main() {
    // Get files from files/ subdirectory
    auto files = get_files_from_directory();
    
    if (files.empty()) {
        std::cerr << "No files found in files/ directory!\n";
        std::cerr << "Please create a files/ subdirectory and add some text files.\n";
        return 1;
    }
    
    std::cout << "Found " << files.size() << " files:\n";
    for (const auto& file : files) {
        std::cout << "  - " << file << "\n";
    }
    std::cout << "\n";
    
    // Interactive mode for pattern search
    std::string pattern;
    std::cout << "=== FLEXIBLE MAPREDUCE PATTERN SEARCH ===\n";
    std::cout << "Enter pattern to search (or 'quit' to exit): ";
    
    while (std::getline(std::cin, pattern) && pattern != "quit") {
        if (!pattern.empty()) {
            // Create search engine with custom mapper/reducer
            PatternSearchMapReduce search_engine(pattern, 4, 2);
            
            // Generate output filename based on pattern
            std::string output_file = "results_" + pattern + ".txt";
            std::replace(output_file.begin(), output_file.end(), ' ', '_');
            
            // Perform search
            search_engine.search_files(files, output_file);
        }
        std::cout << "\nEnter another pattern (or 'quit' to exit): ";
    }
    
    std::cout << "Goodbye!\n";
    return 0;
}
