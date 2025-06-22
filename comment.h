#include <iostream>
using namespace std;

class Comment
{
    int comID;
    string com;
    int postid;
    int userid;

public:
    Comment()
    {
        com = "";
        comID = postid = userid = 0;
    }
    Comment(int cid, int p, int u, string c)
    {
        comID = cid;
        com = c;
        postid = p;
        userid = u;
    }
    Comment(const Comment &obj)
    {
        comID = obj.comID;
        com = obj.com;
        postid = obj.postid;
        userid = obj.userid;
    }
    Comment &operator=(const Comment &obj)
    {
        if (this != &obj)
        {
            comID = obj.comID;
            com = obj.com;
            postid = obj.postid;
            userid = obj.userid;
        }
        return *this;
    }
    void setCommentID(int cid)
    {
        comID = cid;
    }
    void setComment(string c)
    {
        com = c;
    }
    void setPostID(int p)
    {
        postid = p;
    }
    void setUserID(int u)
    {
        userid = u;
    }
    int getCommentID()
    {
        return comID;
    }
    string getComment()
    {
        return com;
    }
    int getPostID()
    {
        return postid;
    }
    int getUserID()
    {
        return userid;
    }
};