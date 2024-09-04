#include <iostream>
#include <queue>

int main() {
    std::queue<int> q;

    // Adding elements
    q.push(10);
    q.push(20);
    q.push(30);

    // Accessing front and back
    std::cout << "Front: " << q.front() << std::endl; // Output: 10
    std::cout << "Back: " << q.back() << std::endl;   // Output: 30

    // Modifying front and back
    q.front() += 1;  // Front becomes 11
    q.back() -= 5;   // Back becomes 25

    std::cout << "Modified Front: " << q.front() << std::endl; // Output: 11
    std::cout << "Modified Back: " << q.back() << std::endl;   // Output: 25

    // Removing elements
    q.pop(); // Removes 11; Queue now contains 20, 25

    // Checking size and emptiness
    std::cout << "Size: " << q.size() << std::endl;   // Output: 2
    std::cout << "Is Empty: " << (q.empty() ? "Yes" : "No") << std::endl; // Output: No

    // Swapping queues
    std::queue<int> q2;
    q2.push(100);
    q2.push(200);

    q.swap(q2);

    std::cout << "After swap, Front of q: " << q.front() << std::endl; // Output: 100
    std::cout << "After swap, Front of q2: " << q2.front() << std::endl; // Output: 20

    return 0;
}
