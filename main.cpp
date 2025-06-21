#include <iostream>
#include <string>
#include <conio.h>
#include "WelcomePage.h"
#include "Login+SignUpFunctions.h"
using namespace std;

int main()
{
    AVL data;
    AVL emailTree;
    DoublyLinkedList<Post> postsLL;
back:
    int loginSize = readFromFile("Assets/loginDetails.txt", data, emailTree);
    int postsSize = readFromFile("Assets/posts.txt", postsLL);

    char ch = welcomePage();
    string email{}, password{}, username{}, fullname{}, id{};

    if (ch == 'l' || ch == 'L')
    {
        int userID = 0;
        bool check = true;
        do
        {
            system("CLS");
            if (!check)
                cout << "Incorrect password. Please try again 🙁 [Enter 0 in email and password to quit]\n";
            cout << "Enter your email: ";
            cin >> email;
            cout << "Enter your password: ";
            cin.ignore();
            getline(cin, password);
            if (email == "0" && password == "0")
            {
                break;
            }

            userID = login(email, password, emailTree);
            if (userID == 0)
                check = false;
        } while (userID == 0);

        if (userID != 0)
            mainMenu(userID, data, postsLL, postsSize);
    }
    else if (ch == 'S' || ch == 's')
    {
        system("CLS");
        int userID = signUp(data, emailTree);
        mainMenu(userID, data, postsLL, postsSize);
    }
    goto back;
    return 0;
}