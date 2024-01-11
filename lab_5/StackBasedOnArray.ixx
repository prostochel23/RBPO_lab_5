module;

#include <iostream>
using namespace std;

export module dynamic_structure: StackBasedOnArray;

import :AbstractClass;
export namespace dynamic_structure
{
    template <typename T>
    class StackBasedOnArray : public AbstractClass<T> {
        T* elements;
        const int capacity=150;
        int top;
        int size;

    public:
        int GetSize() const override {
            return size;
        };
        void clear() {
            delete[] elements;
            top = -1;
            size = 0;
        }
        bool Push(const T& element) override {
            if (size < capacity) {
                T* newelements = new T[capacity * 2];
                for (int i = 0; i < size; i++) {
                    newelements[i] = elements[i];
                }
                delete[] elements;
                elements = newelements;
            }
            top++;
            elements[top] = element;
            size++;
            return true;
        }
        bool Pop(T& element) override {
            if (size == 0) {
                return false;
            }
            element = elements[top];
            top--;
            size--;
            return true;
        }
        bool Peek(T& element) const override {
            if (size == 0) {
                return false;
            }
            element = elements[top];
            return true;
        }
        StackBasedOnArray() : elements(nullptr), top(-1), size(0) {}
        StackBasedOnArray(const StackBasedOnArray<T>& other) : elements(nullptr), top(-1), size(0) {
            *this = other;
        }
        StackBasedOnArray(StackBasedOnArray<T>&& other) : elements(nullptr), top(-1), size(0) {
            *this = std::move(other);
        }
        StackBasedOnArray(initializer_list<T> ilist) : elements(nullptr), top(-1), size(0) {
            *this = ilist;
        }
        ~StackBasedOnArray() override {
            clear(); 
        }
        StackBasedOnArray<T>& operator=(const StackBasedOnArray<T>& other) {
            if (this != &other) {
                clear();
                if (other.size > 0) {
                    elements = new T[other.size];
                    for (int i = 0; i < other.size; i++) {
                        elements[i] = other.elements[i];
                    }
                    top = other.top;
                    size = other.size;
                }
            }
            return *this;
        }
        StackBasedOnArray<T>& operator=(StackBasedOnArray<T>&& other) {
            if (this != &other) {
                clear();
                elements = other.elements;
                top = other.top;
                size = other.size;
                other.elements = nullptr;
                other.top = -1;
                other.size = 0;
            }
            return *this;
        }
        StackBasedOnArray<T>& operator=(initializer_list<T> ilist) {
            clear(); 
            elements = new T[ilist.size()];
            for (const T& element : ilist) {
                push(element);
            }
            return *this;
        }
        friend std::ostream& operator<<(std::ostream& os, const StackBasedOnArray<T>& stack) {
            for (int i = stack.top; i >= 0; i--) {
                os << stack.elements[i] << " ";
            }
            return os;
        }
    };

}