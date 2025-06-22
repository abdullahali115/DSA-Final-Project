#include "Login+SignUpFunctions.h"

void mainMenu(User currentUser, AVL &data, DoublyLinkedList<Post> &postsLL, int postSize, DoublyLinkedList<Pair> &likePairs, DoublyLinkedList<Comment> &comments, DoublyLinkedList<Pair> &requestPairs)
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
            else if (choice == 'F' || choice == 'f')
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
}