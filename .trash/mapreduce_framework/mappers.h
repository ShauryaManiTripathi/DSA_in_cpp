#pragma once

#include "interfaces.h"
#include <sstream>
#include <algorithm>
#include <cctype>
#include <regex>
#include <numeric>

namespace MapReduceFramework {

    // ============ WORD COUNT MAPPERS ============
    
    // Basic word count mapper - splits lines into words
    class WordCountMapper : public IMapper {
    public:
        MapOutput map(const MapInput& input) override {
            MapOutput results;
            std::istringstream iss(input);
            std::string word;
            
            while (iss >> word) {
                // Remove punctuation and convert to lowercase
                word.erase(std::remove_if(word.begin(), word.end(), 
                    [](char c) { return std::ispunct(c); }), word.end());
                
                if (!word.empty()) {
                    std::transform(word.begin(), word.end(), word.begin(), ::tolower);
                    results.emplace_back(word, "1");
                }
            }
            return results;
        }
        
        std::string get_description() const override {
            return "Word Count Mapper - splits lines into words";
        }
    };

    // Pattern-based word mapper - only extracts words matching a pattern
    class PatternWordMapper : public IMapper {
    private:
        std::string pattern;
        
    public:
        PatternWordMapper(const std::string& search_pattern) : pattern(search_pattern) {}
        
        MapOutput map(const MapInput& input) override {
            MapOutput results;
            std::istringstream iss(input);
            std::string word;
            
            while (iss >> word) {
                word.erase(std::remove_if(word.begin(), word.end(), 
                    [](char c) { return std::ispunct(c); }), word.end());
                
                if (!word.empty()) {
                    std::transform(word.begin(), word.end(), word.begin(), ::tolower);
                    std::string lower_pattern = pattern;
                    std::transform(lower_pattern.begin(), lower_pattern.end(), 
                                 lower_pattern.begin(), ::tolower);
                    
                    if (word.find(lower_pattern) != std::string::npos) {
                        results.emplace_back(word, "1");
                    }
                }
            }
            return results;
        }
        
        std::string get_description() const override {
            return "Pattern Word Mapper - extracts words containing: " + pattern;
        }
    };

    // ============ DATA ANALYSIS MAPPERS ============
    
    // CSV field extractor mapper
    class CSVFieldMapper : public IMapper {
    private:
        int field_index;
        char delimiter;
        
    public:
        CSVFieldMapper(int field_idx, char delim = ',') 
            : field_index(field_idx), delimiter(delim) {}
        
        MapOutput map(const MapInput& input) override {
            MapOutput results;
            std::stringstream ss(input);
            std::string field;
            int current_index = 0;
            
            while (std::getline(ss, field, delimiter)) {
                if (current_index == field_index) {
                    // Trim whitespace
                    field.erase(field.find_last_not_of(" \t\r\n") + 1);
                    field.erase(0, field.find_first_not_of(" \t\r\n"));
                    
                    if (!field.empty()) {
                        results.emplace_back(field, "1");
                    }
                    break;
                }
                current_index++;
            }
            return results;
        }
        
        std::string get_description() const override {
            return "CSV Field Mapper - extracts field " + std::to_string(field_index);
        }
    };

    // Number range mapper - categorizes numbers into ranges
    class NumberRangeMapper : public IMapper {
    private:
        int range_size;
        
    public:
        NumberRangeMapper(int range = 10) : range_size(range) {}
        
        MapOutput map(const MapInput& input) override {
            MapOutput results;
            try {
                double number = std::stod(input);
                int range_start = (static_cast<int>(number) / range_size) * range_size;
                std::string range_key = std::to_string(range_start) + "-" + 
                                      std::to_string(range_start + range_size - 1);
                results.emplace_back(range_key, std::to_string(number));
            } catch (const std::exception&) {
                // Invalid number, skip
            }
            return results;
        }
        
        std::string get_description() const override {
            return "Number Range Mapper - groups numbers into ranges of " + 
                   std::to_string(range_size);
        }
    };

    // ============ LOG ANALYSIS MAPPERS ============
    
    // Log level extractor mapper
    class LogLevelMapper : public IMapper {
    public:
        MapOutput map(const MapInput& input) override {
            MapOutput results;
            
            // Look for common log levels
            std::vector<std::string> log_levels = {"ERROR", "WARN", "INFO", "DEBUG", "TRACE"};
            
            for (const auto& level : log_levels) {
                if (input.find(level) != std::string::npos) {
                    results.emplace_back(level, "1");
                    break; // Only count first occurrence per line
                }
            }
            return results;
        }
        
        std::string get_description() const override {
            return "Log Level Mapper - extracts log levels from log lines";
        }
    };

    // IP address extractor mapper
    class IPAddressMapper : public IMapper {
    public:
        MapOutput map(const MapInput& input) override {
            MapOutput results;
            
            // Simple regex for IP addresses (basic pattern)
            std::regex ip_pattern(R"(\b(?:[0-9]{1,3}\.){3}[0-9]{1,3}\b)");
            std::sregex_iterator iter(input.begin(), input.end(), ip_pattern);
            std::sregex_iterator end;
            
            for (; iter != end; ++iter) {
                std::string ip = iter->str();
                results.emplace_back(ip, "1");
            }
            return results;
        }
        
        std::string get_description() const override {
            return "IP Address Mapper - extracts IP addresses from text";
        }
    };

    // ============ GENERIC MAPPERS ============
    
    // Line length categorizer mapper
    class LineLengthMapper : public IMapper {
    public:
        MapOutput map(const MapInput& input) override {
            MapOutput results;
            size_t length = input.length();
            
            std::string category;
            if (length == 0) category = "empty";
            else if (length < 50) category = "short";
            else if (length < 200) category = "medium";
            else category = "long";
            
            results.emplace_back(category, "1");
            return results;
        }
        
        std::string get_description() const override {
            return "Line Length Mapper - categorizes lines by length";
        }
    };

    // Character frequency mapper
    class CharFrequencyMapper : public IMapper {
    public:
        MapOutput map(const MapInput& input) override {
            MapOutput results;
            
            for (char c : input) {
                if (std::isalnum(c)) {
                    std::string char_key(1, std::tolower(c));
                    results.emplace_back(char_key, "1");
                }
            }
            return results;
        }
        
        std::string get_description() const override {
            return "Character Frequency Mapper - counts alphanumeric characters";
        }
    };

} // namespace MapReduceFramework
