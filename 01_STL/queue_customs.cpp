#include <iostream>
#include <queue>
#include <tuple>
#include <utility> // For std::pair

// Templated function to print a queue of pairs
template <typename T1, typename T2>
void printQueue(std::queue<std::pair<T1, T2>> q) {
    while (!q.empty()) {
        std::pair<T1, T2> p = q.front();
        std::cout << "(" << p.first << ", " << p.second << ") ";
        q.pop();
    }
    std::cout << std::endl;
}

// Templated function to print a queue of tuples
template <typename... Args>
void printQueue(std::queue<std::tuple<Args...>> q) {
    while (!q.empty()) {
        std::tuple<Args...> t = q.front();
        std::apply([](Args... args) {
            std::cout << "(";
            ((std::cout << args << ", "), ...);
            std::cout << ") ";
        }, t);
        q.pop();
    }
    std::cout << std::endl;
}

int main() {
    // Queue with pairs
    std::queue<std::pair<int, int>> q_pair;

    // Adding elements
    q_pair.push({10, 20});
    q_pair.push({30, 40});
    q_pair.push({50, 60});

    // Accessing front and back
    std::cout << "Pair Queue Front: (" << q_pair.front().first << ", " << q_pair.front().second << ")" << std::endl; // Output: (10, 20)
    std::cout << "Pair Queue Back: (" << q_pair.back().first << ", " << q_pair.back().second << ")" << std::endl;   // Output: (50, 60)

    // Modifying front and back
    q_pair.front().first += 1;  // Front first element becomes 11
    q_pair.back().second -= 5;   // Back second element becomes 55

    std::cout << "Modified Pair Queue: ";
    printQueue(q_pair); // Output: (11, 20) (30, 40) (50, 55)

    // Removing elements
    q_pair.pop(); // Removes (11, 20); Queue now contains (30, 40), (50, 55)

    // Checking size and emptiness
    std::cout << "Pair Queue Size: " << q_pair.size() << std::endl;   // Output: 2
    std::cout << "Pair Queue Is Empty: " << (q_pair.empty() ? "Yes" : "No") << std::endl; // Output: No

    // Swapping queues
    std::queue<std::pair<int, int>> q_pair2;
    q_pair2.push({100, 200});
    q_pair2.push({300, 400});

    q_pair.swap(q_pair2);

    std::cout << "After swap, Pair Queue Front: (" << q_pair.front().first << ", " << q_pair.front().second << ")" << std::endl; // Output: (100, 200)
    std::cout << "After swap, Pair Queue 2 Front: (" << q_pair2.front().first << ", " << q_pair2.front().second << ")" << std::endl; // Output: (30, 40)

    // Queue with tuples
    std::queue<std::tuple<int, std::string, double>> q_tuple;

    // Adding elements
    q_tuple.push(std::make_tuple(1, "Hello", 3.14));
    q_tuple.push(std::make_tuple(2, "World", 2.71));

    // Accessing front and back
    auto front_tuple = q_tuple.front();
    auto back_tuple = q_tuple.back();

    std::cout << "Tuple Queue Front: (" << std::get<0>(front_tuple) << ", " << std::get<1>(front_tuple) << ", " << std::get<2>(front_tuple) << ")" << std::endl; // Output: (1, Hello, 3.14)
    std::cout << "Tuple Queue Back: (" << std::get<0>(back_tuple) << ", " << std::get<1>(back_tuple) << ", " << std::get<2>(back_tuple) << ")" << std::endl;   // Output: (2, World, 2.71)

    // Modifying front and back
    std::get<0>(q_tuple.front()) += 10;  // Modify the first element of the front tuple
    std::get<2>(q_tuple.back()) -= 0.71; // Modify the third element of the back tuple

    std::cout << "Modified Tuple Queue: ";
    printQueue(q_tuple); // Output: (11, Hello, 3.14) (2, World, 2.00)

    return 0;
}
