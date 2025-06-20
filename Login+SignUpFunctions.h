#include <iostream>
#include <iomanip>
#include <fstream>
#include "LinkedList.h"
using namespace std;

class User;

bool isValidChar(char ch)
{
    return ((ch >= 'A' && ch <= 'Z') || (ch >= 'a' && ch <= 'z') || (ch >= '0' && ch <= '9'));
}
bool isEmailValid(string email)
{
    int countAt{};
    int atTheRateOf = -1, period = -1;
    if (!isValidChar(email[0]))
    {
        cout << "Error! 1st character of email can only be (a-z) or (0-9)" << endl;
        return false;
    }
    int i{};
    for (i = 0; email[i] != '\0'; i++)
    {
        if (email[i] == '.' && email[i + 1] == '.')
        {
            cout << "Error! Email can't have consecutive periods (.)" << endl;
            return false;
        }
        if (email[i] == '.')
        {
            period = i;
        }
        if (email[i] == '@')
        {
            countAt++;
            atTheRateOf = i;
        }
        if ((email[i] == '@') && !(isValidChar(email[i - 1])) && !(isValidChar(email[i + 1])))
        {
            cout << "Invalid Format! Please try (example@gmail.com)" << endl;
            return false;
        }
    }
    if (countAt != 1)
    {
        cout << "Error! Email address must have only one '@'" << endl;
        return false;
    }
    if ((atTheRateOf > period) || (period == -1 || atTheRateOf == -1))
    {
        cout << "Invalid Format! Please try (example@gmail.com)" << endl;
        return false;
    }
    if (period >= i - 1)
    {
        cout << "Last character of email can't be period (.)" << endl;
        return false;
    }
    return true;
}

bool containsSpace(string arr)
{
    for (int i = 0; arr[i] != '\0'; i++)
    {
        if (arr[i] == ' ')
        {
            return false;
        }
    }
    return true;
}
bool checkPass(string pass)
{
    if (pass.length() < 8)
    {
        return false;
    }
    return true;
}
void writeToFile(string filename, int id, string arr, string arr2, string arr3, string arr4)
{
    fstream fout(filename, ios::app);
    if (!fout)
    {
        ofstream file(filename);
        file.close();
        fout.open(filename, ios::app);
    }
    if (fout.is_open())
    {
        fout << id << " " << arr << " " << arr2 << " " << arr3 << " " << arr4 << "\n";
    }
}

void validate(string toBeChanged, string &arr)
{
    while (!containsSpace(arr))
    {
        cout << "    " << toBeChanged << " can't have space" << endl;
        {
            cout << "    " << "Enter another " << toBeChanged << ": ";
            cin >> arr;
        }
    }
}

bool isSame(string arr1, string arr2)
{
    if (arr1.length() != arr2.length())
    {
        return false;
    }
    for (int i = 0; arr1[i] != '\0' || arr2[i] != '\0'; i++)
    {
        if (arr1[i] != arr2[i])
        {
            return false;
        }
    }
    return true;
}

class User
{
    int id;
    string email;
    string username;
    string password;
    string fullname;

public:
    User()
    {
        email = username = password = fullname = "";
    }
    User(int i, string e, string u, string p, string f)
    {
        id = i;
        email = e;
        username = u;
        password = p;
        fullname = f;
    }
    void setID(int i)
    {
        id = i;
    }
    void setEmail(string e)
    {
        email = e;
    }
    void setUsername(string u)
    {
        username = u;
    }
    void setFullname(string f)
    {
        fullname = f;
    }
    void setPassword(string p)
    {
        password = p;
    }
    int getID()
    {
        return id;
    }
    string getEmail()
    {
        return email;
    }
    string getUsername()
    {
        return username;
    }
    string getFullname()
    {
        return fullname;
    }
    string getPassword()
    {
        return password;
    }
};

int readFromFile(string filename, DoublyLinkedList<User> &data)
{
    fstream fin(filename, ios::in);
    int i = 0;
    int id{};
    string email{};
    string username{};
    string password{};
    string fullname{};
    if (fin.is_open())
    {
        while (fin >> id)
        {
            fin >> email;
            fin >> username;
            fin >> password;
            fin >> fullname;
            data.insertAtHead(User(id, email, username, password, fullname));
            i++;
        }
    }
    fin.close();
    return i;
}

int login(string email, string password, DoublyLinkedList<User> data)
{
    for (int i = 0; i < data.size(); i++)
    {
        if (isSame(email, data[i].getEmail()) && isSame(password, data[i].getPassword()))
        {
            return data[i].getID();
        }
    }
    return 0;
}

bool isAlreadyExist(string toBeChanged, DoublyLinkedList<User> data, string &arr, int choice)
{
    bool cond = false;
    int s = 0;
    while (s < data.size())
    {
        if (choice == 0)
        {
            validate("Username", arr);
            while (isSame(data[s].getUsername(), arr))
            {
                cout << toBeChanged << " already in use" << endl;
                cout << "Please enter another " << toBeChanged << ": ";
                cin >> arr;
            }
            cond = true;
        }
        if (choice == 1)
        {
            validate("Email", arr);
            while (!isEmailValid(arr))
            {
                cout << "Please enter another " << toBeChanged << ": ";
                cin >> arr;
            }
            while (isSame(data[s].getEmail(), arr))
            {
                cout << toBeChanged << " already in use" << endl;
                cout << "Please enter another " << toBeChanged << ": ";
                cin >> arr;
            }
            cond = true;
        }
        s++;
    }
    return cond;
}

int signUp(DoublyLinkedList<User> &data)
{
    string email{}, password{}, username{}, fullname{};
    int id{};
    cout << "Enter email: ";
    cin >> email;
    while (!isEmailValid(email))
    {
        cout << "Email Invalid!\n";
        cout << "Enter email: ";
        cin >> email;
        validate("Email", email);
    }
    while (!isAlreadyExist("Email", data, email, 1))
        ;
    cout << "Enter username: ";
    cin >> username;
    validate("Useername", username);
    while (!isAlreadyExist("Username", data, username, 0))
        ;
    cout << "Enter password: ";
    cin >> password;
    while (!checkPass(password))
    {
        cout << "Password can't be less than 8 characters!\n";
        cout << "Enter password: ";
        cin >> password;
    }
    cout << "Enter Full Name: ";
    cin >> fullname;
    data.insertAtTail(User(data.size() + 1, email, username, password, fullname));
    writeToFile("loginDetails.txt", data.size(), email, username, password, fullname);
    return data.size();
}
