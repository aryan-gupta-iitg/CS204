#include <iostream>

class Numbers {
private:
    int data[5] = {10, 20, 30, 40, 50};

public:
    // 1. Define the Iterator class (often nested inside the container)
    class Iterator {
    private:
        int* ptr; // Pointer to the current element

    public:
        // Constructor
        Iterator(int* p) : ptr(p) {}

        // Overload * to get the value
        int& operator*() {
            return *ptr;
        }

        // Overload ++ to move to the next element
        Iterator& operator++() {
            ptr++;
            return *this;
        }

        // Overload != to check if we've reached the end
        bool operator!=(const Iterator& other) const {
            return ptr != other.ptr;
        }
    };

    // 2. Add begin() and end() methods to the container class
    Iterator begin() {
        return Iterator(data); // Iterator starts at the beginning of our array
    }

    Iterator end() {
        return Iterator(data + 5); // Iterator ends one past the last element
    }
};

int main() {
    Numbers my_numbers;

    // Now you can use a for-each loop! 🎉
    std::cout << "My numbers are: ";
    for (int number : my_numbers) {
        std::cout << number << " ";
    }
    std::cout << std::endl;

    return 0;
}