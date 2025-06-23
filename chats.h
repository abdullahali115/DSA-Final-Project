#include <iostream>
using namespace std;

class Chat
{
    string message;
    int senderID;
    int receiverID;

public:
    Chat()
    {
        message = "";
        senderID = receiverID = 0;
    }
    Chat(string m, int s, int r)
    {
        message = m;
        senderID = s;
        receiverID = r;
    }
    Chat(const Chat &obj)
    {
        message = obj.message;
        senderID = obj.senderID;
        receiverID = obj.receiverID;
    }
    Chat &operator=(const Chat &obj)
    {
        if (this != &obj)
        {
            message = obj.message;
            senderID = obj.senderID;
            receiverID = obj.receiverID;
        }
        return *this;
    }
    void setMessage(string m)
    {
        message = m;
    }
    void setSenderID(int s)
    {
        senderID = s;
    }
    void setReceiverID(int r)
    {
        receiverID = r;
    }
    string getMessage()
    {
        return message;
    }
    int getSenderID()
    {
        return senderID;
    }
    int getReceiverID()
    {
        return receiverID;
    }
};