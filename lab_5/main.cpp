import dynamic_structure;

#include <iostream>
using namespace dynamic_structure;
using namespace std;


template <typename T>
void view(AbstractClass<T>& structure, const std::initializer_list<T>& elements) {
    cout << "Add elements: ";
    for (const auto& element : elements) {
        structure.Push(element);
        cout << element << "  ";
    }
    cout << endl;

    cout << "Size: " << structure.GetSize() << endl;

    T topElement;
    if (structure.Peek(topElement)) {
        cout << "Top: " << topElement <<endl;
    }

    T popElement;
    if (structure.Pop(popElement)) {
        cout << "Pop: " << popElement << endl;
    }

    cout << "All elements: ";
    while (structure.GetSize() > 0) {
        structure.Peek(topElement);
        cout << topElement << "  ";
        structure.Pop(topElement);
    }
    cout << endl;
};


int main() {
    cout << "Demonstration of the work:" << endl<<endl;
    cout << "StackBasedOnUnidirectionalCyclicLinkedList" << endl;
    dynamic_structure::StackBasedOnUnidirectionalCyclicLinkedList<int> StackOnList;
    view(StackOnList, { 1, 2, 3, 4, 5 });

    cout << "------------------------------" << endl;

    cout << "StackBasedOnArray" << endl;
    dynamic_structure::StackBasedOnArray<int> StackOnArray;
    view(StackOnArray, { 21, 32, 43, 54, 65 });

    return 0;
}