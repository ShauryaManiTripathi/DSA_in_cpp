#include <iostream>
#include <list>
#include <utility>
#include <tuple>
#include <string>
#include <algorithm>

// Print functions (same as before)
void printIntList(const std::list<int>& lst, const std::string& name) {
    std::cout << name << ": ";
    for (const auto& item : lst) {
        std::cout << item << " ";
    }
    std::cout << std::endl;
}

void printPairList(const std::list<std::pair<int, std::string>>& lst, const std::string& name) {
    std::cout << name << ": ";  
    for (const auto& item : lst) {
        std::cout << "(" << item.first << "," << item.second << ") ";
    }
    std::cout << std::endl;
}

void printTupleList(const std::list<std::tuple<int, double, char>>& lst, const std::string& name) {
    std::cout << name << ": ";
    for (const auto& item : lst) {
        std::cout << "(" << std::get<0>(item) << "," << std::get<1>(item) << "," << std::get<2>(item) << ") ";
    }
    std::cout << std::endl;
}

int main() {
    // Demonstrating methods for std::list<int>
    std::list<int> List1; // Default constructor

    std::list<int> List2(5); // Constructs a list with 5 default-initialized elements

    std::list<int> List3(5, 10); // Constructs a list with 5 elements, each initialized to 10

    std::list<int> List4(List3); // Copy constructor

    std::list<int> List5(List3.begin(),List3.end()); // Constructs a list with elements from a range

    std::initializer_list<int> List = {1, 2, 3, 4, 5};
    std::list<int> List6(List); // Constructs a list with elements from an initializer list
    
    std::list<int> intList = {3, 1, 4, 1, 5, 9, 2, 6, 5};
    printIntList(intList, "Original intList");

    // Element access
    std::cout << "Front: " << intList.front() << ", Back: " << intList.back() << std::endl;

    // Capacity
    std::cout << "Size: " << intList.size() << ", Max size: " << intList.max_size() << ", Empty: " << intList.empty() << std::endl;

    // Modifiers
    intList.push_front(0);// O(1)
    intList.push_back(10);// O(1)
    printIntList(intList, "After push_front and push_back");

    intList.pop_front();
    intList.pop_back();
    printIntList(intList, "After pop_front and pop_back");

    auto it = std::find(intList.begin(), intList.end(), 4);
    intList.insert(it, 100);// O(n) - worst case, O(1) at ends
    printIntList(intList, "After insert");

    it = std::find(intList.begin(), intList.end(), 5);
    intList.erase(it);// O(n) - worst case, O(1) at ends
    printIntList(intList, "After erase");

    intList.resize(5);// O(n) if shrinking, O(1) if growing
    printIntList(intList, "After resize to 5");

    intList.clear(); // O(n)
    std::cout << "After clear, size: " << intList.size() << std::endl;

    // Operations
    std::list<int> intList2 = {1, 2, 3, 4, 5};
    intList.splice(intList.begin(), intList2);
    printIntList(intList, "After splice");

    intList.remove(3);
    printIntList(intList, "After remove 3");

    intList.remove_if([](int n) { return n % 2 == 0; });
    printIntList(intList, "After remove_if (remove even numbers)");

    intList = {1, 2, 2, 3, 3, 3, 4, 5, 5};
    intList.unique();
    printIntList(intList, "After unique");

    intList.sort();
    printIntList(intList, "After sort");

    intList.reverse();
    printIntList(intList, "After reverse");

    // Demonstrating methods for std::list<std::pair<int, std::string>>
    std::list<std::pair<int, std::string>> pairList = {{1, "one"}, {2, "two"}, {3, "three"}};
    printPairList(pairList, "Original pairList");

    pairList.emplace_front(0, "zero");
    pairList.emplace_back(4, "four");
    printPairList(pairList, "After emplace_front and emplace_back");

    pairList.sort([](const auto& a, const auto& b) { return a.first > b.first; });
    printPairList(pairList, "After sort (descending order)");

    // Demonstrating methods for std::list<std::tuple<int, double, char>>
    std::list<std::tuple<int, double, char>> tupleList = {{1, 1.1, 'a'}, {2, 2.2, 'b'}, {3, 3.3, 'c'}};
    printTupleList(tupleList, "Original tupleList");

    tupleList.emplace(tupleList.begin(), 0, 0.0, 'z');
    printTupleList(tupleList, "After emplace at beginning");

    tupleList.assign(3, std::make_tuple(5, 5.5, 'e'));
    printTupleList(tupleList, "After assign");

    std::list<std::tuple<int, double, char>> tupleList2 = {{9, 9.9, 'x'}, {8, 8.8, 'y'}};
    tupleList.swap(tupleList2);
    printTupleList(tupleList, "After swap with tupleList2");

    return 0;
}