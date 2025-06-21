#include <iostream>
using namespace std;

class Post
{
    string post;
    int postid;
    int userid;

public:
    Post()
    {
        post = "";
        postid = 0;
        userid = 0;
    }
    Post(int pid, int uid, string p)
    {
        post = p;
        postid = pid;
        userid = uid;
    }
    void setPost(string p)
    {
        post = p;
    }
    void setpostid(int pid)
    {
        postid = pid;
    }
    void setuserid(int uid)
    {
        userid = uid;
    }
    string getPost()
    {
        return post;
    }
    int getpostid()
    {
        return postid;
    }
    int getuserid()
    {
        return userid;
    }
};