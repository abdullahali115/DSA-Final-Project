#include <iostream>
using namespace std;

template <typename T>
struct LLNode
{
    T data;
    LLNode *prev;
    LLNode *next;

    LLNode(T d)
    {
        data = d;
        prev = NULL;
        next = NULL;
    }
};

template <typename T>
class DoublyLinkedList
{
private:
    LLNode<T> *head;
    LLNode<T> *tail;

public:
    DoublyLinkedList()
    {
        head = NULL;
        tail = NULL;
    }

    void insertAtHead(T data)
    {
        LLNode<T> *newLLNode = new LLNode<T>(data);
        if (head == NULL)
        {
            head = newLLNode;
            tail = newLLNode;
        }
        else
        {
            newLLNode->next = head;
            head->prev = newLLNode;
            head = newLLNode;
        }
    }

    void insertAtTail(T data)
    {
        LLNode<T> *newLLNode = new LLNode<T>(data);
        if (tail == NULL)
        {
            head = newLLNode;
            tail = newLLNode;
        }
        else
        {
            newLLNode->prev = tail;
            tail->next = newLLNode;
            tail = newLLNode;
        }
    }

    void deleteAtHead()
    {
        if (head == NULL)
        {
            cout << "List is empty!" << endl;
            return;
        }
        LLNode<T> *temp = head;
        if (head == tail)
        {
            head = NULL;
            tail = NULL;
        }
        else
        {
            head = head->next;
            head->prev = NULL;
        }
        delete temp;
    }

    void deleteAtTail()
    {
        if (tail == NULL)
        {
            cout << "List is empty!" << endl;
            return;
        }
        LLNode<T> *temp = tail;
        if (head == tail)
        {
            head = NULL;
            tail = NULL;
        }
        else
        {
            tail = tail->prev;
            tail->next = NULL;
        }
        delete temp;
    }
    void deleteAtIndex(int index)
    {
        if (head == NULL)
        {
            cout << "List is empty!" << endl;
            return;
        }

        if (index == 0)
        {
            deleteAtHead();
            return;
        }

        LLNode<T> *temp = head;
        int count = 0;

        while (temp != NULL && count < index)
        {
            temp = temp->next;
            count++;
        }

        if (temp == NULL)
        {
            cout << "Index out of range!" << endl;
            return;
        }

        if (temp == tail)
        {
            deleteAtTail();
            return;
        }

        temp->prev->next = temp->next;
        temp->next->prev = temp->prev;

        delete temp;
    }

    void displayForward()
    {
        LLNode<T> *temp = head;
        while (temp != NULL)
        {
            cout << temp->data << " ";
            temp = temp->next;
        }
        cout << endl;
    }
    int size()
    {
        int count{};
        LLNode<T> *temp = head;
        while (temp != NULL)
        {
            temp = temp->next;
            count++;
        }
        return count;
    }
    T operator[](int index)
    {
        int count = 0;
        LLNode<T> *temp = head;
        while (temp != NULL)
        {
            if (index == count)
                return temp->data;
            count++;
        }
        T obj;
        return obj;
    }
    T getTail()
    {
        if(tail == nullptr)
            return NULL;
        return tail->data;
    }
};
