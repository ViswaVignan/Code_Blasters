#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <string>
#include <unordered_set>

using namespace std;

struct Person_Record
{
    string Person_Name;
    unordered_set<string> Series_Names;
    int time_slots[25]; // first slot in array goes to the total number of slots available for that person.
};

void slot_file_read()
{

    ifstream file("slots.csv");
    if (!file.is_open())
    {
        cout << "Error opening file." << endl;
        return;
    }

    vector<Person_Record> records; // this is for storing each person's data in the records vector.

    string line;

    while (getline(file, line))
    {
        stringstream ss(line);
        string name, series_names, time_slots;

        // Read name and series names
        getline(ss, name, ',');         // reads the data up to ',' and stores in name
        getline(ss, series_names, ','); // stores the data in series_names
        getline(ss, time_slots);        

        Person_Record record;
        record.Person_Name = name;

        // Split series names by space
        stringstream series_ss(series_names);
        string series_name;
        while (getline(series_ss, series_name, ' '))
        { // inserts the series names in the unorderd_set
            record.Series_Names.insert(series_name);
        }

        // Split time slots by comma and store in the array
        stringstream slots_ss(time_slots);
        // Assuming 'record' is a structure containing the time slots array
        int hour = 0;
        string slot;
        while (getline(slots_ss, slot, ','))
        {
            int value = stoi(slot);              // converts string to the integer value
            record.time_slots[hour + 1] = value; // Store data from arr[1] onwards
            hour++;
        }

        // Update total slots for the person
        record.time_slots[0] = 0;
        for (int i = 1; i <= 24; i++)
        {
            if (record.time_slots[i] == 1)
            {
                record.time_slots[0]++;
            }
        }

        records.push_back(record);
    }
}

void series_file_read(vector<string> &available_series)
{
    ifstream file("series.csv");
    if (!file.is_open())
    {
        cout << "Error opening file." << endl;
        return;
    }

    string line;
    while (getline(file, line))
    {
        stringstream ss(line);
        string series_name;

        // Read series names
        while (getline(ss, series_name, ','))
        {
            available_series.push_back(series_name);
        }
    }
}
int main()
{
    vector<string> available_series;
    series_file_read(available_series);
    return 0;
}