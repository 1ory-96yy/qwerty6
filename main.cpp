#include <iostream>

template <typename T>
class SmartPointer {
private:
    T* ptr;

public:
    explicit SmartPointer(T* p = nullptr) : ptr(p) {}

    ~SmartPointer() {
        delete ptr;
    }

    SmartPointer(const SmartPointer& other) = delete;
    SmartPointer& operator=(const SmartPointer& other) = delete;

    SmartPointer(SmartPointer&& other) noexcept {
        ptr = other.ptr;
        other.ptr = nullptr;
    }

    SmartPointer& operator=(SmartPointer&& other) noexcept {
        if (this != &other) {
            delete ptr;
            ptr = other.ptr;
            other.ptr = nullptr;
        }
        return *this;
    }

    T& operator*() const {
        return *ptr;
    }

    T* operator->() const {
        return ptr;
    }

    explicit operator bool() const {
        return ptr != nullptr;
    }

    T* get() const {
        return ptr;
    }

    void release() {
        ptr = nullptr;
    }

    void reset(T* p = nullptr) {
        delete ptr;
        ptr = p;
    }
};

int main() {
    {
        int* rawPtr = new int(42);
        SmartPointer<int> ptr1(rawPtr);
        std::cout << *ptr1 << std::endl;
    }

    {
        SmartPointer<int> ptr2(new int(10));
        SmartPointer<int> ptr3 = std::move(ptr2);
        std::cout << *ptr3 << std::endl;
    }

    {
        SmartPointer<int> ptr4;
        if (!ptr4) {
            std::cout << "Pointer is nullptr" << std::endl;
        }
    }

    return 0;
}
