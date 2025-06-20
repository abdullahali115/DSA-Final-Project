#include <iostream>
#include <iomanip>
using namespace std;

void welcomePage()
{
    system("chcp 65001");
    system("CLS");
    cout << setw(79) << " ==================== Welcome to ==================\n";
    cout << setw(80) << "|                                                  |\n";
    cout << setw(80) << "|                                                  |\n";
    cout << setw(80) << "|                    Connectify                    |\n";
    cout << setw(80) << "|             Where connections begin              |\n";
    cout << setw(89) << "|      👥 Community | 💬 Chat | ❤️  React           |\n";
    cout << setw(80) << "|                                                  |\n";
    cout << setw(80) << "|                                                  |\n";
    cout << setw(79) << " ==================================================\n";
    cout << "👋 Ready to dive in?\nPress L to Log In or S to Sign Up and join our amazing community ! 🌟\n";
}
