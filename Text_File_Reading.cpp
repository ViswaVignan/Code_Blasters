//THE BELOW CODE WAS USED BY US FOR TRYING TO LEARN TO READ A TEXT FILE IN C++


#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

int main() {
    string filename = "example.txt";

    // Writing to a file
    ofstream outputFile(filename);
    if (outputFile.is_open()) {
        outputFile << "Hello, World!\n";
        outputFile << "This is a simple text file.\n";
        outputFile.close();
        cout << "File '" << filename << "' has been written successfully." << endl;
    } else {
        cerr << "Unable to open file '" << filename << "' for writing." << endl;
        return 1;
    }

    // Reading from a file
    ifstream inputFile(filename);
    if (inputFile.is_open()) {
        cout << "Contents of file '" << filename << "':" << endl;
        string line;
        while (getline(inputFile, line)) {
            cout << line << endl;

            // Use stringstream to obtain each line
            stringstream ss(line);
            string word;
            while (ss >> word) {
                cout << "Word: " << word << endl;
            }
        }
        inputFile.close();
    } else {
        cerr << "Unable to open file '" << filename << "' for reading." << endl;
        return 1;
    }

    return 0;
}
