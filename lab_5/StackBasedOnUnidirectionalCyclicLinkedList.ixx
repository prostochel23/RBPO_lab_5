module;
#include <iostream>
#include <new>
export module dynamic_structure: StackBasedOnUnidirectionalCyclicLinkedList;
using namespace std;

import :AbstractClass;
export namespace dynamic_structure
    {
        template <typename T>
        class StackBasedOnUnidirectionalCyclicLinkedList : public AbstractClass<T> {
            template <typename T>
            class Node {
            public:
                T data;
                Node* next;

                Node(T data = T(), Node* next = nullptr)
                    : data(data), next(next) {}
            };

            Node<T>* head; // дно
            Node<T>* top;  // вершина стека
            int size;

        public:

            int GetSize() const override {
                return size;
            };
            void clear();
            bool Push(const T& element) override;
            bool Pop(T& element) override;
            bool Peek(T& element) const override;
            StackBasedOnUnidirectionalCyclicLinkedList();
            StackBasedOnUnidirectionalCyclicLinkedList(const StackBasedOnUnidirectionalCyclicLinkedList<T>& other);
            StackBasedOnUnidirectionalCyclicLinkedList(StackBasedOnUnidirectionalCyclicLinkedList<T>&& other);
            StackBasedOnUnidirectionalCyclicLinkedList(std::initializer_list<T> ilist);
            ~StackBasedOnUnidirectionalCyclicLinkedList() override;
            StackBasedOnUnidirectionalCyclicLinkedList<T>& operator=(const StackBasedOnUnidirectionalCyclicLinkedList<T>& other);
            StackBasedOnUnidirectionalCyclicLinkedList<T>& operator=(StackBasedOnUnidirectionalCyclicLinkedList<T>&& other);
            StackBasedOnUnidirectionalCyclicLinkedList<T>& operator=(initializer_list<T> ilist);
            friend std::ostream& operator<<(std::ostream& os, const StackBasedOnUnidirectionalCyclicLinkedList<T>& stack);
        };

        template<typename T>
        StackBasedOnUnidirectionalCyclicLinkedList<T>::StackBasedOnUnidirectionalCyclicLinkedList() : head(nullptr), top(nullptr), size(0) {}

        template <typename T>
        StackBasedOnUnidirectionalCyclicLinkedList<T>::StackBasedOnUnidirectionalCyclicLinkedList(const StackBasedOnUnidirectionalCyclicLinkedList<T>& other) : head(nullptr), top(nullptr), size(0) {
            *this = other; 
        }
        template <typename T>
        StackBasedOnUnidirectionalCyclicLinkedList<T>::StackBasedOnUnidirectionalCyclicLinkedList(StackBasedOnUnidirectionalCyclicLinkedList<T>&& other) : head(nullptr), top(nullptr), size(0) {
            *this = std::move(other); 
        }
        template <typename T>
        StackBasedOnUnidirectionalCyclicLinkedList<T>::StackBasedOnUnidirectionalCyclicLinkedList(std::initializer_list<T> ilist) : head(nullptr), top(nullptr), size(0) {
            *this = ilist;
        }
        template<typename T>
        StackBasedOnUnidirectionalCyclicLinkedList<T>::~StackBasedOnUnidirectionalCyclicLinkedList() {
            clear();
        }
        template<typename T>
        StackBasedOnUnidirectionalCyclicLinkedList<T>& StackBasedOnUnidirectionalCyclicLinkedList<T>::operator=(const StackBasedOnUnidirectionalCyclicLinkedList<T>& other) {
            if (this != &other) {
                clear();
                top = other.top;
                size = other.size;
                other.top = nullptr;
                other.size = 0;
            }

            return *this;
        }
        template<typename T>
        StackBasedOnUnidirectionalCyclicLinkedList<T>& StackBasedOnUnidirectionalCyclicLinkedList<T>::operator=(StackBasedOnUnidirectionalCyclicLinkedList<T>&& other) {
            if (this != &other) { 
                clear(); 
                head = other.head;
                top = other.top;
                size = other.size;
                other.head = nullptr;
                other.top = nullptr;
                other.size = 0;
            }

            return *this;
        }
        template<typename T>
        StackBasedOnUnidirectionalCyclicLinkedList<T>& StackBasedOnUnidirectionalCyclicLinkedList<T>::operator=(initializer_list<T> ilist) {
            clear(); 
            for (const T& item : ilist) {
                Push(item);
            }
            return *this;
        }
        template <typename T>
        std::ostream& operator<<(std::ostream& os, const StackBasedOnUnidirectionalCyclicLinkedList<T>& stack) {
            typename StackBasedOnUnidirectionalCyclicLinkedList<T>::Node* current = stack.head;
            os << "[";
            while (current != nullptr) {
                os << current->data;
                current = current->next;
                if (current != nullptr) {
                    os << ", ";
                }
            }
            os << "]";

            return os;
        }
        template<typename T>
        void StackBasedOnUnidirectionalCyclicLinkedList<T>::clear() {
            Node<T>* currentNode = head;
            while (currentNode != nullptr) {
                Node<T>* nextNode = currentNode->next; 
                delete currentNode; 
                currentNode = nextNode;
            }
            top = nullptr;
            size = 0; 
        }
        template<typename T>
        bool StackBasedOnUnidirectionalCyclicLinkedList<T>::Push(const T& element) {
            Node<T>* newNode = new(std::nothrow) Node<T>(element);
            if (newNode == nullptr) {
                return false;
            }
            if (head == nullptr) {
                head = newNode;
            }
            else {
                top->next = newNode;
            }
            top = newNode;
            ++size;
            return true;
        }
        template<typename T>
        bool StackBasedOnUnidirectionalCyclicLinkedList<T>::Pop(T& element) {
            if (head == nullptr) {
                return false;
            }
            element = top->data;
            Node<T>* toDelete = top;
            if (head == top) {
                head = nullptr;
                top = nullptr;
            }
            else {
                Node<T>* currentNode = head;
                while (currentNode->next != top) {
                    currentNode = currentNode->next;
                }
                currentNode->next = nullptr;
                top = currentNode; 
            }
            delete toDelete;  
            --size;          
            return true;
        }
        template<typename T>
        bool StackBasedOnUnidirectionalCyclicLinkedList<T>::Peek(T& element) const {
            if (head == nullptr) {
                return false;
            }
            element = top->data;
            return true;
        }
    }