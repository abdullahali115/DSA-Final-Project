#include <iostream>
#include "WelcomePage.h"
#include "Login+SignUpFunctions.h"
using namespace std;

int main()
{
    DoublyLinkedList<User> data;
    int loginSize = readFromFile("loginDetails.txt", data);

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
                cout << "Email or Password Incorrect!\n";
            cout << "Enter your email: ";
            cin >> email;
            cout << "Enter your password: ";
            cin >> password;

            userID = login(email, password, data);
            if (userID == 0)
                check = false;
        } while (userID == 0);
    }
    else if (ch == 'S' || ch == 's')
    {
        system("CLS");
        int userID = signUp(data);
    }
}