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
    AVL idTree;
    DoublyLinkedList<Post> postsLL;
    DoublyLinkedList<Pair> likePairs;
    DoublyLinkedList<Comment> comments;
    DoublyLinkedList<Pair> requestPairs;
    DoublyLinkedList<Pair> friendPairs;
back:

    int loginSize = readFromFile("Assets/loginDetails.txt", data, emailTree, idTree);
    char ch = welcomePage();
    int postsSize = readFromFile("Assets/posts.txt", postsLL);
    int pairSize = readFromLikePairFiles("Assets/likePairs.txt", likePairs);
    int commentSize = readFromCommentFiles("Assets/comments.txt", comments);
    int requests = readFromRequestFile("Assets/requests.txt", requestPairs);
    int friends = readFromFriendsFile("Assets/friends.txt", friendPairs);
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
            password = getHiddenPassword();
            if (email == "0" && password == "0")
            {
                break;
            }
            currentUser = login(email, password, emailTree);
            if (currentUser.getID() == 0)
                check = false;
        } while (currentUser.getID() == 0);

        if (currentUser.getID() != 0)
            mainMenu(currentUser, data, postsLL, postsSize, likePairs, comments, requestPairs, idTree);
    }
    else if (ch == 'S' || ch == 's')
    {
        system("CLS");
        User currentUser = signUp(data, emailTree, idTree);
        mainMenu(currentUser, data, postsLL, postsSize, likePairs, comments, requestPairs, idTree);
    }
    else if (ch == '0')
        return 0;
    goto back;
    return 0;
}