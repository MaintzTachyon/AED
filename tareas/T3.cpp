#include <cstddef>
#include <initializer_list>
#include <iostream>
#include <utility>

template<typename T>
class Vector {
    T* data_ = nullptr;
    std::size_t size_ = 0;
    std::size_t capacity_ = 0;

    void grow() {
        if (size_ < capacity_) return;

        const std::size_t new_capacity = capacity_ == 0 ? 1 : capacity_ * 2;
        T* new_data = new T[new_capacity];

        for (std::size_t index = 0; index < size_; ++index) {
            new_data[index] = data_[index];
        }

        delete[] data_;
        data_ = new_data;
        capacity_ = new_capacity;
    }

public:
    using iterator = T*;
    using const_iterator = const T*;

    Vector() = default;

    explicit Vector(std::size_t count)
        : data_(count == 0 ? nullptr : new T[count]),
          size_(count),
          capacity_(count) {}

    Vector(std::initializer_list<T> values) {
        for (const T& value : values) push_back(value);
    }

    Vector(const Vector& other)
        : data_(other.capacity_ == 0 ? nullptr : new T[other.capacity_]),
          size_(other.size_),
          capacity_(other.capacity_) {
        for (std::size_t index = 0; index < size_; ++index) {
            data_[index] = other.data_[index];
        }
    }

    Vector& operator=(const Vector& other) {
        if (this == &other) return *this;

        Vector copy(other);
        swap(copy);
        return *this;
    }

    ~Vector() {
        delete[] data_;
    }

    void push_back(const T& value) {
        grow();
        data_[size_] = value;
        ++size_;
    }

    void pop_back() {
        if (size_ > 0) --size_;
    }

    T& operator[](std::size_t index) { return data_[index]; }
    const T& operator[](std::size_t index) const { return data_[index]; }

    T& front() { return data_[0]; }
    const T& front() const { return data_[0]; }
    T& back() { return data_[size_ - 1]; }
    const T& back() const { return data_[size_ - 1]; }

    std::size_t size() const { return size_; }
    std::size_t capacity() const { return capacity_; }
    bool empty() const { return size_ == 0; }

    iterator begin() { return data_; }
    const_iterator begin() const { return data_; }
    iterator end() { return data_ + size_; }
    const_iterator end() const { return data_ + size_; }

    void clear() { size_ = 0; }

    void swap(Vector& other) noexcept {
        std::swap(data_, other.data_);
        std::swap(size_, other.size_);
        std::swap(capacity_, other.capacity_);
    }
};

int main() {
    Vector<int> values = {1, 2, 3};

    std::cout << "Vector inicial: ";
    for (int value : values) std::cout << value << ' ';
    std::cout << "\nTamano: " << values.size()
              << "\nCapacidad: " << values.capacity() << '\n';

    values.push_back(4);
    values.push_back(5);
    values.push_back(6);

    std::cout << "\nDespues de agregar 4, 5 y 6:\n";
    std::cout << "Elemento en indice 2: " << values[2] << '\n';
    std::cout << "Primer elemento: " << values.front() << '\n';
    std::cout << "Ultimo elemento: " << values.back() << '\n';
    std::cout << "Tamano: " << values.size()
              << "\nCapacidad: " << values.capacity() << '\n';

    Vector<int> copy = values;
    copy[0] = 100;

    std::cout << "\nCopia modificada: ";
    for (int value : copy) std::cout << value << ' ';
    std::cout << "\nVector original: ";
    for (int value : values) std::cout << value << ' ';

    values.pop_back();
    std::cout << "\n\nDespues de pop_back(): ";
    for (int value : values) std::cout << value << ' ';
    std::cout << "\nTamano final: " << values.size() << '\n';

    return 0;
}
