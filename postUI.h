#include <iostream>
#include <string>
using namespace std;

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