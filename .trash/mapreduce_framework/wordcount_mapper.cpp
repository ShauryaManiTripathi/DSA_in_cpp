#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>
#include <cctype>

int main() {
    std::string line;
    
    while (std::getline(std::cin, line)) {
        // Convert to lowercase and extract words
        std::transform(line.begin(), line.end(), line.begin(), ::tolower);
        
        std::istringstream iss(line);
        std::string word;
        
        while (iss >> word) {
            // Remove punctuation
            word.erase(std::remove_if(word.begin(), word.end(), 
                      [](char c) { return std::ispunct(c); }), word.end());
            
            if (!word.empty()) {
                std::cout << word << "\t1" << std::endl;
            }
        }
    }
    
    return 0;
}
