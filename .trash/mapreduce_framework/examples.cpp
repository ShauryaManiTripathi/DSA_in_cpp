#include "mapreduce.h"
#include <iostream>

using namespace MapReduceFramework;

void example_word_count() {
    std::cout << "\n" << std::string(50, '=') << "\n";
    std::cout << "EXAMPLE 1: Word Count Analysis\n";
    std::cout << std::string(50, '=') << "\n";
    
    // Create a word count pipeline using factory function
    auto pipeline = create_word_count_pipeline(4, 2);
    
    // Run on directory of text files
    pipeline
        .from_directory("../threading/files", ".txt")
        .run();
}

void example_pattern_search() {
    std::cout << "\n" << std::string(50, '=') << "\n";
    std::cout << "EXAMPLE 2: Pattern Search\n";
    std::cout << std::string(50, '=') << "\n";
    
    std::string pattern;
    std::cout << "Enter search pattern: ";
    std::getline(std::cin, pattern);
    
    if (pattern.empty()) {
        pattern = "the"; // Default pattern
        std::cout << "Using default pattern: " << pattern << "\n";
    }
    
    // Create pattern search pipeline
    auto pipeline = create_pattern_search_pipeline(pattern, 4, 2);
    
    pipeline
        .from_directory("../threading/files", ".txt")
        .output_csv("pattern_results.csv")
        .run();
}

void example_custom_string_data() {
    std::cout << "\n" << std::string(50, '=') << "\n";
    std::cout << "EXAMPLE 3: Custom String Data Processing\n";
    std::cout << std::string(50, '=') << "\n";
    
    // Sample data
    std::vector<std::string> sample_data = {
        "The quick brown fox jumps over the lazy dog",
        "MapReduce is a programming model for processing large data sets",
        "Parallel processing enables faster computation on big data",
        "Threading allows concurrent execution of multiple tasks",
        "Data analysis requires efficient algorithms and data structures"
    };
    
    // Custom pipeline for line length analysis
    MapReducePipeline()
        .configure(2, 1, true)
        .from_strings(sample_data)
        .map_line_lengths()
        .reduce_count()
        .output_top(10)
        .run();
}

void example_character_frequency() {
    std::cout << "\n" << std::string(50, '=') << "\n";
    std::cout << "EXAMPLE 4: Character Frequency Analysis\n";
    std::cout << std::string(50, '=') << "\n";
    
    // Create character frequency pipeline
    auto pipeline = create_char_frequency_pipeline(3, 2);
    
    pipeline
        .from_directory("../threading/files", ".txt")
        .output_json("char_frequency.json")
        .run();
}

void example_number_analysis() {
    std::cout << "\n" << std::string(50, '=') << "\n";
    std::cout << "EXAMPLE 5: Number Range Analysis\n";
    std::cout << std::string(50, '=') << "\n";
    
    // Sample numeric data
    std::vector<std::string> numbers = {
        "15", "23", "8", "45", "67", "12", "89", "34", "56", "78",
        "91", "5", "38", "72", "29", "63", "41", "87", "14", "96"
    };
    
    MapReducePipeline()
        .configure(2, 1)
        .from_strings(numbers)
        .map_number_ranges(20)  // Group into ranges of 20
        .reduce_statistics()
        .output_statistics("number_analysis.txt")
        .run();
}

void example_advanced_statistics() {
    std::cout << "\n" << std::string(50, '=') << "\n";
    std::cout << "EXAMPLE 6: Advanced Statistical Analysis\n";
    std::cout << std::string(50, '=') << "\n";
    
    // Generate sample data with random numbers
    std::vector<std::string> data;
    for (int i = 0; i < 100; ++i) {
        data.push_back(std::to_string(rand() % 1000));
    }
    
    MapReducePipeline()
        .configure(4, 2)
        .from_strings(data)
        .map_number_ranges(100)  // Group into ranges of 100
        .reduce_statistics()
        .output_statistics()
        .run();
}

int main() {
    std::cout << "=== GENERAL PURPOSE MAPREDUCE FRAMEWORK ===\n";
    std::cout << "Version: " << VERSION << "\n\n";
    
    std::cout << "Available Examples:\n";
    std::cout << "1. Word Count Analysis\n";
    std::cout << "2. Pattern Search\n";
    std::cout << "3. Custom String Data Processing\n";
    std::cout << "4. Character Frequency Analysis\n";
    std::cout << "5. Number Range Analysis\n";
    std::cout << "6. Advanced Statistical Analysis\n";
    std::cout << "0. Run All Examples\n\n";
    
    int choice;
    std::cout << "Enter your choice (0-6): ";
    std::cin >> choice;
    std::cin.ignore(); // Clear input buffer
    
    try {
        switch (choice) {
            case 1:
                example_word_count();
                break;
            case 2:
                example_pattern_search();
                break;
            case 3:
                example_custom_string_data();
                break;
            case 4:
                example_character_frequency();
                break;
            case 5:
                example_number_analysis();
                break;
            case 6:
                example_advanced_statistics();
                break;
            case 0:
                example_word_count();
                example_custom_string_data();
                example_character_frequency();
                example_number_analysis();
                example_advanced_statistics();
                break;
            default:
                std::cout << "Invalid choice. Running word count example.\n";
                example_word_count();
                break;
        }
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << "\n";
        return 1;
    }
    
    std::cout << "\n=== EXECUTION COMPLETED ===\n";
    return 0;
}
