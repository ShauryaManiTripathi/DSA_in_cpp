#include <iostream>
#include <stack>
#include <utility>
#include <tuple>
#include <string>
#include <vector>

// Print functions
template<typename T>
void printStack(std::stack<T> s, const std::string& name) {
    std::cout << name << " (top to bottom): ";
    while (!s.empty()) {
        std::cout << s.top() << " ";
        s.pop();
    }
    std::cout << std::endl;
}

void printPairStack(std::stack<std::pair<int, std::string>> s, const std::string& name) {
    std::cout << name << " (top to bottom): ";
    while (!s.empty()) {
        std::cout << "(" << s.top().first << "," << s.top().second << ") ";
        s.pop();
    }
    std::cout << std::endl;
}

void printTupleStack(std::stack<std::tuple<int, double, char>> s, const std::string& name) {
    std::cout << name << " (top to bottom): ";
    while (!s.empty()) {
        std::cout << "(" << std::get<0>(s.top()) << "," << std::get<1>(s.top()) << "," << std::get<2>(s.top()) << ") ";
        s.pop();
    }
    std::cout << std::endl;
}

template<typename T>
void demonstrateStackOperations(std::stack<T>& s, const std::string& typeName) {
    std::cout << "\n--- Demonstrating operations for std::stack<" << typeName << "> ---\n";
    
    // Print original stack
    printStack(s, "Original stack");

    // Element access
    std::cout << "Top: " << s.top() << std::endl;

    // Capacity
    std::cout << "Size: " << s.size() << ", Empty: " << s.empty() << std::endl;

    // Modifiers
    s.push(s.top());
    printStack(s, "After push");

    s.pop();
    printStack(s, "After pop");

    s.emplace(T());  // Emplace a default-constructed element
    printStack(s, "After emplace");

    // Clear the stack
    while (!s.empty()) {
        s.pop();
    }
    std::cout << "After clear, size: " << s.size() << std::endl;
}

int main() {
    // Demonstrate operations for std::stack<int>
    std::stack<int> intStack;
    intStack.push(3);
    intStack.push(1);
    intStack.push(4);
    intStack.push(1);
    intStack.push(5);
    demonstrateStackOperations(intStack, "int");

    // Demonstrate operations for std::stack<std::pair<int, std::string>>
    std::stack<std::pair<int, std::string>> pairStack;
    pairStack.push({1, "one"});
    pairStack.push({2, "two"});
    pairStack.push({3, "three"});
    
    std::cout << "\n--- Demonstrating operations for std::stack<std::pair<int, std::string>> ---\n";
    
    printPairStack(pairStack, "Original pairStack");

    std::cout << "Top: (" << pairStack.top().first << "," << pairStack.top().second << ")" << std::endl;

    std::cout << "Size: " << pairStack.size() << ", Empty: " << pairStack.empty() << std::endl;

    pairStack.push({4, "four"});
    printPairStack(pairStack, "After push");

    pairStack.pop();
    printPairStack(pairStack, "After pop");

    pairStack.emplace(5, "five");
    printPairStack(pairStack, "After emplace");

    while (!pairStack.empty()) {
        pairStack.pop();
    }
    std::cout << "After clear, size: " << pairStack.size() << std::endl;

    // Demonstrate operations for std::stack<std::tuple<int, double, char>>
    std::stack<std::tuple<int, double, char>> tupleStack;
    tupleStack.push({1, 1.1, 'a'});
    tupleStack.push({2, 2.2, 'b'});
    tupleStack.push({3, 3.3, 'c'});
    
    std::cout << "\n--- Demonstrating operations for std::stack<std::tuple<int, double, char>> ---\n";
    
    printTupleStack(tupleStack, "Original tupleStack");

    std::cout << "Top: (" << std::get<0>(tupleStack.top()) << "," 
              << std::get<1>(tupleStack.top()) << "," 
              << std::get<2>(tupleStack.top()) << ")" << std::endl;

    std::cout << "Size: " << tupleStack.size() << ", Empty: " << tupleStack.empty() << std::endl;

    tupleStack.push({4, 4.4, 'd'});
    printTupleStack(tupleStack, "After push");

    tupleStack.pop();
    printTupleStack(tupleStack, "After pop");

    tupleStack.emplace(5, 5.5, 'e');
    printTupleStack(tupleStack, "After emplace");

    while (!tupleStack.empty()) {
        tupleStack.pop();
    }
    std::cout << "After clear, size: " << tupleStack.size() << std::endl;

    // Demonstrate stack with different underlying container
    std::stack<int, std::vector<int>> vectorStack;
    vectorStack.push(1);
    vectorStack.push(2);
    vectorStack.push(3);

    // Demonstrate stack operations
    std::stack<int> stack1, stack2;
    stack1.push(1);
    stack1.push(2);
    stack2.push(3);
    stack2.push(4);
    
    std::cout << "\n--- Demonstrating stack operations ---\n";
    printStack(stack1, "stack1 before swap");
    printStack(stack2, "stack2 before swap");
    
    stack1.swap(stack2);
    
    printStack(stack1, "stack1 after swap");
    printStack(stack2, "stack2 after swap");

    return 0;
}