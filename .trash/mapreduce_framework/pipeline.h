#pragma once

#include "interfaces.h"
#include "mapreduce_engine.h"
#include "mappers.h"
#include "reducers.h"
#include "result_handlers.h"
#include <filesystem>
#include <fstream>
#include <iostream>
#include <vector>
#include <unordered_map>
#include <memory>
#include <string>

namespace MapReduceFramework {

    // Data source interface for different input types
    class IDataSource {
    public:
        virtual ~IDataSource() = default;
        virtual std::vector<MapInput> load_data() = 0;
        virtual std::string get_description() const = 0;
        
        // For streaming large datasets - return file paths instead of loading data
        virtual std::vector<std::string> get_file_paths() const { return {}; }
        virtual bool supports_streaming() const { return false; }
    };

    // File-based data source with streaming support
    class FileDataSource : public IDataSource {
    private:
        std::vector<std::string> file_paths;
        bool read_line_by_line;
        bool enable_streaming;
        size_t max_file_size_mb;
        
    public:
        FileDataSource(const std::vector<std::string>& files, bool line_mode = true, bool streaming = true)
            : file_paths(files), read_line_by_line(line_mode), enable_streaming(streaming), max_file_size_mb(100) {}
        
        FileDataSource(const std::string& directory, const std::string& extension = ".txt", bool streaming = true)
            : read_line_by_line(true), enable_streaming(streaming), max_file_size_mb(100) {
            load_files_from_directory(directory, extension);
        }
        
        std::vector<MapInput> load_data() override {
            std::vector<MapInput> data;
            
            // For large files or when streaming is enabled, don't load into memory
            if (enable_streaming && has_large_files()) {
                std::cout << "Note: Large files detected. Use get_file_paths() for streaming processing.\n";
                return data; // Return empty - caller should use get_file_paths()
            }
            
            for (const auto& file_path : file_paths) {
                std::ifstream file(file_path);
                if (!file.is_open()) {
                    std::cerr << "Warning: Could not open file: " << file_path << "\n";
                    continue;
                }
                
                if (read_line_by_line) {
                    std::string line;
                    while (std::getline(file, line)) {
                        if (!line.empty()) {
                            data.push_back(line);
                        }
                    }
                } else {
                    // Check file size before loading
                    file.seekg(0, std::ios::end);
                    size_t file_size = file.tellg();
                    file.seekg(0, std::ios::beg);
                    
                    if (file_size > max_file_size_mb * 1024 * 1024) {
                        std::cerr << "Warning: File " << file_path << " is too large (" 
                                  << file_size / (1024*1024) << " MB). Skipping.\n";
                        continue;
                    }
                    
                    // Read entire file as one input
                    std::string content((std::istreambuf_iterator<char>(file)),
                                      std::istreambuf_iterator<char>());
                    if (!content.empty()) {
                        data.push_back(content);
                    }
                }
                file.close();
            }
            
            return data;
        }
        
        std::vector<std::string> get_file_paths() const override {
            return file_paths;
        }
        
        bool supports_streaming() const override {
            return enable_streaming;
        }
        
        std::string get_description() const override {
            return "File Data Source - " + std::to_string(file_paths.size()) + " files, " +
                   (read_line_by_line ? "line-by-line" : "whole-file") + " mode" +
                   (enable_streaming ? " (streaming enabled)" : "");
        }
        
    private:
        bool has_large_files() const {
            for (const auto& file_path : file_paths) {
                if (std::filesystem::exists(file_path)) {
                    auto file_size = std::filesystem::file_size(file_path);
                    if (file_size > max_file_size_mb * 1024 * 1024) {
                        return true;
                    }
                }
            }
            return false;
        }
        
        void load_files_from_directory(const std::string& directory, const std::string& extension) {
            if (!std::filesystem::exists(directory)) {
                std::cerr << "Warning: Directory does not exist: " << directory << "\n";
                return;
            }
            
            for (const auto& entry : std::filesystem::directory_iterator(directory)) {
                if (entry.is_regular_file()) {
                    std::string file_path = entry.path().string();
                    if (extension.empty() || file_path.ends_with(extension)) {
                        file_paths.push_back(file_path);
                    }
                }
            }
            
            std::sort(file_paths.begin(), file_paths.end());
        }
    };

    // String array data source
    class StringArrayDataSource : public IDataSource {
    private:
        std::vector<std::string> data;
        
    public:
        StringArrayDataSource(const std::vector<std::string>& input_data)
            : data(input_data) {}
        
        std::vector<MapInput> load_data() override {
            return data;
        }
        
        std::string get_description() const override {
            return "String Array Data Source - " + std::to_string(data.size()) + " items";
        }
    };

    // CSV data source
    class CSVDataSource : public IDataSource {
    private:
        std::string file_path;
        char delimiter;
        bool has_header;
        
    public:
        CSVDataSource(const std::string& csv_file, char delim = ',', bool header = true)
            : file_path(csv_file), delimiter(delim), has_header(header) {}
        
        std::vector<MapInput> load_data() override {
            std::vector<MapInput> data;
            std::ifstream file(file_path);
            
            if (!file.is_open()) {
                std::cerr << "Error: Could not open CSV file: " << file_path << "\n";
                return data;
            }
            
            std::string line;
            bool first_line = true;
            
            while (std::getline(file, line)) {
                if (first_line && has_header) {
                    first_line = false;
                    continue; // Skip header
                }
                
                if (!line.empty()) {
                    data.push_back(line);
                }
                first_line = false;
            }
            
            file.close();
            return data;
        }
        
        std::string get_description() const override {
            return "CSV Data Source - " + file_path + 
                   (has_header ? " (with header)" : " (no header)");
        }
    };

    // Pipeline manager for easy MapReduce job composition
    class MapReducePipeline {
    private:
        std::unique_ptr<IDataSource> data_source;
        std::unique_ptr<MapReduceEngine> engine;
        MapReduceConfig config;
        
    public:
        MapReducePipeline(const MapReduceConfig& cfg = MapReduceConfig())
            : config(cfg) {
            engine = std::make_unique<MapReduceEngine>(config);
        }
        
        // Move constructor
        MapReducePipeline(MapReducePipeline&& other) noexcept
            : data_source(std::move(other.data_source)),
              engine(std::move(other.engine)),
              config(std::move(other.config)) {}
        
        // Move assignment operator
        MapReducePipeline& operator=(MapReducePipeline&& other) noexcept {
            if (this != &other) {
                data_source = std::move(other.data_source);
                engine = std::move(other.engine);
                config = std::move(other.config);
            }
            return *this;
        }
        
        // Delete copy constructor and assignment
        MapReducePipeline(const MapReducePipeline&) = delete;
        MapReducePipeline& operator=(const MapReducePipeline&) = delete;
        
        // Set data source
        MapReducePipeline& from_files(const std::vector<std::string>& files, bool line_mode = true) {
            data_source = std::make_unique<FileDataSource>(files, line_mode);
            return *this;
        }
        
        MapReducePipeline& from_directory(const std::string& directory, const std::string& extension = ".txt") {
            data_source = std::make_unique<FileDataSource>(directory, extension);
            return *this;
        }
        
        MapReducePipeline& from_strings(const std::vector<std::string>& data) {
            data_source = std::make_unique<StringArrayDataSource>(data);
            return *this;
        }
        
        MapReducePipeline& from_csv(const std::string& file, char delimiter = ',', bool has_header = true) {
            data_source = std::make_unique<CSVDataSource>(file, delimiter, has_header);
            return *this;
        }
        
        // Set processing components with factory methods
        MapReducePipeline& map_word_count() {
            engine->set_mapper(std::make_unique<WordCountMapper>());
            return *this;
        }
        
        MapReducePipeline& map_pattern_words(const std::string& pattern) {
            engine->set_mapper(std::make_unique<PatternWordMapper>(pattern));
            return *this;
        }
        
        MapReducePipeline& map_csv_field(int field_index, char delimiter = ',') {
            engine->set_mapper(std::make_unique<CSVFieldMapper>(field_index, delimiter));
            return *this;
        }
        
        MapReducePipeline& map_number_ranges(int range_size = 10) {
            engine->set_mapper(std::make_unique<NumberRangeMapper>(range_size));
            return *this;
        }
        
        MapReducePipeline& map_log_levels() {
            engine->set_mapper(std::make_unique<LogLevelMapper>());
            return *this;
        }
        
        MapReducePipeline& map_ip_addresses() {
            engine->set_mapper(std::make_unique<IPAddressMapper>());
            return *this;
        }
        
        MapReducePipeline& map_line_lengths() {
            engine->set_mapper(std::make_unique<LineLengthMapper>());
            return *this;
        }
        
        MapReducePipeline& map_char_frequency() {
            engine->set_mapper(std::make_unique<CharFrequencyMapper>());
            return *this;
        }
        
        // Custom mapper
        MapReducePipeline& map_custom(std::unique_ptr<IMapper> mapper) {
            engine->set_mapper(std::move(mapper));
            return *this;
        }
        
        // Reducer factory methods
        MapReducePipeline& reduce_sum() {
            engine->set_reducer(std::make_unique<SumReducer>());
            return *this;
        }
        
        MapReducePipeline& reduce_count() {
            engine->set_reducer(std::make_unique<CountReducer>());
            return *this;
        }
        
        MapReducePipeline& reduce_average() {
            engine->set_reducer(std::make_unique<AverageReducer>());
            return *this;
        }
        
        MapReducePipeline& reduce_min_max() {
            engine->set_reducer(std::make_unique<MinMaxReducer>());
            return *this;
        }
        
        MapReducePipeline& reduce_concat(const std::string& delimiter = ",") {
            engine->set_reducer(std::make_unique<ConcatReducer>(delimiter));
            return *this;
        }
        
        MapReducePipeline& reduce_unique() {
            engine->set_reducer(std::make_unique<UniqueReducer>());
            return *this;
        }
        
        MapReducePipeline& reduce_statistics() {
            engine->set_reducer(std::make_unique<StatisticsReducer>());
            return *this;
        }
        
        MapReducePipeline& reduce_frequency_rank() {
            engine->set_reducer(std::make_unique<FrequencyRankReducer>());
            return *this;
        }
        
        MapReducePipeline& reduce_log_severity() {
            engine->set_reducer(std::make_unique<LogSeverityReducer>());
            return *this;
        }
        
        // Custom reducer
        MapReducePipeline& reduce_custom(std::unique_ptr<IReducer> reducer) {
            engine->set_reducer(std::move(reducer));
            return *this;
        }
        
        // Output handler factory methods
        MapReducePipeline& output_csv(const std::string& filename = "results.csv") {
            config.output_file = filename;
            engine->set_result_handler(std::make_unique<CSVResultHandler>());
            return *this;
        }
        
        MapReducePipeline& output_json(const std::string& filename = "results.json") {
            config.output_file = filename;
            engine->set_result_handler(std::make_unique<JSONResultHandler>());
            return *this;
        }
        
        MapReducePipeline& output_top(int n = 10, bool sort_by_value = true) {
            engine->set_result_handler(std::make_unique<TopResultsHandler>(n, sort_by_value));
            return *this;
        }
        
        MapReducePipeline& output_statistics(const std::string& filename = "") {
            if (!filename.empty()) {
                config.output_file = filename;
            }
            engine->set_result_handler(std::make_unique<StatisticalSummaryHandler>());
            return *this;
        }
        
        MapReducePipeline& output_log_analysis() {
            engine->set_result_handler(std::make_unique<LogAnalysisHandler>());
            return *this;
        }
        
        // Custom output handler
        MapReducePipeline& output_custom(std::unique_ptr<IResultHandler> handler) {
            engine->set_result_handler(std::move(handler));
            return *this;
        }
        
        // Configuration
        MapReducePipeline& configure(int mappers, int reducers, bool verbose = true) {
            config.num_mappers = mappers;
            config.num_reducers = reducers;
            config.verbose = verbose;
            engine->update_config(config);
            return *this;
        }
        
        // Execute the pipeline
        void run() {
            if (!data_source) {
                throw std::runtime_error("Data source must be set before execution");
            }
            
            if (config.verbose) {
                std::cout << "=== MAPREDUCE PIPELINE EXECUTION ===\n";
                std::cout << "Data Source: " << data_source->get_description() << "\n";
            }
            
            // Load data
            auto data = data_source->load_data();
            
            if (data.empty()) {
                std::cout << "Warning: No data loaded from source\n";
                return;
            }
            
            // Execute MapReduce
            engine->execute(data);
        }
        
        // Get results for further processing
        const std::unordered_map<ReduceKey, ReduceValue>& get_results() const {
            return engine->get_results();
        }
    };

} // namespace MapReduceFramework
