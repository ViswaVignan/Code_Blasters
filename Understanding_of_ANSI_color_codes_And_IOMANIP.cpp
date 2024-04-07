#include <iostream>
#include <iomanip>

using namespace std;

int main() {
   
    const string reset = "\033[0m";
    const string red = "\033[1;31m";
    const string green = "\033[1;32m";
    const string yellow = "\033[1;33m";
    const string blue = "\033[1;34m";
    const string magenta = "\033[1;35m";
    const string cyan = "\033[1;36m";

   
    cout << red << "Red text" << reset << endl;
    cout << green << "Green text" << reset << endl;
    cout << yellow << "Yellow text" << reset << endl;
    cout << blue << "Blue text" << reset << endl;
    cout << magenta << "Magenta text" << reset << endl;
    cout << cyan << "Cyan text" << reset << endl;

    
    cout << setw(10) << "Width 10" << endl;
    cout << setw(20) << "Width 20" << endl;

    return 0;
}
