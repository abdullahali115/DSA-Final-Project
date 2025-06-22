#include "Login+SignUpFunctions.h"

void mainMenu(User currentUser, AVL &data, DoublyLinkedList<Post> &postsLL, int postSize, DoublyLinkedList<Pair> &likePairs, DoublyLinkedList<Comment> &comments, DoublyLinkedList<Pair> &requestPairs, AVL &idTree)
{
    system("chcp 65001");
    system("CLS");
    cout << "📜 Press 'F' to view the feed\n";
    cout << "📥 Press 'I' to go to inbox\n";
    cout << "🔍 Press 'S' to search any user\n";
    cout << "✍️ Press 'C' to create a new post\n";
    cout << "📨 Press 'R' to view the friend requests received\n";
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

        postsLL.insertAtTail(Post(postSize + 1, currentUser.getID(), post, 0, 0));
        writeToFile("Assets/posts.txt", postSize + 1, currentUser.getID(), post, 0, 0);
    }
    else if (choice == 'F' || choice == 'f')
    {
        for (int i = 0; i < postSize; i++)
        {
            system("CLS");
            displayPost(currentUser.getUsername(), postsLL[i].getPost(), postsLL[i].getnoOflikes(), postsLL[i].getnoOfComments());
            cout << "Press 'L' to like the post\n";
            cout << "Press 'C' to comment on the post\n";
            if (currentUser.getID() != postsLL[i].getuserid())
                cout << "Press 'F' to send friend request to author\n";
            if (i > 0)
                cout << "Press 'B' to go back to previous post\n";
            char ch = _getch();
            if (ch == 'L' || ch == 'l')
            {
                if (!isAlreadyLiked(postsLL[i].getpostid(), currentUser.getID(), likePairs))
                {
                    int t = postsLL[i].getnoOflikes() + 1;
                    postsLL[i].setnoOflikes(t);
                    likePairs.insertAtTail(Pair(postsLL[i].getpostid(), currentUser.getID()));
                    updateLikePairs("Assets/likePairs.txt", likePairs);
                    updatePosts("Assets/posts.txt", postsLL);
                    i--;
                }
                else
                {
                    cout << "You have already liked this post\n";
                    system("pause");
                }
            }
            else if (ch == 'C' || ch == 'c')
            {
                string comment{};
                cout << "💬 What would you like to comment on this post? ";
                getline(cin, comment);
                writeToCommentsFile("Assets/comments.txt", comments.size() + 1, postsLL[i].getpostid(), currentUser.getID(), comment);
            }
            else if (ch == 'F' || ch == 'f')
            {
                if (currentUser.getID() != postsLL[i].getuserid())
                {
                    readFromRequestFile("Assets/requests.txt", requestPairs);
                    if (requestAlreadySent(currentUser.getID(), postsLL[i].getuserid(), requestPairs))
                    {
                        cout << "📨 Friend request already sent — waiting for a response.\n";
                        system("pause");
                    }
                    else if (requestAlreadyReceived(currentUser.getID(), postsLL[i].getuserid(), requestPairs))
                    {
                        cout << "🤝 You've already received a friend request from this user. Consider accepting it instead.😃\n";
                        system("pause");
                    }
                    else
                    {
                        writeToRequestFile("Assets/requests.txt", currentUser.getID(), postsLL[i].getuserid());
                        cout << "✅ Friend request sent successfully!\n";
                        system("pause");
                    }
                }
            }
        }
    }
    else if (choice == 'S' || choice == 's')
    {
        string str;
        cout << "🔎 Enter name to search: ";
        getline(cin, str);
        data.inOrderSearch(str);

        cout << "Press 'F' to send friend request to anyone from the list\n";
        cout << "Press 'B' to go back\n";
        char ch = _getch();
        if (ch == 'F' || ch == 'f')
        {
            int uid{};
            cout << "Enter UserID to send request: ";
            cin >> uid;
            if (uid > 0 && uid <= data.size())
            {
                if (requestAlreadySent(currentUser.getID(), uid, requestPairs))
                {
                    cout << "📨 Friend request already sent — waiting for a response.\n";
                    system("pause");
                }
                else if (requestAlreadyReceived(currentUser.getID(), uid, requestPairs))
                {
                    cout << "🤝 You've already received a friend request from this user. Consider accepting it instead.😃\n";
                    system("pause");
                }
                else
                {
                    writeToRequestFile("Assets/requests.txt", currentUser.getID(), uid);
                    cout << "✅ Friend request sent successfully!\n";
                    system("pause");
                }
            }
            else
            {
                cout << "❌ Invalid UserID entered\n";
                system("pause");
            }
        }
    }
    else if (choice == 'R' || choice == 'r')
    {
        for (int i = 0; i < requestPairs.size(); i++)
        {
            system("CLS");
            if (requestPairs[i].getP2() == currentUser.getID())
            {
                User sender = idTree.searchUserByID(requestPairs[i].getP1());
                cout << "📨 Friend request received from: " << sender.getFullname() << endl;
                cout << "✅ Press 'A' to accept the request\n";
                cout << "❌ Press 'R' to reject it\n";
                cout << "🤔 Press 'I' to ignore for now\n";
                char ch = _getch();
                if (ch == 'A' || ch == 'a')
                {
                    writeToRequestFile("Assets/friends.txt", sender.getID(), currentUser.getID());
                    requestPairs.deleteAtIndex(i);
                    updateLikePairs("Assets/requests.txt", requestPairs);
                    i--;
                    cout << "🤝 You are now friends with " << sender.getFullname() << endl;
                    system("pause");
                }
            }
        }
        system("pause");
    }
}