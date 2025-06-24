#include <iomanip>
#include <conio.h>
#include <fstream>
#include "pairs.h"
#include "AVLTree.h"
#include "posts.h"
#include "Stack.h"
#include "comment.h"
#include "chats.h"

using namespace std;

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
int countFriends(string filename, int id)
{
    fstream fin(filename, ios::in);
    if (!fin)
    {
        ofstream file(filename);
        file.close();
        fin.open(filename, ios::in);
    }
    int i = 0;
    int count = 0;
    int f1{};
    int f2{};
    if (fin.is_open())
    {
        while (fin >> f1)
        {
            fin >> f2;
            if (id == f1 || id == f2)
                count++;
            i++;
        }
    }
    fin.close();
    return count;
}
void convertToLower(string &temp)
{
    for (int i = 0; temp[i] != '\0'; i++)
        temp[i] = tolower(temp[i]);
}
void convertToCipher(string &temp, char key)
{
    for (int i = 0; temp[i] != '\0'; i++)
        temp[i] ^= key;
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

int updateLikePairs(string filename, DoublyLinkedList<Pair> &likePairs)
{
    ofstream fout(filename);
    int i = 0;
    int s = likePairs.size();
    if (fout.is_open())
    {
        while (i < s)
        {
            fout << likePairs[i].getP1() << " ";
            fout << likePairs[i].getP2() << "\n";
            i++;
        }
    }
    fout.close();
    return i;
}
int updatePosts(string filename, DoublyLinkedList<Post> &postsLL)
{
    ofstream fout(filename);
    int i = 0;
    int s = postsLL.size();
    if (fout.is_open())
    {
        while (i < s)
        {
            Post temp = postsLL[i];
            fout << temp.getpostid() << " " << temp.getuserid() << " " << temp.getnoOflikes() << " " << temp.getnoOfComments() << " " << temp.getPost() << "\n";
            i++;
        }
    }
    fout.close();
    return i;
}
void writeToCommentsFile(string filename, int comid, int postid, int userid, string com)
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
        fout << comid << " " << postid << " " << userid << " " << com << "\n";
    }
}
int readFromCommentFiles(string filename, DoublyLinkedList<Comment> &comments)
{
    fstream fin(filename, ios::in);
    if (!fin)
    {
        ofstream file(filename);
        file.close();
        fin.open(filename, ios::in);
    }
    int i = 0;
    int comID{};
    int postID{};
    int userID{};
    string comment{};
    if (fin.is_open())
    {
        while (fin >> comID)
        {
            fin >> postID;
            fin >> userID;
            fin.ignore();
            getline(fin, comment);
            comments.insertAtTail(Comment(comID, postID, userID, comment));
            i++;
        }
    }
    fin.close();
    return i;
}
void writeToRequestFile(string filename, int sender, int receiver)
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
        fout << sender << " " << receiver << "\n";
    }
}
int readFromRequestFile(string filename, DoublyLinkedList<Pair> &requestPairs)
{
    fstream fin(filename, ios::in);
    if (!fin)
    {
        ofstream file(filename);
        file.close();
        fin.open(filename, ios::in);
    }
    int i = 0;
    int u1;
    int u2;
    if (fin.is_open())
    {
        while (fin >> u1)
        {
            fin >> u2;
            requestPairs.insertAtTail(Pair(u1, u2));
            i++;
        }
    }
    fin.close();
    return i;
}
int readFromFriendsFile(string filename, DoublyLinkedList<Pair> &friendPairs)
{
    fstream fin(filename, ios::in);
    if (!fin)
    {
        ofstream file(filename);
        file.close();
        fin.open(filename, ios::in);
    }
    int i = 0;
    int u1;
    int u2;
    if (fin.is_open())
    {
        while (fin >> u1)
        {
            fin >> u2;
            friendPairs.insertAtTail(Pair(u1, u2));
            i++;
        }
    }
    fin.close();
    return i;
}
int readFromLikePairFiles(string filename, DoublyLinkedList<Pair> &likePairs)
{
    fstream fin(filename, ios::in);
    if (!fin)
    {
        ofstream file(filename);
        file.close();
        fin.open(filename, ios::in);
    }
    int i = 0;
    int p1{};
    int p2{};
    if (fin.is_open())
    {
        while (fin >> p1)
        {
            fin >> p2;
            likePairs.insertAtTail(Pair(p1, p2));
            i++;
        }
    }
    fin.close();
    return i;
}
int loadMessages(string filename, DoublyLinkedList<Chat> &chats)
{
    fstream fin(filename, ios::in);
    if (!fin)
    {
        ofstream file(filename);
        file.close();
        fin.open(filename, ios::in);
    }
    int i = 0;
    string message{};
    int senderID{};
    int receiverID{};
    if (fin.is_open())
    {
        while (fin >> senderID)
        {
            fin >> receiverID;
            if (fin.peek() == '\n')
                fin.ignore();
            getline(fin, message);
            chats.insertAtTail(Chat(message, senderID, receiverID));
            i++;
        }
    }
    fin.close();
    return i;
}
void showChats(User currentUser, User &friendInbox, DoublyLinkedList<Chat> &chats)
{
    system("CLS");
    string name = friendInbox.getFullname();
    string msg = "==================== " + name + " ======================";
    cout << setw((60 + msg.length()) / 2) << "==================== " << friendInbox.getFullname() << " ======================\n";
    int s = chats.size();
    for (int i = 0; i < s; i++)
    {
        Chat temp = chats[i];
        if ((temp.getSenderID() == currentUser.getID() && temp.getReceiverID() == friendInbox.getID()))
        {
            cout << "[Me] " << temp.getMessage() << endl;
        }
        if ((temp.getReceiverID() == currentUser.getID() && temp.getSenderID() == friendInbox.getID()))
        {
            cout << "[" << friendInbox.getUsername() << "] " << temp.getMessage() << endl;
        }
    }
}
void writeChat(string filename, User &currentUser, User &receiver, string message, DoublyLinkedList<Chat> &chats)
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
        fout << currentUser.getID() << " " << receiver.getID() << " " << message << "\n";
    }
    showChats(currentUser, receiver, chats);
}
int readFromFile(string filename, AVL &data, AVL &emailAVL, AVL &idTree)
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
            fin.ignore();
            getline(fin, fullname);
            data.insertIntoUserAVL(User(id, email, username, password, fullname));
            emailAVL.insertIntoEmailAVL(User(id, email, username, password, fullname));
            idTree.insertIntoIDAVL(User(id, email, username, password, fullname));
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
    int likes{};
    int comments{};
    if (fin.is_open())
    {
        while (fin >> postid)
        {
            fin >> userid;
            fin >> likes;
            fin >> comments;
            if (fin.peek() == '\n')
                fin.ignore();
            getline(fin, post);
            postsLL.insertAtTail(Post(postid, userid, post, likes, comments));
            i++;
        }
    }
    fin.close();
    return i;
}
int countPosts(string filename, int uid)
{
    fstream fin(filename, ios::in);
    if (!fin)
    {
        ofstream file(filename);
        file.close();
        fin.open(filename, ios::in);
    }
    int i = 0;
    int count = 0;
    string post{};
    int userid{};
    int postid{};
    int likes{};
    int comments{};
    if (fin.is_open())
    {
        while (fin >> postid)
        {
            fin >> userid;
            fin >> likes;
            fin >> comments;
            if (fin.peek() == '\n')
                fin.ignore();
            getline(fin, post);
            if (userid == uid)
                count++;
            i++;
        }
    }
    fin.close();
    return count;
}
void writeToFile(string filename, int postid, int userid, string post, int likes, int comments)
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
        fout << postid << " " << userid << " " << likes << " " << comments << " " << post << "\n";
    }
}
#include <iostream>
#include <conio.h> // For _getch()

using namespace std;

string getHiddenPassword()
{
    string password;
    char ch;

    while (true)
    {
        ch = _getch();
        if (ch == 13)
        {
            cout << endl;
            break;
        }
        else if (ch == 8)
        {
            if (!password.empty())
            {
                password.pop_back();
                cout << "\b \b";
            }
        }
        else if (ch == ' ')
        {
            continue;
        }
        else if (ch >= 33 && ch <= 126)
        {
            password += ch;
            cout << '*';
        }
    }
    return password;
}

User login(string email, string password, AVL &data)
{
    User temp = data.searchUserByEmail(email);
    if (email == temp.getEmail() && password == temp.getPassword())
        return temp;
    return User();
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

bool requestAlreadySent(int sender, int receiver, DoublyLinkedList<Pair> &requests)
{
    int s = requests.size();
    for (int i = 0; i < s; i++)
    {
        if (sender == requests[i].getP1() && receiver == requests[i].getP2())
            return true;
    }
    return false;
}
bool requestAlreadyReceived(int sender, int receiver, DoublyLinkedList<Pair> &requests)
{
    int s = requests.size();
    for (int i = 0; i < s; i++)
    {
        if (sender == requests[i].getP2() && receiver == requests[i].getP1())
            return true;
    }
    return false;
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
User signUp(AVL &data, AVL &emailAVL, AVL &idTree)
{
    cout << setw(84) << "==================== Signup Page ====================\n\n\n";
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
    password = getHiddenPassword();
    convertToCipher(password, 0x54);
    while (!checkPass(password))
    {
        cout << "Password can't be less than 8 characters!\n";
        cout << "Enter password: ";
        password = getHiddenPassword();
        convertToCipher(password, 0x54);
    }
    cout << "Enter Full Name: ";
    if (cin.peek() == '\n')
        cin.ignore();
    getline(cin, fullname);
    int s = data.getMaxID();
    convertToLower(username);
    convertToLower(email);
    data.insertIntoUserAVL(User(s + 1, email, username, password, fullname));
    emailAVL.insertIntoEmailAVL(User(s + 1, email, username, password, fullname));
    idTree.insertIntoIDAVL(User(s + 1, email, username, password, fullname));
    writeToFile("Assets/loginDetails.txt", s + 1, email, username, password, fullname);

    return User(s + 1, email, username, password, fullname);
}

void displayPost(string username, string content, int likes, int comments)
{
    const int conwidth = 50;
    const int bWidth = conwidth + 7;
    const int fullWIdth = 100;
    const int padding = (fullWIdth - bWidth) / 2;
    int contLen = content.length();
    int lines = (contLen + conwidth - 1) / conwidth;
    string pad(padding, ' ');
    cout << pad << string(bWidth, '=') << '\n';
    string user = "👤 @" + username + "    ";
    cout << pad << "| " << user << string(conwidth - user.length() + 4, ' ') << "   |\n";
    for (int i = 0; i < lines; ++i)
    {
        string line = content.substr(i * conwidth, conwidth);
        cout << pad << "|   " << line << string(conwidth - line.length(), ' ') << "   |\n";
    }
    cout << pad << "|   " << string(conwidth, ' ') << "   |\n";
    string lastLine = "💕 " + to_string(likes) + "   💬 " + to_string(comments);
    cout << pad << "|   " << lastLine << string(conwidth - lastLine.length() + 4, ' ') << "   |\n";

    cout << pad << string(bWidth, '=') << '\n';
}
void displayPostAndComments(DoublyLinkedList<Comment> &comments, DoublyLinkedList<Post> &postsLL, int uid, string username)
{
    int s = postsLL.size();
    int index = 1;
    for (int i = 0; i < s; i++)
    {
        Post temp = postsLL[i];
        int c = comments.size();
        if (temp.getuserid() == uid)
        {
            displayPost(username, temp.getPost(), temp.getnoOflikes(), temp.getnoOfComments());
            for (int j = 0; j < c; j++)
            {
                Comment temp2 = comments[j];
                if (temp.getpostid() == temp2.getPostID())
                {
                    cout << index++ << ". " << temp2.getComment() << "\n\n";
                }
            }
        }
    }
}
bool isAlreadyLiked(int p1, int p2, DoublyLinkedList<Pair> &likePairs)
{
    int s = likePairs.size();
    for (int i = 0; i < s; i++)
    {
        if (likePairs[i].getP1() == p1 && likePairs[i].getP2() == p2)
            return true;
    }
    return false;
}