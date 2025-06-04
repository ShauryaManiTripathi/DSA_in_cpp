#include "mapreduce.h"

using namespace MapReduceFramework;

void print_usage() {
    std::cout << "Usage: ./mapreduce_engine [options]\n";
    std::cout << "Options:\n";
    std::cout << "  --mapper <executable>     Path to mapper executable\n";
    std::cout << "  --reducer <executable>    Path to reducer executable\n";
    std::cout << "  --input <dir/file>        Input directory or file\n";
    std::cout << "  --output <dir>            Output directory (default: output)\n";
    std::cout << "  --mappers <num>           Number of mapper threads (default: 4)\n";
    std::cout << "  --reducers <num>          Number of reducer threads (default: 2)\n";
    std::cout << "  --merge                   Merge final output into single file\n";
    std::cout << "  --verbose                 Enable verbose logging\n";
    std::cout << "  --help                    Show this help\n";
    std::cout << "\nExample:\n";
    std::cout << "  ./mapreduce_engine --mapper ./wordcount_mapper --reducer ./wordcount_reducer --input data/ --mappers 8 --reducers 4\n";
}

int main(int argc, char* argv[]) {
    Config config;
    bool merge_output = false;
    
    // Parse command line arguments
    for (int i = 1; i < argc; ++i) {
        std::string arg = argv[i];
        
        if (arg == "--help") {
            print_usage();
            return 0;
        } else if (arg == "--mapper" && i + 1 < argc) {
            config.mapper_executable = argv[++i];
        } else if (arg == "--reducer" && i + 1 < argc) {
            config.reducer_executable = argv[++i];
        } else if (arg == "--input" && i + 1 < argc) {
            config.input_dir = argv[++i];
        } else if (arg == "--output" && i + 1 < argc) {
            config.output_dir = argv[++i];
        } else if (arg == "--mappers" && i + 1 < argc) {
            config.num_mappers = std::stoi(argv[++i]);
        } else if (arg == "--reducers" && i + 1 < argc) {
            config.num_reducers = std::stoi(argv[++i]);
        } else if (arg == "--merge") {
            merge_output = true;
        } else if (arg == "--verbose") {
            config.verbose = true;
        } else {
            std::cerr << "Unknown argument: " << arg << std::endl;
            print_usage();
            return 1;
        }
    }
    
    // Validate required arguments
    if (config.mapper_executable.empty() || config.reducer_executable.empty() || config.input_dir.empty()) {
        std::cerr << "Error: mapper, reducer, and input are required\n\n";
        print_usage();
        return 1;
    }
    
    try {
        std::cout << "=== MULTITHREADED MAPREDUCE ENGINE ===\n";
        
        // Create and run MapReduce engine
        MapReduceEngine engine(config);
        engine.execute();
        
        // Optionally merge output
        if (merge_output) {
            engine.merge_final_output();
        }
        
        std::cout << "\n=== EXECUTION COMPLETED SUCCESSFULLY ===\n";
        
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
    
    return 0;
}
