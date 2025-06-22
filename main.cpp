#include <iostream>
#include <string>
#include <conio.h>
#include "WelcomePage.h"
#include "mainMenu.h"
using namespace std;

int main()
{
    system("chcp 65001");
    system("CLS");
    AVL data;
    AVL emailTree;
    DoublyLinkedList<Post> postsLL;
    DoublyLinkedList<Pair> likePairs;
    DoublyLinkedList<Comment> comments;
    DoublyLinkedList<Pair> requestPairs;
    DoublyLinkedList<Pair> friendPairs;
back:

    int loginSize = readFromFile("Assets/loginDetails.txt", data, emailTree);
    char ch = welcomePage();
    int postsSize = readFromFile("Assets/posts.txt", postsLL);
    int pairSize = readFromLikePairFiles("Assets/likePairs.txt", likePairs);
    int commentSize = readFromCommentFiles("Assets/comments.txt", comments);
    int requests = readFromRequestFile("Assets/requests.txt", requestPairs);
    string email{}, password{}, username{}, fullname{}, id{};

    if (ch == 'l' || ch == 'L')
    {
        User currentUser;
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
            currentUser = login(email, password, emailTree);
            if (currentUser.getID() == 0)
                check = false;
        } while (currentUser.getID() == 0);

        if (currentUser.getID() != 0)
            mainMenu(currentUser, data, postsLL, postsSize, likePairs, comments, requestPairs);
    }
    else if (ch == 'S' || ch == 's')
    {
        system("CLS");
        User currentUser = signUp(data, emailTree);
        mainMenu(currentUser, data, postsLL, postsSize, likePairs, comments, requestPairs);
    }
    goto back;
    return 0;
}