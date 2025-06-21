#include <string>
using namespace std;
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
        id = 0;
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
    bool operator<(const User &obj)
    {
        return this->username < obj.username;
    }
    bool operator>(const User &obj)
    {
        return this->username > obj.username;
    }
    bool operator==(const User &obj)
    {
        return this->username == obj.username;
    }
    bool operator<(const string obj)
    {
        return this->username < obj;
    }
    bool operator>(const string obj)
    {
        return this->username > obj;
    }
    bool operator==(const string obj)
    {
        return this->username == obj;
    }
};