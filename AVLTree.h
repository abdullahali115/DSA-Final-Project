#include <iostream>
#include <fstream>
#include "user.h"
using namespace std;

class Node
{
public:
    User data;
    Node *left;
    Node *right;
    Node(User val)
    {
        data = val;
        left = right = nullptr;
    }
};

void ToLower(string &temp)
{
    for (int i = 0; temp[i] != '\0'; i++)
        temp[i] = tolower(temp[i]);
}
class AVL
{
    Node *root;

    int height(Node *temp)
    {
        if (temp == nullptr)
            return -1;
        return 1 + max(height(temp->left), height(temp->right));
    }
    Node *rotateRight(Node *p)
    {
        Node *c = p->left;
        Node *t = c->right;

        c->right = p;
        p->left = t;
        return c;
    }
    Node *rotateLeft(Node *p)
    {
        Node *c = p->right;
        Node *t = c->left;

        c->left = p;
        p->right = t;
        return c;
    }
    Node *rotate(Node *temp)
    {
        int leftHeight = height(temp->left);
        int rightHeight = height(temp->right);
        if (leftHeight - rightHeight > 1 || leftHeight - rightHeight < -1)
        {
            if (leftHeight > rightHeight)
            {
                // leftHeavy
                int leftSubHeight = height(temp->left->left);
                int rightSubHeight = height(temp->left->right);
                if (leftSubHeight > rightSubHeight)
                {
                    // left-left case
                    return rotateRight(temp);
                }
                else if (rightSubHeight > leftSubHeight)
                {
                    // left-Right case
                    temp->left = rotateLeft(temp->left);
                    return rotateRight(temp);
                }
            }
            else if (leftHeight < rightHeight)
            {
                // right heavy
                int leftSubHeight = height(temp->right->left);
                int rightSubHeight = height(temp->right->right);
                if (rightSubHeight > leftSubHeight)
                {
                    // right-right case
                    return rotateLeft(temp);
                }
                else if (rightSubHeight < leftSubHeight)
                {
                    // right-left case
                    temp->right = rotateRight(temp->right);
                    return rotateLeft(temp);
                }
            }
        }
        return temp;
    }
    Node *insertHelperUsername(Node *temp, User val)
    {
        if (temp == nullptr)
            return new Node(val);
        if (temp->data.getUsername() < val.getUsername())
        {
            temp->right = insertHelperUsername(temp->right, val);
        }
        if (temp->data.getUsername() > val.getUsername())
        {
            temp->left = insertHelperUsername(temp->left, val);
        }
        return rotate(temp);
    }
    Node *insertHelperEmail(Node *temp, User val)
    {
        if (temp == nullptr)
            return new Node(val);
        if (temp->data.getEmail() < val.getEmail())
        {
            temp->right = insertHelperEmail(temp->right, val);
        }
        if (temp->data.getEmail() > val.getEmail())
        {
            temp->left = insertHelperEmail(temp->left, val);
        }
        return rotate(temp);
    }
    Node *insertHelperID(Node *temp, User val)
    {
        if (temp == nullptr)
            return new Node(val);
        if (temp->data.getID() < val.getID())
        {
            temp->right = insertHelperID(temp->right, val);
        }
        if (temp->data.getID() > val.getID())
        {
            temp->left = insertHelperID(temp->left, val);
        }
        return rotate(temp);
    }
    User searchByUsername(Node *temp, string key)
    {
        if (temp == nullptr)
            return User();
        if (temp->data.getUsername() == key)
            return temp->data;
        if (temp->data.getUsername() < key)
            return searchByUsername(temp->right, key);
        return searchByUsername(temp->left, key);
    }
    User searchByEmail(Node *temp, string key)
    {
        if (temp == nullptr)
            return User();
        if (temp->data.getEmail() == key)
            return temp->data;
        if (temp->data.getEmail() < key)
            return searchByEmail(temp->right, key);
        return searchByEmail(temp->left, key);
    }
    User searchByID(Node *temp, int key)
    {
        if (temp == nullptr)
            return User();
        if (temp->data.getID() == key)
        {
            return temp->data;
        }
        if (temp->data.getID() < key)
            return searchByID(temp->right, key);
        return searchByID(temp->left, key);
    }
    int getMaxIDHelper(Node *temp)
    {
        if (temp == nullptr)
            return 0;
        if (temp->right == nullptr)
            return temp->data.getID();
        return getMaxIDHelper(temp->right);
    }
    Node *getMax(Node *temp)
    {
        if (temp == nullptr)
            return 0;
        if (temp->right == nullptr)
            return temp;
        return getMax(temp->right);
    }
    void inOrderHelper(Node *temp)
    {
        if (temp == nullptr)
            return;
        inOrderHelper(temp->left);
        cout << temp->data.getID() << " ";
        inOrderHelper(temp->right);
    }
    void inOrderSearchHelper(Node *temp, string str, string notInclude, bool &check)
    {
        if (temp == nullptr)
            return;
        inOrderSearchHelper(temp->left, str, notInclude, check);
        string tempStr = temp->data.getFullname();
        ToLower(tempStr);
        ToLower(str);
        if (tempStr.find(str) != string::npos && temp->data.getUsername() != notInclude)
        {
            check = true;
            cout << "UserID: " << temp->data.getID() << " Full Name: " << temp->data.getFullname() << " Username: " << temp->data.getUsername() << endl;
        }
        inOrderSearchHelper(temp->right, str, notInclude, check);
    }
    int sizeHelper(Node *temp)
    {
        if (temp == nullptr)
            return 0;
        return 1 + sizeHelper(temp->left) + sizeHelper(temp->right);
    }
    void updateFileHelper(ofstream &file, Node *temp)
    {
        if (temp == nullptr)
            return;
        updateFileHelper(file, temp->left);
        file << temp->data.getID() << " ";
        file << temp->data.getEmail() << " ";
        file << temp->data.getUsername() << " ";
        file << temp->data.getPassword() << " ";
        file << temp->data.getFullname() << "\n";
        updateFileHelper(file, temp->right);
    }
    Node *deleteFromBST(Node *temp, int key)
    {
        if (temp == nullptr)
            return nullptr;
        if (temp->data.getID() > key)
            temp->left = deleteFromBST(temp->left, key);
        else if (temp->data.getID() < key)
            temp->right = deleteFromBST(temp->right, key);
        else
        {
            // case 1 + 2
            if (temp->right == nullptr)
            {
                Node *temp2 = temp->left;
                delete temp;
                return temp2;
            }
            else if (temp->left == nullptr)
            {
                Node *temp2 = temp->right;
                delete temp;
                return temp2;
            }
            // case 3
            else
            {
                Node *inOrder = getMax(temp->right);
                temp->data.setID(inOrder->data.getID());
                temp->data.setEmail(inOrder->data.getEmail());
                temp->data.setUsername(inOrder->data.getUsername());
                temp->data.setPassword(inOrder->data.getPassword());
                temp->data.setFullname(inOrder->data.getFullname());
                temp->right = deleteFromBST(temp->right, inOrder->data.getID());
            }
        }
        return temp;
    }

public:
    AVL() : root(nullptr)
    {
    }
    void insertIntoUserAVL(User data)
    {
        root = insertHelperUsername(root, data);
    }
    void insertIntoEmailAVL(User data)
    {
        root = insertHelperEmail(root, data);
    }
    void insertIntoIDAVL(User data)
    {
        root = insertHelperID(root, data);
    }
    User searchByUser(string val)
    {
        return searchByUsername(root, val);
    }
    User searchUserByEmail(string val)
    {
        return searchByEmail(root, val);
    }
    User searchUserByID(int val)
    {
        return searchByID(root, val);
    }
    int getMaxID()
    {
        return getMaxIDHelper(root);
    }
    void inOrderDisplay()
    {
        inOrderHelper(root);
    }
    bool inOrderSearch(string str, string notInclude)
    {
        bool check = false;
        inOrderSearchHelper(root, str, notInclude, check);
        return check;
    }
    int size()
    {
        return sizeHelper(root);
    }
    void updateFile(string filename)
    {
        ofstream file(filename);
        if (file.is_open())
        {
            updateFileHelper(file, root);
            file.close();
        }
        return;
    }
    void deleteUser(int id)
    {
        root = deleteFromBST(root, id);
    }
};