#include <iostream>
using namespace std;

class Post
{
    string post;
    int postid;
    int userid;

public:
    Post(string p, int pid, int uid)
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
    int setpostid()
    {
        return postid;
    }
    int setuserid()
    {
        return userid;
    }
};