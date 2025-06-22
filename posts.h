#include <iostream>
using namespace std;

class Post
{
    string post;
    int noOfLikes;
    int noOfComments;
    int postid;
    int userid;

public:
    Post()
    {
        post = "";
        postid = userid = noOfLikes = noOfComments = 0;
    }
    Post(int pid, int uid, string p, int n, int c)
    {
        post = p;
        postid = pid;
        userid = uid;
        noOfLikes = n;
        noOfComments = n;
    }
    Post(const Post &obj)
    {
        post = obj.post;
        postid = obj.postid;
        userid = obj.userid;
        noOfLikes = obj.noOfLikes;
        noOfComments = obj.noOfComments;
    }
    Post &operator=(const Post &obj)
    {
        if (this != &obj)
        {
            post = obj.post;
            postid = obj.postid;
            userid = obj.userid;
            noOfLikes = obj.noOfLikes;
            noOfComments = obj.noOfComments;
        }
        return *this;
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
    void setnoOflikes(int n)
    {
        noOfLikes = n;
    }
    void setnoOfComments(int c)
    {
        noOfComments = c;
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
    int getnoOflikes()
    {
        return noOfLikes;
    }
    int getnoOfComments()
    {
        return noOfComments;
    }
};