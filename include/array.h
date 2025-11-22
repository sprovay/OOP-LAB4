#ifndef ARRAY_H
#define ARRAY_H

#include <memory>
#include <stdexcept>
#include <iostream>

template<typename T>
class Array {
public:
    Array(unsigned int initialCapacity = 10) 
        : size(0), capacity(initialCapacity) {
        data = std::make_unique<std::shared_ptr<T>[]>(capacity);
    }

    ~Array() = default;

    void add(std::shared_ptr<T> element) {
        if (size >= capacity) {
            resize(capacity * 2);
        }
        data[size++] = element;
    }

    void remove(unsigned int index) {
        for (unsigned int i = index; i < size - 1; ++i) {
            data[i] = data[i + 1];
        }
        data[--size].reset();
    }

    std::shared_ptr<T>& operator[](unsigned int index) {
        return data[index];
    }

    const std::shared_ptr<T>& operator[](unsigned int index) const {
        return data[index];
    }

    unsigned int getSize() const { return size; }
    unsigned int getCapacity() const { return capacity; }

    double totalArea() const {
        double total = 0.0;
        for (unsigned int i = 0; i < size; ++i) {
            if (data[i]) {
                total += data[i]->area();
            }
        }
        return total;
    }

    void printAll() const {
        std::cout << std::endl;
        std::cout << "-----------------------------------------" << std::endl;
        std::cout << "===========ФИГУРЫ В МАССИВЕ==============" << std::endl;
        std::cout << "-----------------------------------------" << std::endl;
        
        for (unsigned int i = 0; i < size; ++i) {
            if (data[i]) {
                std::cout << "Фигура " << i << ": " << *data[i] << std::endl;
                
                auto center = data[i]->center();
                std::cout << "  - Центр: " << center << std::endl;
                
                double area = static_cast<double>(*data[i]);
                std::cout << "  - Площадь: " << area << std::endl;
                
                std::cout << "=========================================" << std::endl;
            }
        }
        std::cout << std::endl;
    }

    bool isEmpty() const {
        return size == 0;
    }

    void clear() {
        for (unsigned int i = 0; i < size; ++i) {
            data[i].reset();
        }
        size = 0;
    }

private:
    void resize(unsigned int newCapacity) {
        auto newData = std::make_unique<std::shared_ptr<T>[]>(newCapacity);
        for (unsigned int i = 0; i < size; ++i) {
            newData[i] = std::move(data[i]);
        }
        data = std::move(newData);
        capacity = newCapacity;
    }

    unsigned int size;
    unsigned int capacity;
    std::unique_ptr<std::shared_ptr<T>[]> data;
};

#endif