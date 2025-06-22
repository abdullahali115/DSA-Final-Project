#include <iostream>
#include <stdexcept>
using namespace std;

template <typename T>
struct LLNode
{
    T data;
    LLNode *prev;
    LLNode *next;

    LLNode(T d) : data(d), prev(nullptr), next(nullptr) {}
};

template <typename T>
class DoublyLinkedList
{
private:
    LLNode<T> *head;
    LLNode<T> *tail;

public:
    DoublyLinkedList() : head(nullptr), tail(nullptr) {}

    ~DoublyLinkedList()
    {
        while (head != nullptr)
            deleteAtHead();
    }

    void insertAtHead(T data)
    {
        LLNode<T> *newNode = new LLNode<T>(data);
        if (!head)
        {
            head = tail = newNode;
        }
        else
        {
            newNode->next = head;
            head->prev = newNode;
            head = newNode;
        }
    }

    void insertAtTail(T data)
    {
        LLNode<T> *newNode = new LLNode<T>(data);
        if (!tail)
        {
            head = tail = newNode;
        }
        else
        {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
    }

    T deleteAtHead()
    {
        if (!head)
            throw out_of_range("Cannot delete from empty list");

        T data = head->data;
        LLNode<T> *temp = head;

        if (head == tail)
        {
            head = tail = nullptr;
        }
        else
        {
            head = head->next;
            head->prev = nullptr;
        }

        delete temp;
        return data;
    }

    T deleteAtTail()
    {
        if (!tail)
            throw out_of_range("Cannot delete from empty list");

        T data = tail->data;
        LLNode<T> *temp = tail;

        if (head == tail)
        {
            head = tail = nullptr;
        }
        else
        {
            tail = tail->prev;
            tail->next = nullptr;
        }

        delete temp;
        return data;
    }

    void deleteAtIndex(int index)
    {
        if (!head)
            throw out_of_range("List is empty");

        if (index == 0)
        {
            deleteAtHead();
            return;
        }

        LLNode<T> *temp = head;
        int count = 0;

        while (temp && count < index)
        {
            temp = temp->next;
            count++;
        }

        if (!temp)
            throw out_of_range("Index out of range");

        if (temp == tail)
        {
            deleteAtTail();
            return;
        }

        temp->prev->next = temp->next;
        temp->next->prev = temp->prev;
        delete temp;
    }

    void displayForward() const
    {
        LLNode<T> *temp = head;
        while (temp)
        {
            cout << temp->data << " ";
            temp = temp->next;
        }
        cout << endl;
    }

    int size() const
    {
        int count = 0;
        LLNode<T> *temp = head;
        while (temp)
        {
            count++;
            temp = temp->next;
        }
        return count;
    }

    T &operator[](int index)
    {
        int count = 0;
        LLNode<T> *temp = head;
        while (temp)
        {
            if (count == index)
                return temp->data;
            count++;
            temp = temp->next;
        }
        throw out_of_range("Index out of range in operator[]");
    }

    T getTail() const
    {
        if (!tail)
            throw out_of_range("Tail does not exist");
        return tail->data;
    }

    bool isEmpty() const
    {
        return head == nullptr;
    }
};
