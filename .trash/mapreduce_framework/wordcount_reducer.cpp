#include <iostream>
#include <string>
#include <sstream>

int main() {
    std::string line;
    std::string current_word;
    int current_count = 0;
    
    while (std::getline(std::cin, line)) {
        if (line.empty()) continue;
        
        std::istringstream iss(line);
        std::string word;
        int count;
        
        if (iss >> word >> count) {
            if (current_word == word) {
                current_count += count;
            } else {
                if (!current_word.empty()) {
                    std::cout << current_word << "\t" << current_count << std::endl;
                }
                current_word = word;
                current_count = count;
            }
        }
    }
    
    // Output the last word
    if (!current_word.empty()) {
        std::cout << current_word << "\t" << current_count << std::endl;
    }
    
    return 0;
}
