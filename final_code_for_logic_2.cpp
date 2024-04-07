#include <climits>
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <string>
#include <unordered_set>
#include <unordered_map>
#include <list>
#include <algorithm> // for std::sort

using namespace std;

struct Person_Record
{
    string Person_Name;
    unordered_set<string> Series_Names;
    int time_slots[25];
};

struct Node
{
    string Person_Name;
    unordered_set<string> Series_Names;
    int time_slots[25];
    Node *next;
};

void printRecords(const vector<Person_Record> &records)
{
    for (const Person_Record &record : records)
    {
        cout << "Person Name: " << record.Person_Name << endl;
        cout << "Total Available Slots: " << record.time_slots[0] << endl;
        cout << "Available Slot Timings:" << endl;
        for (int i = 1; i <= 24; i++)
        {
            if (record.time_slots[i] == 1)
            {
                cout << "Hour " << i << ": Available" << endl;
            }
            else
            {
                cout << "Hour " << i << ": Not Available" << endl;
            }
        }
        cout << endl;
    }
}

void printAvailableSeries(const vector<string> &available_series)
{
    cout << "Available Series:" << endl;
    for (const string &series : available_series)
    {
        cout << series << endl;
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

    getline(file, line);

    while (getline(file, line))
    {
        stringstream ss(line);
        string name, series_names, time_slots;

        getline(ss, name, ',');
        getline(ss, series_names, ',');
        getline(ss, time_slots);

        Person_Record record;
        record.Person_Name = name;

        stringstream series_ss(series_names);
        string series_name;
        while (getline(series_ss, series_name, ' '))
        {
            record.Series_Names.insert(series_name);
        }

        stringstream slots_ss(time_slots);
        int hour = 0;
        string slot;
        while (getline(slots_ss, slot, ','))
        {
            int value = stoi(slot);
            record.time_slots[hour + 1] = value;
            hour++;
        }

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
    printRecords(records);
}

void series_file_read(vector<string> &available_series)
{
    ifstream file("final_series_input.csv");
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

        while (getline(ss, series_name, ','))
        {
            available_series.push_back(series_name);
        }
    }
}

void find_and_update_clashes(vector<Person_Record> &records, unordered_map<string, string> &schedule_map, const vector<string> &available_series)
{
    for (int hour = 0; hour < 24; hour++)
    {
        string slot_key = to_string(hour) + ":00-" + to_string((hour + 1) % 24) + ":00";

        list<Node *> clashes;

        for (Person_Record &record : records)
        {
            if (record.time_slots[hour + 1] == 1)
            {
                Node *newNode = new Node;
                newNode->Person_Name = record.Person_Name;
                newNode->Series_Names = record.Series_Names;
                for (int i = 0; i < 25; i++)
                {
                    newNode->time_slots[i] = record.time_slots[i];
                }
                if (!(newNode->Series_Names.empty()))
                {
                    clashes.push_back(newNode);
                }
                if (newNode->Series_Names.empty())
                {
                    record.time_slots[hour + 1] = 0;
                    record.time_slots[0]--;
                }
            }
        }

        if (clashes.empty())
        {
            cout << slot_key << ": Empty slot" << endl;
            continue;
        }

        if (clashes.size() == 1)
        {
            Node *node = clashes.front();
            string most_common_series = *(node->Series_Names.begin());
            string schedule_entry = node->Person_Name + " (" + most_common_series + ") ";

            node->time_slots[hour + 1] = 0;
            node->Series_Names.erase(most_common_series);

            for (Person_Record &record : records)
            {
                if (record.Person_Name == node->Person_Name)
                {
                    record.Series_Names.erase(most_common_series);
                    record.time_slots[hour + 1] = 0;
                    break;
                }
            }
            schedule_map[slot_key] = schedule_entry;
            cout << "Time Slot: " << slot_key << " - Persons: " << schedule_map[slot_key] << endl;
        }
        else if (!clashes.empty())
        {
            unordered_map<string, int> series_count;
            for (const string &series : available_series)
            {
                series_count[series] = 0;
            }

            for (const Node *node : clashes)
            {
                for (const string &series : node->Series_Names)
                {
                    if (series_count.find(series) != series_count.end())
                    {
                        series_count[series]++;
                    }
                }
            }

            vector<string> max_series;
            int max_count = 0;
            for (const auto &pair : series_count)
            {
                if (pair.second > max_count)
                {
                    max_series.clear();
                    max_series.push_back(pair.first);
                    max_count = pair.second;
                }
                else if (pair.second == max_count)
                {
                    max_series.push_back(pair.first);
                }
            }

            if (max_series.size() > 1)
            {
                unordered_map<string, int> series_slots;
                for (const string &series : max_series)
                {
                    series_slots[series] = 0;
                }

                for (const Node *node : clashes)
                {
                    for (const string &series : node->Series_Names)
                    {
                        if (series_slots.find(series) != series_slots.end())
                        {
                            series_slots[series] += node->Series_Names.count(series);
                        }
                    }
                }

                string most_common_series;
                int max_net_count = INT_MIN;
                for (const auto &pair : series_slots)
                {
                    int net_count = pair.second - max_count;
                    if (net_count > max_net_count)
                    {
                        most_common_series = pair.first;
                        max_net_count = net_count;
                    }
                }

                string schedule_entry;
                for (Node *node : clashes)
                {
                    if (node->Series_Names.find(most_common_series) != node->Series_Names.end())
                    {
                        schedule_entry += node->Person_Name + " (" + most_common_series + ") ";
                        node->time_slots[hour + 1] = 0;
                        node->Series_Names.erase(most_common_series);
                        for (Person_Record &record : records)
                        {
                            if (record.Person_Name == node->Person_Name)
                            {
                                record.Series_Names.erase(most_common_series);
                                record.time_slots[hour + 1] = 0;
                                record.time_slots[0]--;
                                break;
                            }
                        }
                    }
                }

                schedule_map[slot_key] = schedule_entry;
                cout << "Time Slot: " << slot_key << " - Persons: " << schedule_map[slot_key] << endl;
            }
            else
            {
                string most_common_series = max_series[0];
                string schedule_entry;
                for (Node *node : clashes)
                {
                    if (node->Series_Names.find(most_common_series) != node->Series_Names.end())
                    {
                        schedule_entry += node->Person_Name + " (" + most_common_series + ") ";
                        node->time_slots[hour + 1] = 0;
                        node->Series_Names.erase(most_common_series);
                        for (Person_Record &record : records)
                        {
                            if (record.Person_Name == node->Person_Name)
                            {
                                record.Series_Names.erase(most_common_series);
                                record.time_slots[hour + 1] = 0;
                                record.time_slots[0]--;
                                break;
                            }
                        }
                    }
                }

                schedule_map[slot_key] = schedule_entry;
                cout << "Time Slot: " << slot_key << " - Persons: " << schedule_map[slot_key] << endl;
            }
        }
        else
        {
            schedule_map[slot_key] = "No person free here";
        }

        for (Node *node : clashes)
        {
            delete node;
        }
    }
}

void total_misses(const vector<Person_Record> &records)
{
    int total_misses = 0;
    for (const Person_Record &record : records)
    {
        total_misses += record.Series_Names.size();
    }
    cout << "Total misses: " << total_misses << endl;
}

int main()
{
    vector<string> available_series;
    series_file_read(available_series);

    vector<Person_Record> records;
    slot_file_read(records);

    printAvailableSeries(available_series);

    unordered_map<string, string> schedule_map;

    find_and_update_clashes(records, schedule_map, available_series);

    total_misses(records);

    return 0;
}
