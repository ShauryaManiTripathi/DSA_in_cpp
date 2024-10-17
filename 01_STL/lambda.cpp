#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>
#include <memory>

// A simple class to demonstrate capture of this
class Multiplier {
private:
    int factor;

public:
    Multiplier(int f) : factor(f) {}

    // Demonstrates capturing this and mutable lambda
    auto getMultiplierClosure() {
        return [this](int x) mutable {
            factor++;
            return x * factor;
        };
    }

    // Demonstrates capturing *this (C++17)
    auto getMultiplierClosureByValue() {
        return [*this](int x) mutable {
            factor++;
            return x * factor;
        };
    }
};

int main() {
    // Basic lambda with capture
    int base = 10;
    auto adder = [base](int x) { return base + x; };
    std::cout << "Adder result: " << adder(5) << std::endl;

    // Mutable lambda
    auto counter = [count = 0]() mutable { return ++count; };
    std::cout << "Counter: " << counter() << ", " << counter() << std::endl;

    // Polymorphic lambda (C++14)
    auto multiplier = [](auto a, auto b) { return a * b; };
    std::cout << "Multiply int: " << multiplier(5, 3) << std::endl;
    std::cout << "Multiply double: " << multiplier(3.14, 2.0) << std::endl;

    // Lambda with capture by reference
    int value = 100;
    auto modifier = [&value]() { value *= 2; };
    modifier();
    std::cout << "Modified value: " << value << std::endl;

    // Using lambda with standard algorithms
    std::vector<int> numbers = {1, 2, 3, 4, 5};
    std::transform(numbers.begin(), numbers.end(), numbers.begin(),
                   [](int n) { return n * n; });
    std::cout << "Squared numbers: ";
    for (int n : numbers) std::cout << n << " ";
    std::cout << std::endl;

    // Lambda returning another lambda
    auto create_adder = [](int base) {
        return [base](int x) { return base + x; };
    };
    auto add5 = create_adder(5);
    std::cout << "Add 5 to 10: " << add5(10) << std::endl;

    // Using lambda with bind and placeholders
    using namespace std::placeholders;
    auto bound_multiplier = std::bind(multiplier, _1, 10);
    std::cout << "Bound multiplier: " << bound_multiplier(5) << std::endl;

    // Demonstrating capture of this
    Multiplier mult(10);
    auto closure = mult.getMultiplierClosure();
    std::cout << "Multiplier closure: " << closure(5) << ", " << closure(5) << std::endl;

    // Demonstrating capture of *this (C++17)
    auto closure_by_value = mult.getMultiplierClosureByValue();
    std::cout << "Multiplier closure by value: " << closure_by_value(5) << ", " << closure_by_value(5) << std::endl;

    // Generic lambda with variadic templates (C++20)
    auto sum = []<typename... Args>(Args... args) {
        return (args + ...);
    };
    std::cout << "Sum of 1, 2, 3, 4: " << sum(1, 2, 3, 4) << std::endl;

    return 0;
}