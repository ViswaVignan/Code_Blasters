#include <iostream>
#include <vector>
using namespace std;

void display(vector<vector<int>>& HashTable) 
{
    cout << "Hash Table:" << endl;
    cout << "Time Slot   Input 1   Input 2   Input 3   Output" << endl;
    for (int i = 0; i < HashTable.size(); ++i)
    {
        for (int j = 0; j < HashTable[i].size(); ++j)
        {
            cout << HashTable[i][j] << "         | ";
        }
        cout << endl;
    }
    cout << endl;
}
int main()
{
    vector<vector<int>> Hash(4, vector<int>(4));
    cout << "Enter inputs for hash table (0 or 1):" << endl;
    for (int i = 0; i < Hash.size(); ++i)
    {
        cout << "Row " << i + 1 << ":" << endl;
        for (int j = 0; j < 3; ++j) 
        {
            cout << "Input " << j + 1 << ": ";
            cin >> Hash[i][j + 1];
        }
    }
    for(int i=0;i<4;i++)
    {
        Hash[i][0]=i+1;
    }
    display(Hash);
    for(int i=0,count=0;i<4;i++)
    {
        int x,y;
        for(int j=1;j<4;j++)
        {
            if(Hash[i][j]==1)
            {
                x=i+1;y=j;
            }
            count=count+Hash[i][j];
        }
        if(count==0)
        {
            cout<<"Time slot left empty.\n";
            count=0;
            continue;
        }
        if(count==1)
        {
            cout<<"Person with index ("<<x<<","<<y<<") is notified.\n";
            count=0;
            continue;
        }
        else
        cout<<"Clash occured.\n";
        count=0;
    }
    return 0;
}
