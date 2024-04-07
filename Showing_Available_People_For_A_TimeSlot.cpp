#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>

using namespace std;

class FamilyMember 
{
public:
    FamilyMember(const string& name, int startTime, int endTime) : name(name), startTime(startTime), endTime(endTime) {}
  string getName() const {
        return name;
    }
    int getStartTime() const {
        return startTime;
    }
    int getEndTime() const {
        return endTime;
    }
private:
    string name;
    int startTime;
    int endTime;
};

void availablePeopleForAtimeSlot(vector<FamilyMember>& familyMembers) 
{
    vector<pair<int, vector<FamilyMember*>>> timeSlots;
    for (auto& member : familyMembers) {
        for (int time = member.getStartTime(); time < member.getEndTime(); ++time)
          {
            bool found = false;
            for (auto& slot : timeSlots)
              {
                if (slot.first == time) 
                {
                    slot.second.push_back(&member);
                    found = true;
                    break;
                }
            }
            if (!found) 
            {
                timeSlots.push_back(make_pair(time, vector<FamilyMember*>{&member}));
            }
        }
    }
    sort(timeSlots.begin(), timeSlots.end(), [](const pair<int, vector<FamilyMember*>>& a, const pair<int, vector<FamilyMember*>>& b) 
    {
        return a.first < b.first;
    });

    // Printing the scheduled series
    cout << "Scheduled Series:\n";
    for (const auto& slot : timeSlots) 
    {
        cout << "Time: " << slot.first << " - ";
        for (const auto& member : slot.second)
          {
            cout << member->getName() << " ";
        }
        cout << endl;
    }
}

int main() 
{
    //FILE HANDELING
    vector<FamilyMember> familyMembers;
    ifstream inputFile("family_info.txt");
    if (!inputFile.is_open())
    {
        cerr << "Error: Unable to open file." << endl;
        return 1;
    }
    string line;
    while (getline(inputFile, line)) 
    {
        stringstream ss(line);
        string name;
        int startTime, endTime;
        if (ss >> name >> startTime >> endTime) 
        {
            familyMembers.push_back(FamilyMember(name, startTime, endTime));
        } 
        else 
        {
            cerr << "Error: Invalid line format." << endl;
        }
    }
    inputFile.close();
   availablePeopleForAtimeSlot(familyMembers);

    return 0;
}
