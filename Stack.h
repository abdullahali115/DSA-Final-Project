#include <iostream>
#include "LinkedList.h"
using namespace std;

template <typename T>
class Stack
{
    DoublyLinkedList<T> data;

public:
    void push(T val)
    {
        data.insertAtHead(val);
    }
    T pop()
    {
        if (!isEmpty())
            return data.deleteAtHead();
        throw std::out_of_range("Can't delete from an empty stack\n");
    }
    bool isEmpty()
    {
        return data.isEmpty();
    }
};