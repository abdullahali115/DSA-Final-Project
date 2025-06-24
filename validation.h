#include <iostream>
#include <string>
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