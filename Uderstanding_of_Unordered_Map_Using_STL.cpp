#include <iostream>
#include <unordered_map>
#include <string>

using namespace std;

int main() {
    unordered_map<string, int> myMap;
    myMap["apple"] = 5;
    myMap["banana"] = 3;
    myMap["orange"] = 7;
    cout << "Initial key-value pairs of the map:" << endl;
    for (const auto& pair : myMap) {
        cout << pair.first << ": " << pair.second << endl;
    }
    cout << "Value associated with key 'banana': " << myMap["banana"] << endl;
    if (myMap.count("apple")) {
        cout << "Key 'apple' exists in the map." << endl;
    } else {
        cout << "Key 'apple' does not exist in the map." << endl;
    }
    myMap["banana"] = 6;
    cout << "Updated value associated with key 'banana': " << myMap["banana"] << endl;
    myMap.insert({"grape", 9});
    cout << "Inserted new key-value pair: grape - " << myMap["grape"] << endl;
    myMap.erase("orange");
    cout << "After erasing key 'orange':" << endl;
    for (const auto& pair : myMap) {
        cout << pair.first << ": " << pair.second << endl;
    }
    cout << "Size of the map: " << myMap.size() << endl;
    myMap.clear();
    cout << "After clearing the map, size: " << myMap.size() << endl;

    return 0;
}
