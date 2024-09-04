#include<iostream>
#include<deque>
using namespace std;


void explainDeque() {
    deque<int>dq;
    dq.push_back(1); // {1} 
    dq.emplace_back(2); // {1, 2}
    dq.push_front(4); // {4, 1, 2}
    dq.emplace_front(3); // {3, 4, 1, 2}

    dq.pop_back(); // {3, 4, 1}
    dq.pop_front(); // {4, 1}

    dq.back();
    dq.front();

    // rest functions same as vector
    // begin, end, rbegin, rend, clear, insert, size, swap
}

/*
std::deque (double-ended queue) vs std::list:

1. Memory Layout:
   - deque: Uses multiple chunks of contiguous memory
   - list: Uses non-contiguous memory (nodes)

2. Random Access:
   - deque: O(1) random access via operator[] or at()
   - list: O(n) access to arbitrary elements

3. Insertion/Deletion:
   - deque: O(1) at both ends, O(n) in the middle
   - list: O(1) anywhere if iterator is known

4. Memory Efficiency:
   - deque: More memory-efficient for small objects
   - list: Each element has overhead for pointers

5. Iterator Invalidation:
   - deque: Only invalidates iterators if reallocated
   - list: Iterators remain valid unless that element is erased

6. Contiguous Memory:
   - deque: Elements not guaranteed to be contiguous
   - list: Elements are never contiguous

Deque is often a good default choice when you need efficient insertion/deletion at both ends
and random access, without the overhead of a list for small objects.
*/
#include <string>
#include <algorithm>

// Print functions (unchanged)
void printIntDeque(const std::deque<int>& dq, const std::string& name) {
    std::cout << name << ": ";
    for (const auto& item : dq) {
        std::cout << item << " ";
    }
    std::cout << std::endl;
}

void printStringDeque(const std::deque<std::string>& dq, const std::string& name) {
    std::cout << name << ": ";
    for (const auto& item : dq) {
        std::cout << item << " ";
    }
    std::cout << std::endl;
}

int main() {
    // Constructors
    std::deque<int> deque1;  // Default constructor - O(1)
    std::deque<int> deque2(5);  // Fill constructor - O(n)
    std::deque<int> deque3(5, 10);  // Fill constructor - O(n)
    std::deque<int> deque4(deque3);  // Copy constructor - O(n)
    std::deque<int> deque5(deque3.begin(), deque3.end());  // Range constructor - O(n)
    std::deque<int> deque6{1, 2, 3, 4, 5};  // Initializer list constructor - O(n)

    std::deque<int> intDeque = {3, 1, 4, 1, 5, 9, 2, 6, 5};  // O(n)
    printIntDeque(intDeque, "Original intDeque");

    // Element access - All O(1)
    std::cout << "Front: " << intDeque.front() << ", Back: " << intDeque.back() << std::endl;
    std::cout << "Element at index 2: " << intDeque[2] << std::endl;
    std::cout << "Element at index 3 (using at()): " << intDeque.at(3) << std::endl;

    // Capacity - All O(1)
    std::cout << "Size: " << intDeque.size() << ", Max size: " << intDeque.max_size() 
              << ", Empty: " << intDeque.empty() << std::endl;

    // Modifiers
    intDeque.push_front(0);  // O(1)
    intDeque.push_back(10);  // O(1)
    printIntDeque(intDeque, "After push_front and push_back");

    intDeque.pop_front();  // O(1)
    intDeque.pop_back();   // O(1)
    printIntDeque(intDeque, "After pop_front and pop_back");

    auto it = std::find(intDeque.begin(), intDeque.end(), 4);  // O(n)
    intDeque.insert(it, 100);  // O(n) - worst case, O(1) at ends
    printIntDeque(intDeque, "After insert");

    it = std::find(intDeque.begin(), intDeque.end(), 5);  // O(n)
    intDeque.erase(it);  // O(n) - worst case, O(1) at ends
    printIntDeque(intDeque, "After erase");

    intDeque.resize(5);  // O(n) if shrinking, O(1) if growing
    printIntDeque(intDeque, "After resize to 5");

    intDeque.clear();  // O(n)
    std::cout << "After clear, size: " << intDeque.size() << std::endl;

    // Operations
    intDeque = {1, 2, 3, 4, 5};  // O(n)
    std::reverse(intDeque.begin(), intDeque.end());  // O(n)
    printIntDeque(intDeque, "After reverse");

    std::sort(intDeque.begin(), intDeque.end());  // O(n log n)
    printIntDeque(intDeque, "After sort");

    // Demonstrating methods for std::deque<std::string>
    std::deque<std::string> stringDeque = {"apple", "banana", "cherry"};  // O(n)
    printStringDeque(stringDeque, "Original stringDeque");

    stringDeque.emplace_front("apricot");  // O(1)
    stringDeque.emplace_back("date");     // O(1)
    printStringDeque(stringDeque, "After emplace_front and emplace_back");

    stringDeque.assign(3, "fig");  // O(n)
    printStringDeque(stringDeque, "After assign");

    std::deque<std::string> stringDeque2 = {"grape", "kiwi"};  // O(n)
    stringDeque.swap(stringDeque2);  // O(1)
    printStringDeque(stringDeque, "After swap with stringDeque2");

    return 0;
}