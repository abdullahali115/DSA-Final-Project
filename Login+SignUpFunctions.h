#include <iostream>
#include <iomanip>
#include <fstream>
#include "AVLTree.h"
#include "LinkedList.h"
#include "posts.h"
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

void convertToLower(string &temp)
{
    for (int i = 0; temp[i] != '\0'; i++)
        tolower(temp[i]);
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

int readFromFile(string filename, AVL &data, AVL &emailAVL)
{
    fstream fin(filename, ios::in);
    if (!fin)
    {
        ofstream file(filename);
        file.close();
        fin.open(filename, ios::in);
    }
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
            data.insertIntoUserAVL(User(id, email, username, password, fullname));
            emailAVL.insertIntoEmailAVL(User(id, email, username, password, fullname));
            i++;
        }
    }
    fin.close();
    return i;
}
int readFromFile(string filename, DoublyLinkedList<Post> &postsLL)
{
    fstream fin(filename, ios::in);
    if (!fin)
    {
        ofstream file(filename);
        file.close();
        fin.open(filename, ios::in);
    }
    int i = 0;
    string post{};
    int userid{};
    int postid{};
    if (fin.is_open())
    {
        while (fin >> postid)
        {
            fin >> userid;
            getline(fin, post);
            postsLL.insertAtTail(Post(postid, userid, post));
            i++;
        }
    }
    fin.close();
    return i;
}
void writeToFile(string filename, int postid, int userid, string post)
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
        fout << postid << " " << userid << " " << post << "\n";
    }
}

int login(string email, string password, AVL &data)
{
    User temp = data.searchUserByEmail(email);
    if (email == temp.getEmail() && password == temp.getPassword())
        return temp.getID();
    return 0;
}
int existCheckUserName(string username, AVL &data)
{
    User temp = data.searchByUser(username);
    return temp.getID();
}
int existCheckEmail(string email, AVL &data)
{
    User temp = data.searchUserByEmail(email);
    return temp.getID();
}

bool isAlreadyExist(string toBeChanged, AVL &data, AVL &emailAVL, string &arr, int choice)
{
    bool cond = false;
    if (choice == 0)
    {
        validate("Username", arr);
        while (existCheckUserName(arr, data))
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
        while (existCheckEmail(arr, emailAVL))
        {
            cout << toBeChanged << " already in use" << endl;
            cout << "Please enter another " << toBeChanged << ": ";
            cin >> arr;
        }
        cond = true;
    }
    return cond;
}

int signUp(AVL &data, AVL &emailAVL)
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
    while (!isAlreadyExist("Email", data, emailAVL, email, 1))
        ;
    cout << "Enter username: ";
    cin >> username;
    validate("Useername", username);
    while (!isAlreadyExist("Username", data, emailAVL, username, 0))
        ;
    cout << "Enter password: ";
    cin.ignore();
    getline(cin, password);
    while (!checkPass(password))
    {
        cout << "Password can't be less than 8 characters!\n";
        cout << "Enter password: ";
        getline(cin, password);
    }
    cout << "Enter Full Name: ";
    getline(cin, fullname);
    int s = data.getMaxID();
    cout << s << endl;
    system("pause");
    convertToLower(username);
    convertToLower(email);
    data.insertIntoUserAVL(User(s + 1, email, username, password, fullname));
    data.insertIntoEmailAVL(User(s + 1, email, username, password, fullname));
    writeToFile("Assets/loginDetails.txt", s + 1, email, username, password, fullname);

    // greting

    return s + 1;
}

void mainMenu(int id, AVL &data, DoublyLinkedList<Post> &postsLL, int postSize)
{
    system("chcp 65001");
    system("CLS");
    cout << "📜 Press 'F' to view the feed\n";
    cout << "📥 Press 'I' to go to inbox\n";
    cout << "🔍 Press 'S' to search any user\n";
    cout << "✍️ Press 'C' to create a new post\n";
    cout << "👤 Press 'P' to view your profile\n";
    char choice = _getch();

    if (choice == 'C' || choice == 'c')
    {
        string post{};
        system("CLS");
        cout << "What's on your mind today?: ";
        do
        {
            getline(cin, post);
        } while (post.size() == 0);

        postsLL.insertAtTail(Post(postSize + 1, id, post));
        writeToFile("Assets/posts.txt", postSize + 1, id, post);
    }
}