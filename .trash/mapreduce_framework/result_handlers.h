#pragma once

#include "interfaces.h"
#include <iostream>
#include <fstream>
#include <algorithm>
#include <iomanip>
#include <sstream>

namespace MapReduceFramework {

    // ============ FILE OUTPUT HANDLERS ============
    
    // CSV output handler
    class CSVResultHandler : public IResultHandler {
    public:
        void handle_results(const std::unordered_map<ReduceKey, ReduceValue>& results, 
                          const MapReduceConfig& config) override {
            std::string filename = config.output_file.empty() ? "results.csv" : config.output_file;
            
            std::ofstream file(filename);
            if (!file.is_open()) {
                std::cerr << "Error: Could not open output file: " << filename << "\n";
                return;
            }
            
            // Write CSV header
            file << "Key,Value\n";
            
            // Sort results by key for consistent output
            std::vector<std::pair<ReduceKey, ReduceValue>> sorted_results(
                results.begin(), results.end());
            std::sort(sorted_results.begin(), sorted_results.end());
            
            for (const auto& pair : sorted_results) {
                // Escape CSV values if they contain commas or quotes
                std::string escaped_key = escape_csv_value(pair.first);
                std::string escaped_value = escape_csv_value(pair.second);
                
                file << escaped_key << "," << escaped_value << "\n";
            }
            
            file.close();
            
            if (config.verbose) {
                std::cout << "\n=== CSV OUTPUT ===\n";
                std::cout << "Results saved to: " << filename << "\n";
                std::cout << "Total records: " << results.size() << "\n";
            }
        }
        
    private:
        std::string escape_csv_value(const std::string& value) {
            if (value.find(',') != std::string::npos || 
                value.find('"') != std::string::npos ||
                value.find('\n') != std::string::npos) {
                
                std::string escaped = "\"";
                for (char c : value) {
                    if (c == '"') escaped += "\"\"";
                    else escaped += c;
                }
                escaped += "\"";
                return escaped;
            }
            return value;
        }
    };

    // JSON output handler
    class JSONResultHandler : public IResultHandler {
    public:
        void handle_results(const std::unordered_map<ReduceKey, ReduceValue>& results, 
                          const MapReduceConfig& config) override {
            std::string filename = config.output_file.empty() ? "results.json" : config.output_file;
            
            std::ofstream file(filename);
            if (!file.is_open()) {
                std::cerr << "Error: Could not open output file: " << filename << "\n";
                return;
            }
            
            file << "{\n";
            file << "  \"mapreduce_results\": {\n";
            file << "    \"total_keys\": " << results.size() << ",\n";
            file << "    \"data\": {\n";
            
            // Sort results by key for consistent output
            std::vector<std::pair<ReduceKey, ReduceValue>> sorted_results(
                results.begin(), results.end());
            std::sort(sorted_results.begin(), sorted_results.end());
            
            for (size_t i = 0; i < sorted_results.size(); ++i) {
                const auto& pair = sorted_results[i];
                file << "      \"" << escape_json_string(pair.first) << "\": \"" 
                     << escape_json_string(pair.second) << "\"";
                
                if (i < sorted_results.size() - 1) {
                    file << ",";
                }
                file << "\n";
            }
            
            file << "    }\n";
            file << "  }\n";
            file << "}\n";
            
            file.close();
            
            if (config.verbose) {
                std::cout << "\n=== JSON OUTPUT ===\n";
                std::cout << "Results saved to: " << filename << "\n";
                std::cout << "Total records: " << results.size() << "\n";
            }
        }
        
    private:
        std::string escape_json_string(const std::string& str) {
            std::string escaped;
            for (char c : str) {
                switch (c) {
                    case '"': escaped += "\\\""; break;
                    case '\\': escaped += "\\\\"; break;
                    case '\n': escaped += "\\n"; break;
                    case '\r': escaped += "\\r"; break;
                    case '\t': escaped += "\\t"; break;
                    default: escaped += c; break;
                }
            }
            return escaped;
        }
    };

    // ============ FORMATTED CONSOLE HANDLERS ============
    
    // Top results handler - shows only top N results
    class TopResultsHandler : public IResultHandler {
    private:
        int top_n;
        bool sort_by_value;
        
    public:
        TopResultsHandler(int n = 10, bool sort_val = true) 
            : top_n(n), sort_by_value(sort_val) {}
        
        void handle_results(const std::unordered_map<ReduceKey, ReduceValue>& results, 
                          const MapReduceConfig& config) override {
            std::cout << "\n=== TOP " << top_n << " RESULTS ===\n";
            std::cout << "Total unique keys: " << results.size() << "\n\n";
            
            // Convert to vector for sorting
            std::vector<std::pair<ReduceKey, ReduceValue>> sorted_results(
                results.begin(), results.end());
            
            if (sort_by_value) {
                // Sort by numeric value (descending)
                std::sort(sorted_results.begin(), sorted_results.end(),
                    [](const auto& a, const auto& b) {
                        try {
                            return std::stod(a.second) > std::stod(b.second);
                        } catch (const std::exception&) {
                            return a.second > b.second; // Fallback to string comparison
                        }
                    });
            } else {
                // Sort by key
                std::sort(sorted_results.begin(), sorted_results.end());
            }
            
            // Show top N results
            int count = 0;
            for (const auto& pair : sorted_results) {
                if (count >= top_n) break;
                
                std::cout << std::setw(3) << (count + 1) << ". "
                          << std::setw(20) << std::left << ("'" + pair.first + "'")
                          << " -> " << pair.second << "\n";
                count++;
            }
            
            if (results.size() > static_cast<size_t>(top_n)) {
                std::cout << "... and " << (results.size() - top_n) << " more results\n";
            }
        }
    };

    // Statistical summary handler
    class StatisticalSummaryHandler : public IResultHandler {
    public:
        void handle_results(const std::unordered_map<ReduceKey, ReduceValue>& results, 
                          const MapReduceConfig& config) override {
            std::cout << "\n=== STATISTICAL SUMMARY ===\n";
            std::cout << "Total unique keys: " << results.size() << "\n";
            
            // Analyze value distribution
            std::vector<double> numeric_values;
            int non_numeric_count = 0;
            
            for (const auto& pair : results) {
                try {
                    numeric_values.push_back(std::stod(pair.second));
                } catch (const std::exception&) {
                    non_numeric_count++;
                }
            }
            
            std::cout << "Numeric values: " << numeric_values.size() << "\n";
            std::cout << "Non-numeric values: " << non_numeric_count << "\n";
            
            if (!numeric_values.empty()) {
                std::sort(numeric_values.begin(), numeric_values.end());
                
                double sum = std::accumulate(numeric_values.begin(), numeric_values.end(), 0.0);
                double mean = sum / numeric_values.size();
                double median = (numeric_values.size() % 2 == 0) ?
                              (numeric_values[numeric_values.size()/2 - 1] + 
                               numeric_values[numeric_values.size()/2]) / 2.0 :
                              numeric_values[numeric_values.size()/2];
                
                std::cout << "\nNumeric Statistics:\n";
                std::cout << "  Sum: " << sum << "\n";
                std::cout << "  Mean: " << mean << "\n";
                std::cout << "  Median: " << median << "\n";
                std::cout << "  Min: " << numeric_values.front() << "\n";
                std::cout << "  Max: " << numeric_values.back() << "\n";
            }
            
            // Save to file if specified
            if (!config.output_file.empty()) {
                save_summary_to_file(results, config, numeric_values, non_numeric_count);
            }
        }
        
    private:
        void save_summary_to_file(const std::unordered_map<ReduceKey, ReduceValue>& results,
                                const MapReduceConfig& config,
                                const std::vector<double>& numeric_values,
                                int non_numeric_count) {
            std::ofstream file(config.output_file);
            if (!file.is_open()) {
                std::cerr << "Error: Could not open output file: " << config.output_file << "\n";
                return;
            }
            
            file << "# MapReduce Statistical Summary\n";
            file << "# Generated by General Purpose MapReduce Framework\n\n";
            file << "Total unique keys: " << results.size() << "\n";
            file << "Numeric values: " << numeric_values.size() << "\n";
            file << "Non-numeric values: " << non_numeric_count << "\n\n";
            
            if (!numeric_values.empty()) {
                double sum = std::accumulate(numeric_values.begin(), numeric_values.end(), 0.0);
                double mean = sum / numeric_values.size();
                
                file << "Numeric Statistics:\n";
                file << "Sum: " << sum << "\n";
                file << "Mean: " << mean << "\n";
                file << "Min: " << numeric_values.front() << "\n";
                file << "Max: " << numeric_values.back() << "\n\n";
            }
            
            file << "# Detailed Results:\n";
            for (const auto& pair : results) {
                file << pair.first << " : " << pair.second << "\n";
            }
            
            file.close();
            std::cout << "Summary saved to: " << config.output_file << "\n";
        }
    };

    // ============ SPECIALIZED HANDLERS ============
    
    // Log analysis handler - specialized for log data
    class LogAnalysisHandler : public IResultHandler {
    public:
        void handle_results(const std::unordered_map<ReduceKey, ReduceValue>& results, 
                          const MapReduceConfig& config) override {
            std::cout << "\n=== LOG ANALYSIS RESULTS ===\n";
            
            // Categorize results
            std::map<std::string, int> log_levels;
            std::map<std::string, int> ip_addresses;
            std::map<std::string, std::string> other_metrics;
            
            for (const auto& pair : results) {
                if (pair.first == "ERROR" || pair.first == "WARN" || 
                    pair.first == "INFO" || pair.first == "DEBUG" || pair.first == "TRACE") {
                    try {
                        log_levels[pair.first] = std::stoi(pair.second);
                    } catch (const std::exception&) {
                        log_levels[pair.first] = 0;
                    }
                } else if (is_ip_address(pair.first)) {
                    try {
                        ip_addresses[pair.first] = std::stoi(pair.second);
                    } catch (const std::exception&) {
                        ip_addresses[pair.first] = 0;
                    }
                } else {
                    other_metrics[pair.first] = pair.second;
                }
            }
            
            // Display log levels
            if (!log_levels.empty()) {
                std::cout << "\nLog Levels:\n";
                for (const auto& pair : log_levels) {
                    std::cout << "  " << std::setw(6) << pair.first 
                              << ": " << pair.second << " occurrences\n";
                }
            }
            
            // Display top IP addresses
            if (!ip_addresses.empty()) {
                std::cout << "\nTop IP Addresses:\n";
                std::vector<std::pair<std::string, int>> sorted_ips(
                    ip_addresses.begin(), ip_addresses.end());
                std::sort(sorted_ips.begin(), sorted_ips.end(),
                    [](const auto& a, const auto& b) { return a.second > b.second; });
                
                int count = 0;
                for (const auto& pair : sorted_ips) {
                    if (count >= 5) break;
                    std::cout << "  " << std::setw(15) << pair.first 
                              << ": " << pair.second << " requests\n";
                    count++;
                }
            }
            
            // Display other metrics
            if (!other_metrics.empty()) {
                std::cout << "\nOther Metrics:\n";
                for (const auto& pair : other_metrics) {
                    std::cout << "  " << pair.first << ": " << pair.second << "\n";
                }
            }
        }
        
    private:
        bool is_ip_address(const std::string& str) {
            // Simple check for IP address pattern
            int dot_count = 0;
            for (char c : str) {
                if (c == '.') dot_count++;
                else if (!std::isdigit(c)) return false;
            }
            return dot_count == 3;
        }
    };

} // namespace MapReduceFramework
