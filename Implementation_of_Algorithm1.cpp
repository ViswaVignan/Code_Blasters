#include <iostream>
#include <vector>
using namespace std;
void displayHashTable(vector<vector<int>>& hashTable) 
{
    cout << "Hash Table:" << endl;
    cout << "Time Slot | Input 1 | Input 2 | Input 3 | Output" << endl;
    for (int i = 0,j,k=0; i < hashTable.size(); ++i,++k) 
    {
        for ( j = 0; j < hashTable[i].size(); ++j) 
        {
            cout << hashTable[i][j] << "         | ";
        }
        cout << endl;
    }
    cout << endl;
}
int main()
{
    //Hash table input and display
    vector<vector<int>> hashTable(4, vector<int>(5));
    cout << "Enter inputs for hash table (0 or 1):" << endl;
    for (int i = 0; i < hashTable.size(); ++i)
    {
        cout << "Row " << i + 1 << ":" << endl;
        for (int j = 0; j < 3; ++j) 
        {
            cout << "Input " << j + 1 << ": ";
            cin >> hashTable[i][j + 1];
        }
    }
    for (int i = 0; i < hashTable.size(); ++i) 
    {
        int sum = 0;
        for (int j = 1; j < 4; ++j) 
        {
            sum += hashTable[i][j];
        }
        if (sum == 0)
            hashTable[i][4] = 0;
        else if (sum == 1) 
        {
            for (int j = 1; j < 4; ++j) 
            {
                if (hashTable[i][j] == 1) 
                {
                    hashTable[i][4] = j;
                    break;
                }
            }
        } else
            hashTable[i][4] = 2;
    }
    displayHashTable(hashTable);

    //Link list input and display

    int arr[5][4],test[5][2];
    for(int i=0;i<5;i++)
    {
        arr[i][0]=(101+i);
        test[i][0]=(101+i);
    }
    for(int i=0;i<5;i++)
    {
        int count=0,x,y;
        for(int j=1;j<4;j++) 
        {
            cout<<"Enter if "<<(101+i)<<" is favourite series of person "<<j<<endl;
            cin>>arr[i][j];
            count+=arr[i][j];
            if(arr[i][j]==1)
            {
                x=i;y=j;
            }
        }
        if(count==1)
        {
            test[i][1]=1;
        }
        else
            test[i][1]=0;
    }
    for(int i=0;i<5;i++)
    {
        for(int j=0;j<4;j++)
        {
            cout<<arr[i][j]<<" ";
        }
        cout<<endl;
    }
    for(int i=0;i<5;i++)
    {
        cout<<test[i][0]<<" "<<test[i][1]<<endl;
    }
    }
    return 0;
}
