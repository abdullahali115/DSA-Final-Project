#include "MajorFunctions.h"

void mainMenu(User currentUser, AVL &data, DoublyLinkedList<Post> &postsLL, int &postSize, DoublyLinkedList<Pair> &likePairs, DoublyLinkedList<Comment> &comments, DoublyLinkedList<Pair> &requestPairs, AVL &idTree, DoublyLinkedList<Pair> &friends, DoublyLinkedList<Chat> &chats, AVL &emailTree)
{
    char choice{};
    do
    {
        system("chcp 65001");
        system("CLS");
        cout << setw(71 - currentUser.getFullname().length()) << "================ Welcome " << currentUser.getFullname() << " ==================\n\n\n";
        cout << "📜 Press 'F' to view the feed\n";
        cout << "📥 Press 'I' to go to inbox\n";
        cout << "🔍 Press 'S' to search any user\n";
        cout << "✍️ Press 'C' to create a new post\n";
        cout << "📨 Press 'R' to view the friend requests received\n";
        cout << "🔐 Press 'U' to update your password\n";
        cout << "👤 Press 'P' to view your profile\n";
        cout << "💔 Press 'D' if you wish to delete your account\n";
        cout << "🚪 Press '0' to exit\n";
        choice = _getch();

        if (choice == 'C' || choice == 'c')
        {
            string post{};
            system("CLS");
            cout << "[Enter '0000' to go back]\n";
            cout << "What's on your mind today?: ";
            do
            {
                getline(cin, post);
            } while (post.empty() && post != "0000");
            if (post == "0000")
                continue;

            postsLL.insertAtTail(Post(postSize + 1, currentUser.getID(), post, 0, 0));
            writeToFile("Assets/posts.txt", postSize + 1, currentUser.getID(), post, 0, 0);
        }
        else if (choice == 'F' || choice == 'f')
        {
            bool check = false;
            int i = 0;
            int pSize = postsLL.size();
            while (i < pSize)
            {
                check = true;
                system("CLS");
                Post tempPost = postsLL[i];
                User author = idTree.searchUserByID(tempPost.getuserid());
                displayPost(author.getUsername(), tempPost.getPost(), tempPost.getnoOflikes(), tempPost.getnoOfComments());
                cout << "Press 'L' to like the post\n";
                cout << "Press 'C' to comment on the post\n";
                cout << "Press 'N' to go to the next post\n";
                if (currentUser.getID() != tempPost.getuserid())
                    cout << "Press 'F' to send friend request to author\n";
                if (i > 0)
                    cout << "Press 'B' to go back to previous post\n";
                cout << "👈 Press '0' to go back\n";
                char ch = _getch();
                if (ch == 'L' || ch == 'l')
                {
                    if (!isAlreadyLiked(tempPost.getpostid(), currentUser.getID(), likePairs))
                    {
                        int t = tempPost.getnoOflikes() + 1;
                        postsLL[i].setnoOflikes(t);
                        likePairs.insertAtTail(Pair(tempPost.getpostid(), currentUser.getID()));
                        updateLikePairs("Assets/likePairs.txt", likePairs);
                        updatePosts("Assets/posts.txt", postsLL);
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
                    if (cin.peek() == '\n')
                        cin.ignore();
                    getline(cin, comment);
                    comments.insertAtTail(Comment(comments.size() + 1, tempPost.getpostid(), currentUser.getID(), comment));
                    writeToCommentsFile("Assets/comments.txt", comments.size() + 1, tempPost.getpostid(), currentUser.getID(), comment);
                    postsLL[i].setnoOfComments(tempPost.getnoOfComments() + 1);
                    updatePosts("Assets/posts.txt", postsLL);
                    cout << "Comment Published successfully\n";
                    system("pause");
                }
                else if (ch == 'F' || ch == 'f')
                {
                    if (currentUser.getID() != tempPost.getuserid())
                    {
                        readFromRequestFile("Assets/requests.txt", requestPairs);
                        if (requestAlreadySent(currentUser.getID(), tempPost.getuserid(), requestPairs))
                        {
                            cout << "📨 Friend request already sent — waiting for a response.\n";
                            system("pause");
                        }
                        else if (requestAlreadyReceived(currentUser.getID(), tempPost.getuserid(), requestPairs))
                        {
                            cout << "🤝 You've already received a friend request from this user. Consider accepting it instead.😃\n";
                            system("pause");
                        }
                        else if (currentUser.getID() == tempPost.getuserid())
                        {
                            cout << "Error! Can't send friend request to yourself 😁\n";
                            system("pause");
                        }
                        else
                        {
                            friends.insertAtTail(Pair(currentUser.getID(), tempPost.getuserid()));
                            writeToRequestFile("Assets/requests.txt", currentUser.getID(), tempPost.getuserid());
                            cout << "✅ Friend request sent successfully!\n";
                            system("pause");
                        }
                    }
                }
                else if (ch == 'n' || ch == 'N')
                    i++;
                else if ((ch == 'b' || ch == 'B') && i > 0)
                    i--;
                else if (ch == '0')
                    break;
                if (i == postSize)
                {
                    if (check)
                        cout << "🕵️ Nothing left... you're all caught up! ✅\n\n";
                    else
                        cout << "📭 No posts available for now. Please check back later! 😊\n";
                    system("pause");
                }
            }
            if (!check)
            {
                if (i == postSize)
                {
                    if (check)
                        cout << "🕵️ Nothing left... you're all caught up! ✅\n\n";
                    else
                        cout << "📭 No posts available for now. Please check back later! 😊\n";
                    system("pause");
                }
            }
        }
        else if (choice == 'S' || choice == 's')
        {
            string str;
            cout << "\n\n🔎 Enter name to search: ";
            cin.ignore();
            getline(cin, str);
            cout << "\n\n";
            bool check = data.inOrderSearch(str, currentUser.getUsername());
            if (check)
            {
                cout << "\n\nPress 'F' to send friend request to anyone from the list\n";
                cout << "Press '0' to go back\n";
                char ch;
                do
                {
                    ch = _getch();
                } while (ch != 'F' && ch != 'f' && ch != '0');
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
                        else if (currentUser.getID() == uid)
                        {
                            cout << "Error! Can't send friend request to yourself 😁\n";
                            system("pause");
                        }
                        else if (requestAlreadyReceived(currentUser.getID(), uid, friends) || requestAlreadyReceived(uid, currentUser.getID(), friends))
                        {
                            cout << "🤝 You're already friends with this user.😃\n";
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
            else
            {
                cout << "😕 No Users Found 🔍\n";
                system("pause");
            }
        }
        else if (choice == 'R' || choice == 'r')
        {
            int i = 0;
            bool check = false;
            for (i; i < requestPairs.size(); i++)
            {
                system("CLS");
                Pair tempReq = requestPairs[i];
                if (tempReq.getP2() == currentUser.getID())
                {
                    check = true;
                    User sender = idTree.searchUserByID(tempReq.getP1());
                    cout << "📨 Friend request received from: " << sender.getFullname() << endl;
                    cout << "✅ Press 'A' to accept the request\n";
                    cout << "❌ Press 'R' to reject it\n";
                    cout << "🤔 Press 'I' to ignore for now\n";
                    char ch = _getch();
                    if (ch == 'A' || ch == 'a')
                    {
                        writeToRequestFile("Assets/friends.txt", sender.getID(), currentUser.getID());
                        friends.insertAtTail(Pair(sender.getID(), currentUser.getID()));
                        requestPairs.deleteAtIndex(i);
                        updateLikePairs("Assets/requests.txt", requestPairs);
                        cout << "🤝 You are now friends with " << sender.getFullname() << endl;
                        system("pause");
                    }
                    else if (ch == 'R' || ch == 'r')
                    {
                        requestPairs.deleteAtIndex(i);
                        updateLikePairs("Assets/requests.txt", requestPairs);
                        cout << "❌ Friend request from " << sender.getFullname() << " has been rejected successfully.\n";
                        system("pause");
                    }
                    else if (ch == 'I' || ch == 'i')
                    {
                        cout << "You ignored " << sender.getFullname() << "'s friend request. Maybe later! 😉\n";
                        system("pause");
                    }
                }
            }
            if (!check)
            {
                cout << "😊 You're all caught up! No new friend requests.\n";
                system("pause");
            }
        }
        else if (choice == 'i' || choice == 'I')
        {
            system("CLS");
            cout << setw(80) << "================ Welcome To your Inbox ==================\n\n\n";
            bool check = false;
            int i = 0;
            for (i; i < friends.size(); i++)
            {
                Pair tempFriend = friends[i];
                if (tempFriend.getP2() == currentUser.getID())
                {
                    check = true;
                    User sender = idTree.searchUserByID(tempFriend.getP1());
                    cout << "Friend ID: " << sender.getID() << "\nName: " << sender.getFullname() << endl;
                }
                if (currentUser.getID() == friends[i].getP1())
                {
                    check = true;
                    User sender = idTree.searchUserByID(tempFriend.getP2());
                    cout << "Friend ID: " << sender.getID() << "\nName: " << sender.getFullname() << endl;
                }
            }
            if (check)
            {
                int uid{};
                cout << "\n\nEnter UserID of the friend to chat with [Enter 0 to go back]: ";
                cin >> uid;
                while (!requestAlreadyReceived(currentUser.getID(), uid, friends) && !requestAlreadyReceived(uid, currentUser.getID(), friends))
                {
                    if (uid == 0)
                        break;
                    cout << "UserID not found\n";
                    cout << "Enter again [Enter 0 to go back]: ";
                    cin >> uid;
                    if (uid == 0)
                        break;
                }
                if (uid != 0)
                {
                    char ch{};
                    do
                    {
                        User friendInbox = idTree.searchUserByID(uid);
                        showChats(currentUser, friendInbox, chats);

                        cout << "\n\n\nEnter 'S' to send a message\n";
                        cout << "Enter 'R' to reload chat\n";
                        cout << "Enter 'B' to go back to main menu\n";
                        ch = _getch();
                        if (ch == 's' || ch == 'S')
                        {
                            system("CLS");
                            showChats(currentUser, friendInbox, chats);
                            string m;
                            cout << "\n\n\nEnter the message you want to send: ";
                            if (cin.peek() == '\n')
                                cin.ignore();
                            getline(cin, m);
                            chats.insertAtTail(Chat(m, currentUser.getID(), friendInbox.getID()));
                            writeChat("Assets/chats.txt", currentUser, friendInbox, m, chats);
                        }
                        else if (ch == 'R' || ch == 'r')
                        {
                            showChats(currentUser, friendInbox, chats);
                        }
                    } while (ch != 'B' && ch != 'b');
                    system("pause");
                }
            }
            else
            {
                cout << "😊 You haven't added any friends yet. Why not start now and say hi? 👋\n";
                system("pause");
            }
        }
        else if (choice == 'U' || choice == 'u')
        {
            string curPass{};
            cout << "Enter your current Password: ";
            curPass = getHiddenPassword();
            convertToCipher(curPass, 'K');
            if (curPass == currentUser.getPassword())
            {
                cout << "Enter new password: ";
                string newPass = getHiddenPassword();
                while (!checkPass(newPass))
                {
                    cout << "Password can't be less than 8 characters!\n";
                    cout << "Enter new password: ";
                    newPass = getHiddenPassword();
                }
                cout << "Confirm new password: ";
                curPass = getHiddenPassword();
                if (curPass == newPass)
                {
                    convertToCipher(newPass, 'K');
                    idTree.deleteUser(currentUser.getID());
                    currentUser.setPassword(newPass);
                    idTree.insertIntoIDAVL(currentUser);
                    idTree.updateFile("Assets/loginDetails.txt");
                    cout << "Password changed successfully\n";
                    system("pause");
                }
                else
                {
                    cout << "Passwords didn't match\n";
                    system("pause");
                }
            }
            else
            {
                cout << "Invalid Password! Unable to change\n";
                system("pause");
            }
        }
        else if (choice == 'P' || choice == 'p')
        {
            system("CLS");
            cout << setw(60 - currentUser.getFullname().length()) << "================ Welcome " << currentUser.getFullname() << " to your profile ==================\n\n\n";
            cout << "👤 Username: @" << currentUser.getUsername() << "\n\n";
            cout << "📧 Email: " << currentUser.getEmail() << "\n\n";
            cout << "👥 No. of Friends: " << countFriends("Assets/friends.txt", currentUser.getID()) << "\n\n";
            cout << "📝 No. of Posts: " << countPosts("Assets/posts.txt", currentUser.getID()) << endl;

            cout << "Press 'V' to view your posts and Comments\n";
            cout << "Press 'B' to go back\n";
            char ch{};
            do
            {
                ch = _getch();
            } while (ch != 'v' && ch != 'V' && ch != 'B' && ch != 'b');
            if (ch == 'V' || ch == 'v')
            {
                displayPostAndComments(comments, postsLL, currentUser.getID(), currentUser.getUsername());
                system("pause");
            }
            else if (ch == 'B' || ch == 'b')
                continue;
        }
        else if (choice == 'D' || choice == 'd')
        {
            string tmp{};
            cout << "\nAre you sure to delete your account?\nIf yes then type 'delete': ";
            cin >> tmp;
            convertToLower(tmp);
            if (tmp == "delete")
            {
                idTree.deleteUser(currentUser.getID());
                idTree.updateFile("Assets/loginDetails.txt");
                system("CLS");
                cout << "👋 Your account has been deleted. Farewell, and take care.\n";
                system("pause");
                break;
            }
        }
    } while (choice != '0');
}