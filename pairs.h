#include <iostream>
using namespace std;

class Pair
{
    int p1;
    int p2;
    int p3;

public:
    Pair()
    {
        p1 = p2 = p3 = 0;
    }
    Pair(const Pair &obj)
    {
        p1 = obj.p1;
        p2 = obj.p2;
        p3 = obj.p3;
    }
    Pair &operator=(const Pair &obj)
    {
        if (this != &obj)
        {
            p1 = obj.p1;
            p2 = obj.p2;
            p3 = obj.p3;
        }
        return *this;
    }
    Pair(int x, int y, int z)
    {
        p1 = x;
        p2 = y;
        p3 = z;
    }
    Pair(int x, int y)
    {
        p1 = x;
        p2 = y;
    }
    void setP1(int x)
    {
        p1 = x;
    }
    void setP2(int y)
    {
        p2 = y;
    }
    void setP3(int z)
    {
        p3 = z;
    }

    int getP1()
    {
        return p1;
    }
    int getP2()
    {
        return p2;
    }
    int getP3()
    {
        return p3;
    }
};