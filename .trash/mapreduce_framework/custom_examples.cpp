#include "mapreduce.h"
#include <iostream>
#include <regex>

using namespace MapReduceFramework;

// ============ CUSTOM MAPPER EXAMPLES ============

// Email domain extractor mapper
class EmailDomainMapper : public IMapper {
public:
    MapOutput map(const MapInput& input) override {
        MapOutput results;
        
        // Regex to find email addresses
        std::regex email_pattern(R"(\b[A-Za-z0-9._%+-]+@([A-Za-z0-9.-]+\.[A-Za-z]{2,})\b)");
        std::sregex_iterator iter(input.begin(), input.end(), email_pattern);
        std::sregex_iterator end;
        
        for (; iter != end; ++iter) {
            std::string domain = iter->str(1); // Extract domain (first capture group)
            results.emplace_back(domain, "1");
        }
        
        return results;
    }
    
    std::string get_description() const override {
        return "Email Domain Mapper - extracts email domains";
    }
};

// URL protocol mapper
class URLProtocolMapper : public IMapper {
public:
    MapOutput map(const MapInput& input) override {
        MapOutput results;
        
        // Find URLs and extract protocols
        std::regex url_pattern(R"((https?|ftp|file)://[^\s]+)");
        std::sregex_iterator iter(input.begin(), input.end(), url_pattern);
        std::sregex_iterator end;
        
        for (; iter != end; ++iter) {
            std::string protocol = iter->str(1); // Extract protocol
            results.emplace_back(protocol, "1");
        }
        
        return results;
    }
    
    std::string get_description() const override {
        return "URL Protocol Mapper - extracts URL protocols";
    }
};

// Word length categorizer mapper
class WordLengthMapper : public IMapper {
public:
    MapOutput map(const MapInput& input) override {
        MapOutput results;
        std::istringstream iss(input);
        std::string word;
        
        while (iss >> word) {
            // Remove punctuation
            word.erase(std::remove_if(word.begin(), word.end(), 
                [](char c) { return std::ispunct(c); }), word.end());
            
            if (!word.empty()) {
                std::string category;
                if (word.length() <= 3) category = "short";
                else if (word.length() <= 6) category = "medium";
                else if (word.length() <= 10) category = "long";
                else category = "very_long";
                
                results.emplace_back(category, std::to_string(word.length()));
            }
        }
        
        return results;
    }
    
    std::string get_description() const override {
        return "Word Length Mapper - categorizes words by length";
    }
};

// ============ CUSTOM REDUCER EXAMPLES ============

// Weighted average reducer
class WeightedAverageReducer : public IReducer {
public:
    ReduceOutput reduce(const ReduceKey& key, const ReduceInput& values) override {
        if (values.empty()) {
            return ReduceOutput(key, "0");
        }
        
        double total_weighted_sum = 0.0;
        double total_weight = 0.0;
        
        for (const auto& value : values) {
            try {
                double weight = std::stod(value);
                double weighted_value = weight * weight; // Use value as both value and weight
                total_weighted_sum += weighted_value;
                total_weight += weight;
            } catch (const std::exception&) {
                // Skip invalid numbers
            }
        }
        
        if (total_weight == 0.0) {
            return ReduceOutput(key, "0");
        }
        
        double weighted_avg = total_weighted_sum / total_weight;
        std::string result = "weighted_avg:" + std::to_string(weighted_avg) +
                           ",count:" + std::to_string(values.size());
        
        return ReduceOutput(key, result);
    }
    
    std::string get_description() const override {
        return "Weighted Average Reducer - calculates weighted averages";
    }
};

// Distribution analyzer reducer
class DistributionReducer : public IReducer {
public:
    ReduceOutput reduce(const ReduceKey& key, const ReduceInput& values) override {
        if (values.empty()) {
            return ReduceOutput(key, "empty");
        }
        
        size_t count = values.size();
        
        // Calculate percentile information
        std::string distribution_info;
        if (count == 1) {
            distribution_info = "singleton";
        } else if (count < 5) {
            distribution_info = "rare";
        } else if (count < 20) {
            distribution_info = "uncommon";
        } else if (count < 100) {
            distribution_info = "common";
        } else {
            distribution_info = "frequent";
        }
        
        std::string result = "count:" + std::to_string(count) +
                           ",distribution:" + distribution_info;
        
        return ReduceOutput(key, result);
    }
    
    std::string get_description() const override {
        return "Distribution Reducer - analyzes value distribution patterns";
    }
};

// ============ CUSTOM RESULT HANDLER EXAMPLES ============

class CustomAnalyticsHandler : public IResultHandler {
public:
    void handle_results(const std::unordered_map<ReduceKey, ReduceValue>& results, 
                      const MapReduceConfig& config) override {
        std::cout << "\n=== CUSTOM ANALYTICS REPORT ===\n";
        std::cout << "Analysis completed with " << results.size() << " unique categories\n\n";
        
        // Categorize results
        std::map<std::string, std::vector<std::pair<std::string, std::string>>> categories;
        
        for (const auto& pair : results) {
            // Try to extract category from the result value
            if (pair.second.find("distribution:") != std::string::npos) {
                size_t pos = pair.second.find("distribution:") + 13;
                size_t end = pair.second.find(",", pos);
                if (end == std::string::npos) end = pair.second.length();
                
                std::string dist_category = pair.second.substr(pos, end - pos);
                categories[dist_category].emplace_back(pair.first, pair.second);
            } else {
                categories["other"].emplace_back(pair.first, pair.second);
            }
        }
        
        // Display categorized results
        for (const auto& category : categories) {
            std::cout << "Category: " << category.first << " (" << category.second.size() << " items)\n";
            
            for (const auto& item : category.second) {
                std::cout << "  " << item.first << " -> " << item.second << "\n";
            }
            std::cout << "\n";
        }
        
        // Save detailed report if output file specified
        if (!config.output_file.empty()) {
            save_detailed_report(results, config, categories);
        }
    }
    
private:
    void save_detailed_report(const std::unordered_map<ReduceKey, ReduceValue>& results,
                            const MapReduceConfig& config,
                            const std::map<std::string, std::vector<std::pair<std::string, std::string>>>& categories) {
        std::ofstream file(config.output_file);
        if (!file.is_open()) {
            std::cerr << "Error: Could not open output file: " << config.output_file << "\n";
            return;
        }
        
        file << "# Custom Analytics Report\n";
        file << "# Generated by General Purpose MapReduce Framework\n\n";
        file << "Total Categories: " << categories.size() << "\n";
        file << "Total Items: " << results.size() << "\n\n";
        
        for (const auto& category : categories) {
            file << "## " << category.first << " (" << category.second.size() << " items)\n\n";
            
            for (const auto& item : category.second) {
                file << item.first << " | " << item.second << "\n";
            }
            file << "\n";
        }
        
        file.close();
        std::cout << "Detailed report saved to: " << config.output_file << "\n";
    }
};

// ============ DEMONSTRATION FUNCTIONS ============

void demo_email_domain_analysis() {
    std::cout << "\n" << std::string(50, '=') << "\n";
    std::cout << "DEMO: Email Domain Analysis\n";
    std::cout << std::string(50, '=') << "\n";
    
    // Sample email data
    std::vector<std::string> email_data = {
        "Contact us at support@example.com or sales@company.org",
        "John Doe (john.doe@gmail.com) and Jane Smith (jane@yahoo.com)",
        "For business inquiries: business@startup.io, tech@innovation.ai",
        "University emails: professor@university.edu, student@college.edu",
        "Government contact: info@government.gov, admin@agency.gov"
    };
    
    MapReducePipeline()
        .configure(2, 2)
        .from_strings(email_data)
        .map_custom(std::make_unique<EmailDomainMapper>())
        .reduce_count()
        .output_top(10)
        .run();
}

void demo_url_protocol_analysis() {
    std::cout << "\n" << std::string(50, '=') << "\n";
    std::cout << "DEMO: URL Protocol Analysis\n";
    std::cout << std::string(50, '=') << "\n";
    
    // Sample URL data
    std::vector<std::string> url_data = {
        "Visit https://www.example.com for more information",
        "Download from ftp://files.server.com/data.zip",
        "Secure site: https://secure.bank.com/login",
        "Local file: file:///home/user/document.pdf",
        "Standard site: http://old.website.org/page.html",
        "API endpoint: https://api.service.com/v1/data"
    };
    
    MapReducePipeline()
        .configure(2, 2)
        .from_strings(url_data)
        .map_custom(std::make_unique<URLProtocolMapper>())
        .reduce_count()
        .output_top(5)
        .run();
}

void demo_word_length_analysis() {
    std::cout << "\n" << std::string(50, '=') << "\n";
    std::cout << "DEMO: Word Length Analysis with Custom Reducers\n";
    std::cout << std::string(50, '=') << "\n";
    
    // Use files from the existing directory
    MapReducePipeline()
        .configure(3, 2)
        .from_directory("../threading/files", ".txt")
        .map_custom(std::make_unique<WordLengthMapper>())
        .reduce_custom(std::make_unique<WeightedAverageReducer>())
        .output_custom(std::make_unique<CustomAnalyticsHandler>())
        .run();
}

void demo_distribution_analysis() {
    std::cout << "\n" << std::string(50, '=') << "\n";
    std::cout << "DEMO: Distribution Analysis\n";
    std::cout << std::string(50, '=') << "\n";
    
    MapReducePipeline()
        .configure(4, 2)
        .from_directory("../threading/files", ".txt")
        .map_word_count()
        .reduce_custom(std::make_unique<DistributionReducer>())
        .output_custom(std::make_unique<CustomAnalyticsHandler>())
        .run();
}

int main() {
    std::cout << "=== CUSTOM MAPPERS AND REDUCERS DEMO ===\n\n";
    
    std::cout << "Available Demonstrations:\n";
    std::cout << "1. Email Domain Analysis\n";
    std::cout << "2. URL Protocol Analysis\n";
    std::cout << "3. Word Length Analysis with Custom Reducers\n";
    std::cout << "4. Distribution Analysis\n";
    std::cout << "0. Run All Demonstrations\n\n";
    
    int choice;
    std::cout << "Enter your choice (0-4): ";
    std::cin >> choice;
    std::cin.ignore();
    
    try {
        switch (choice) {
            case 1:
                demo_email_domain_analysis();
                break;
            case 2:
                demo_url_protocol_analysis();
                break;
            case 3:
                demo_word_length_analysis();
                break;
            case 4:
                demo_distribution_analysis();
                break;
            case 0:
                demo_email_domain_analysis();
                demo_url_protocol_analysis();
                demo_word_length_analysis();
                demo_distribution_analysis();
                break;
            default:
                std::cout << "Invalid choice. Running email domain analysis.\n";
                demo_email_domain_analysis();
                break;
        }
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << "\n";
        return 1;
    }
    
    std::cout << "\n=== CUSTOM DEMOS COMPLETED ===\n";
    return 0;
}
