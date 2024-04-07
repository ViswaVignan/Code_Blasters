#include <iostream>
#include <unordered_set>
#include <string>

using namespace std;

int main() 
{
    unordered_set<string> mySet;
    mySet.insert("apple");
    mySet.insert("banana");
    mySet.insert("orange");
    cout << "Initial elements of the set:" << endl;
    for (const auto& element : mySet) 
    {
        cout << element << endl;
    }
    if (mySet.count("banana")) 
    {
        cout << "Element 'banana' exists in the set." << endl;
    } 
    else 
    {
        cout << "Element 'banana' does not exist in the set." << endl;
    }
    mySet.erase("orange");
    cout << "After erasing element 'orange':" << endl;
    for (const auto& element : mySet) 
    {
        cout << element << endl;
    }
    cout << "Size of the set: " << mySet.size() << endl;
    mySet.clear();
    cout << "After clearing the set, size: " << mySet.size() << endl;

    return 0;
}
