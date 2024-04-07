#include<iostream>
#include<string>
#include<fstream>
#include<sstream>
#include<vector>

using namespace std;

int main()
{
    vector<int> marks;
    vector<string> first_name;
    vector<string> last_name;
    ifstream in;
    in.open("dummy.csv");
    string line;
    // Check if the file was opened successfully
    if (!in.is_open()) {
        cerr << "Error: Unable to open file." << endl;
        return 1;
    }
    string dummy;
    getline(in,dummy);  // This is the dummy string read to eliminate the first line which is
                        // column names names and the marks

    while(getline(in, line))
    {
        stringstream ss(line);  // this line helps to convert the line into a stream useful 
        string name, marksStr;
        if(getline(ss, name, ',') && getline(ss, marksStr, ','))
        {
            first_name.push_back(name);
            marks.push_back(stoi(marksStr)); // Convert marksStr to integer using stoi and push it into marks vector
        }
    }

    for(int i=0;i<first_name.size();i++)
    {
        cout<<first_name[i]<<" ";
    }
    cout<<endl<<endl;

    for(int i=0;i<marks.size();i++)
    {
        cout<<marks[i]<<" ";
    }
    
    // Close the file
    in.close();
    
    return 0;
}
