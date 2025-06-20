#include <iostream>
using namespace std;

template <typename T>
struct Node
{
    T data;
    Node *prev;
    Node *next;

    Node(T d)
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
    Node<T> *head;
    Node<T> *tail;

public:
    DoublyLinkedList()
    {
        head = NULL;
        tail = NULL;
    }

    void insertAtHead(T data)
    {
        Node<T> *newNode = new Node<T>(data);
        if (head == NULL)
        {
            head = newNode;
            tail = newNode;
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
        Node<T> *newNode = new Node<T>(data);
        if (tail == NULL)
        {
            head = newNode;
            tail = newNode;
        }
        else
        {
            newNode->prev = tail;
            tail->next = newNode;
            tail = newNode;
        }
    }

    void deleteAtHead()
    {
        if (head == NULL)
        {
            cout << "List is empty!" << endl;
            return;
        }
        Node<T> *temp = head;
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
        Node<T> *temp = tail;
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

        Node<T> *temp = head;
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
        Node<T> *temp = head;
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
        Node<T> *temp = head;
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
        Node<T> *temp = head;
        while (temp != NULL)
        {
            if (index == count)
                return temp->data;
            count++;
        }
        T obj;
        return obj;
    }
};
