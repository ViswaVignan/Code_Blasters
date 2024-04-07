#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <string>
#include <unordered_set>
#include <unordered_map>

using namespace std;

struct Person_Record
{
    string Person_Name;
    unordered_set<string> Series_Names;
    int time_slots[25];
    int total_series;
};

unordered_map<int, string> output_data; .
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

            unordered_set<string> common_series;
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
                            output_data[hour + 1] += record.Person_Name + " (" + most_common_series + ") ";
                            record.Series_Names.erase(most_common_series);
                        }
                        record.time_slots[hour + 1] = 0;
                        record.time_slots[0]--;
                    }
                }
            }
           
            else
            {
                int min = 24;
                int i=0,index_person=0;

                vector<Person_Record> min_condition;
      
                for (auto &record : records)
                {
                    if (record.time_slots[hour + 1] == 1)
                    {
                        if (record.total_series - record.Series_Names.size() < p)
                        {
                            min_condition.push_back(record);
                        }
                    }
                }
               
                for (auto it = min_condition.begin(); it != min_condition.end(); ++it)
                {
                    if(it->time_slots[0]==1 || it->time_slots[0] - it->Series_Names.size() <= min )
                    {
                        min= it->time_slots[0] - it->Series_Names.size();
                        index_person =i;
                    }
                    i++;

                }
                if (min_condition.at(index_person).Series_Names.size())
                {
                   string common_series_name = *(min_condition.at(index_person).Series_Names.begin());
                   output_data[hour + 1] = min_condition.at(index_person).Person_Name + " (" + common_series_name + ") ";
                   min_condition.at(index_person).Series_Names.erase(common_series_name);
                }
                
  

                for (auto &record : records)
                {
                    if (record.time_slots[hour + 1] == 1)
                    {
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
    for (int hour = 0; hour < 24; hour++)
    {

        int length = 0; 
        for (const auto &record : records)
        {
            length += record.time_slots[hour + 1]; 
        }

        if (length == 1)
        {
            for (auto &record : records)
            {

                if (record.time_slots[hour + 1] == 1)
                {
                    if (record.Series_Names.size())
                    {
                        string common_series_name = *record.Series_Names.begin();
                        output_data[hour + 1] = record.Person_Name + " (" + common_series_name + ") ";
                        record.Series_Names.erase(common_series_name);
                    }
                    record.time_slots[hour + 1] = 0;
                    record.time_slots[0]--;
                }
            }
        }
    }
}

void slot_file_read(vector<Person_Record> &records)
{
    ifstream file("input.csv");
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
       
        record.total_series = record.Series_Names.size();
        
        records.push_back(record);
    }
}

void series_file_read(vector<string> &available_series)
{
    ifstream file("series_input.csv");
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

#include <iomanip> 

void print_final_schedule()
{
    
    const string RED_COLOR = "\033[31m";
    const string GREEN_COLOR = "\033[32m";
    const string RESET_COLOR = "\033[0m";
    const string CYAN_COLOR = "\033[36m";
    const string BLUE_COLOR = "\033[34m";

    cout << CYAN_COLOR << "FINAL SCHEDULE: " << RESET_COLOR << endl;
    for (int hour = 1; hour < 25; hour++)
    {
        cout << GREEN_COLOR << setw(8) << "SLOT " << hour << " " << RESET_COLOR << setw(2) << hour - 1 << ":00-" << hour << ":00 - ";
        if (output_data[hour - 1].empty())
        {
            cout << RED_COLOR << "NO ONE HAS BEEN ALLOCATED TO THIS SLOT" << RESET_COLOR << endl;
        }
        else
        {
            cout << BLUE_COLOR << output_data[hour - 1] << RESET_COLOR << endl;
        }
    }
}
void misses(vector<Person_Record> &records)
{
    int total_misses = 0;
    for (const auto &record : records)
    {
        total_misses += record.Series_Names.size();
    }
    cout << "\n THE TOTAL NUMBER OF SERIES MISSED: " << total_misses << endl;
}
int main()
{
    vector<string> available_series;
    series_file_read(available_series);

    vector<Person_Record> records;
    slot_file_read(records);

    scheduler(records);
    print_final_schedule();
    misses(records);

    return 0;
}
