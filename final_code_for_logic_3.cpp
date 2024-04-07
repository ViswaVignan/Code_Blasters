#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <string>
#include <unordered_set>
#include <unordered_map>
#include <limits>
using namespace std;

const string RED_COLOR = "\033[31m";
const string GREEN_COLOR = "\033[32m";
const string RESET_COLOR = "\033[0m";
const string CYAN_COLOR = "\033[36m";
const string BLUE_COLOR = "\033[34m";
const string PINK_COLOR = "\033[95m";

struct Person_Record
{
    string Person_Name;
    unordered_set<string> Series_Names;
    int time_slots[25];
    int total_series;
};

unordered_map<int, string> output_data;
int p;

void scheduler(vector<Person_Record> &records)
{

    for (int hour = 0; hour < 24; hour++)
    {

        int length = 0;

        for (const auto &record : records)
        {
            length += record.time_slots[hour + 1];
        }

        if (length > 1)
        {

            unordered_set<string> common_series; // Multiple people have this slot, check for common series
            unordered_set<string> temp2;
            unordered_map<string, int> max_common_series;

            for (const auto &record : records)
            {

                if (record.time_slots[hour + 1] == 1)
                {

                    for (const auto &series : record.Series_Names)
                    {

                        max_common_series[series];

                        if (temp2.count(series) > 0)
                        {
                            common_series.insert(series);
                            max_common_series[series]++;
                        }
                        else
                        {
                            temp2.insert(series);
                            max_common_series[series]++;
                        }
                    }
                }
            }

            if (common_series.size() >= 1)
            {
                // Multiple common series for all people, remove and update records

                string most_common_series;
                int max_compare = 0;

                for (string value : common_series)
                {
                    for (const auto &data : max_common_series)
                    {
                        int temp_for_max_compare = max_common_series[value];

                        if (temp_for_max_compare > max_compare)
                        {
                            max_compare = temp_for_max_compare;
                            most_common_series = value;
                        }
                    }
                }
                for (auto &record : records)
                {
                    if (record.time_slots[hour + 1] == 1)
                    {
                        if (record.Series_Names.count(most_common_series) > 0)
                        {
                            output_data[hour] += record.Person_Name + " (" + most_common_series + ") ";
                            record.Series_Names.erase(most_common_series);
                        }
                        record.time_slots[hour + 1] = 0;
                        record.time_slots[0]--;
                    }
                }
            }
        }
        else
        {

            continue;
        }
    }

    // write the cases for length=1
    for (int hour = 0; hour < 24; hour++)
    {

        int length = 0;

        // Calculate length of slots for this hour
        for (const auto &record : records)
        {
            length += record.time_slots[hour + 1];
        }

        if (length == 1)
        {

            // Only one person has this slot
            for (auto &record : records)
            {

                if (record.time_slots[hour + 1] == 1)
                {

                    if (record.Series_Names.size())
                    {
                        string common_series_name = *record.Series_Names.begin();
                        output_data[hour] = record.Person_Name + " (" + common_series_name + ") ";

                        record.Series_Names.erase(common_series_name);
                    }

                    record.time_slots[hour + 1] = 0;
                    record.time_slots[0]--;
                }
            }
        }
    }
    // no common series but common slots
    for (int hour = 0; hour < 24; hour++)
    {
        ;
        int length = 0;

        // Calculate length of slots for this hour
        for (const auto &record : records)
        {
            length += record.time_slots[hour + 1];
        }

        if (length > 1)
        {
            // Check if any person has remaining series
            bool person_found = false;
            for (const auto &record : records)
            {
                if (record.time_slots[hour + 1] == 1 && !record.Series_Names.empty())
                {
                    person_found = true;
                    break;
                }
            }

            if (person_found)
            {
                // At least one person has remaining series, assign the slot to one of them
                int x = 0;
                for (const auto &record : records)
                {
                    if (record.time_slots[hour + 1] == 1 && record.Series_Names.size())
                    {
                        break;
                    }
                    x++;
                }
                Person_Record &selected_person = records[x];
                string common_series_name = *selected_person.Series_Names.begin();
                output_data[hour] = selected_person.Person_Name + " (" + common_series_name + ") ";
                selected_person.Series_Names.erase(common_series_name);

                for (auto &record : records)
                {
                    if (record.time_slots[hour + 1] == 1)
                    {
                        record.time_slots[hour + 1] = 0;
                        record.time_slots[0]--;
                    }
                }
            }
            else
            {
                // No person has remaining series, leave the slot unassigned
            }
        }
    }
}

void slot_file_read(vector<Person_Record> &records)
{
    ifstream file("final_input.csv");
    if (!file.is_open())
    {
        cout << "Error opening file." << endl;
        return;
    }

    string line;

    getline(file, line); // this is to skip the first line

    while (getline(file, line))
    {
        stringstream ss(line);
        string name, series_names, time_slots;

        // Read name and series names
        getline(ss, name, ',');
        getline(ss, series_names, ',');
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
            int value = stoi(slot);
            record.time_slots[hour + 1] = value;
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
        // Calculate and store total number of series
        record.total_series = record.Series_Names.size();

        records.push_back(record);
    }
}

#include <iomanip>

void print_final_schedule()
{
    // Color codes for foreground text
    const string RED_COLOR = "\033[31m";
    const string GREEN_COLOR = "\033[32m";
    const string RESET_COLOR = "\033[0m";
    const string CYAN_COLOR = "\033[36m";
    const string BLUE_COLOR = "\033[34m";

    cout << CYAN_COLOR << "FINAL SCHEDULE: " << RESET_COLOR << endl;
    for (int hour = 0; hour < 24; hour++) // Adjusted loop to start from 0
    {
        // Set the width for the hour slot
        cout << GREEN_COLOR << setw(8) << "SLOT " << hour + 1 << " " << RESET_COLOR << setw(2) << hour << ":00-" << hour + 1 << ":00 - ";
        if (output_data[hour].empty())
        {
            cout << RED_COLOR << "NO ONE HAS BEEN ALLOCATED TO THIS SLOT" << RESET_COLOR << endl;
        }
        else
        {
            cout << BLUE_COLOR << output_data[hour] << RESET_COLOR << endl;
        }
    }
}

void misses(vector<Person_Record> &records)
{
    int total_misses = 0;
    cout << "\n"
         << BLUE_COLOR << "MISSED SERIES:" << RESET_COLOR << endl;
    for (const auto &record : records)
    {
        if (!record.Series_Names.empty())
        {
            cout << GREEN_COLOR << setw(15) << record.Person_Name << ":" << RESET_COLOR << " (";
            for (const auto &series : record.Series_Names)
            {
                cout << series << " ";
            }
            cout << ") ";
            if (record.total_series - record.Series_Names.size() < p)
            {
                cout << RED_COLOR << "(This person did not get P slots in the schedule)" << RESET_COLOR;
            }
            cout << endl;
            total_misses += record.Series_Names.size();
        }
    }

    cout << "\n THE TOTAL NUMBER OF SERIES MISSED: " << total_misses << endl;
}

int main()
{
    cout << "\n ENTER THE VALUE OF P: ";
    cin >> p;

    vector<Person_Record> records;
    slot_file_read(records);

    scheduler(records);

    print_final_schedule();
    misses(records);

    return 0;
}
