#pragma once

#include "interfaces.h"
#include <algorithm>
#include <numeric>
#include <sstream>
#include <set>
#include <cmath>

namespace MapReduceFramework {

    // ============ AGGREGATION REDUCERS ============
    
    // Sum reducer - adds up numeric values
    class SumReducer : public IReducer {
    public:
        ReduceOutput reduce(const ReduceKey& key, const ReduceInput& values) override {
            double sum = 0.0;
            
            for (const auto& value : values) {
                try {
                    sum += std::stod(value);
                } catch (const std::exception&) {
                    // Skip invalid numbers
                }
            }
            
            return ReduceOutput(key, std::to_string(sum));
        }
        
        std::string get_description() const override {
            return "Sum Reducer - adds up numeric values";
        }
    };

    // Count reducer - counts occurrences
    class CountReducer : public IReducer {
    public:
        ReduceOutput reduce(const ReduceKey& key, const ReduceInput& values) override {
            return ReduceOutput(key, std::to_string(values.size()));
        }
        
        std::string get_description() const override {
            return "Count Reducer - counts occurrences";
        }
    };

    // Average reducer - calculates mean of numeric values
    class AverageReducer : public IReducer {
    public:
        ReduceOutput reduce(const ReduceKey& key, const ReduceInput& values) override {
            if (values.empty()) {
                return ReduceOutput(key, "0");
            }
            
            double sum = 0.0;
            int valid_count = 0;
            
            for (const auto& value : values) {
                try {
                    sum += std::stod(value);
                    valid_count++;
                } catch (const std::exception&) {
                    // Skip invalid numbers
                }
            }
            
            if (valid_count == 0) {
                return ReduceOutput(key, "0");
            }
            
            double average = sum / valid_count;
            return ReduceOutput(key, std::to_string(average));
        }
        
        std::string get_description() const override {
            return "Average Reducer - calculates mean of numeric values";
        }
    };

    // Min/Max reducer - finds minimum and maximum values
    class MinMaxReducer : public IReducer {
    public:
        ReduceOutput reduce(const ReduceKey& key, const ReduceInput& values) override {
            if (values.empty()) {
                return ReduceOutput(key, "min:0,max:0");
            }
            
            double min_val = std::numeric_limits<double>::max();
            double max_val = std::numeric_limits<double>::lowest();
            bool found_valid = false;
            
            for (const auto& value : values) {
                try {
                    double num = std::stod(value);
                    min_val = std::min(min_val, num);
                    max_val = std::max(max_val, num);
                    found_valid = true;
                } catch (const std::exception&) {
                    // Skip invalid numbers
                }
            }
            
            if (!found_valid) {
                return ReduceOutput(key, "min:0,max:0");
            }
            
            std::string result = "min:" + std::to_string(min_val) + 
                               ",max:" + std::to_string(max_val);
            return ReduceOutput(key, result);
        }
        
        std::string get_description() const override {
            return "MinMax Reducer - finds minimum and maximum values";
        }
    };

    // ============ STRING PROCESSING REDUCERS ============
    
    // Concatenation reducer - joins string values
    class ConcatReducer : public IReducer {
    private:
        std::string delimiter;
        
    public:
        ConcatReducer(const std::string& delim = ",") : delimiter(delim) {}
        
        ReduceOutput reduce(const ReduceKey& key, const ReduceInput& values) override {
            if (values.empty()) {
                return ReduceOutput(key, "");
            }
            
            std::string result = values[0];
            for (size_t i = 1; i < values.size(); ++i) {
                result += delimiter + values[i];
            }
            
            return ReduceOutput(key, result);
        }
        
        std::string get_description() const override {
            return "Concat Reducer - joins values with delimiter '" + delimiter + "'";
        }
    };

    // Unique values reducer - removes duplicates and counts unique occurrences
    class UniqueReducer : public IReducer {
    public:
        ReduceOutput reduce(const ReduceKey& key, const ReduceInput& values) override {
            std::set<std::string> unique_values(values.begin(), values.end());
            
            std::string result = "unique_count:" + std::to_string(unique_values.size()) +
                               ",total_count:" + std::to_string(values.size());
            
            return ReduceOutput(key, result);
        }
        
        std::string get_description() const override {
            return "Unique Reducer - counts unique vs total occurrences";
        }
    };

    // ============ STATISTICAL REDUCERS ============
    
    // Statistics reducer - comprehensive statistical analysis
    class StatisticsReducer : public IReducer {
    public:
        ReduceOutput reduce(const ReduceKey& key, const ReduceInput& values) override {
            if (values.empty()) {
                return ReduceOutput(key, "count:0");
            }
            
            std::vector<double> numbers;
            for (const auto& value : values) {
                try {
                    numbers.push_back(std::stod(value));
                } catch (const std::exception&) {
                    // Skip invalid numbers
                }
            }
            
            if (numbers.empty()) {
                return ReduceOutput(key, "count:0,type:non-numeric");
            }
            
            // Calculate statistics
            size_t count = numbers.size();
            double sum = std::accumulate(numbers.begin(), numbers.end(), 0.0);
            double mean = sum / count;
            
            std::sort(numbers.begin(), numbers.end());
            double median = (count % 2 == 0) ? 
                          (numbers[count/2 - 1] + numbers[count/2]) / 2.0 :
                          numbers[count/2];
            
            double min_val = numbers.front();
            double max_val = numbers.back();
            
            // Calculate standard deviation
            double variance = 0.0;
            for (double num : numbers) {
                variance += (num - mean) * (num - mean);
            }
            variance /= count;
            double std_dev = std::sqrt(variance);
            
            std::string result = "count:" + std::to_string(count) +
                               ",sum:" + std::to_string(sum) +
                               ",mean:" + std::to_string(mean) +
                               ",median:" + std::to_string(median) +
                               ",min:" + std::to_string(min_val) +
                               ",max:" + std::to_string(max_val) +
                               ",stddev:" + std::to_string(std_dev);
            
            return ReduceOutput(key, result);
        }
        
        std::string get_description() const override {
            return "Statistics Reducer - comprehensive statistical analysis";
        }
    };

    // ============ SPECIALIZED REDUCERS ============
    
    // Frequency ranking reducer - ranks items by frequency
    class FrequencyRankReducer : public IReducer {
    public:
        ReduceOutput reduce(const ReduceKey& key, const ReduceInput& values) override {
            size_t frequency = values.size();
            
            // Create a ranking category based on frequency
            std::string rank;
            if (frequency == 1) rank = "rare";
            else if (frequency < 5) rank = "uncommon";
            else if (frequency < 20) rank = "common";
            else rank = "frequent";
            
            std::string result = "frequency:" + std::to_string(frequency) + 
                               ",rank:" + rank;
            
            return ReduceOutput(key, result);
        }
        
        std::string get_description() const override {
            return "Frequency Rank Reducer - categorizes by occurrence frequency";
        }
    };

    // Top-K reducer - keeps only top K most frequent items (simplified version)
    class TopKReducer : public IReducer {
    private:
        int k;
        
    public:
        TopKReducer(int top_k = 10) : k(top_k) {}
        
        ReduceOutput reduce(const ReduceKey& key, const ReduceInput& values) override {
            size_t frequency = values.size();
            
            // This is a simplified version - in a real top-K implementation,
            // you'd need a different approach involving global coordination
            std::string result = "frequency:" + std::to_string(frequency);
            
            return ReduceOutput(key, result);
        }
        
        std::string get_description() const override {
            return "TopK Reducer (simplified) - tracks frequency for top-" + 
                   std::to_string(k) + " analysis";
        }
    };

    // ============ CUSTOM BUSINESS LOGIC REDUCERS ============
    
    // Log severity aggregator - analyzes log severity patterns
    class LogSeverityReducer : public IReducer {
    public:
        ReduceOutput reduce(const ReduceKey& key, const ReduceInput& values) override {
            size_t count = values.size();
            
            // Assign severity scores
            int severity_score = 0;
            if (key == "ERROR") severity_score = 4;
            else if (key == "WARN") severity_score = 3;
            else if (key == "INFO") severity_score = 2;
            else if (key == "DEBUG") severity_score = 1;
            else if (key == "TRACE") severity_score = 0;
            
            int total_severity = severity_score * count;
            
            std::string result = "count:" + std::to_string(count) +
                               ",severity_score:" + std::to_string(severity_score) +
                               ",total_impact:" + std::to_string(total_severity);
            
            return ReduceOutput(key, result);
        }
        
        std::string get_description() const override {
            return "Log Severity Reducer - analyzes log impact by severity";
        }
    };

} // namespace MapReduceFramework
