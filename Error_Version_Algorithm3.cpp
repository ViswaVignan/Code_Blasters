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
};

unordered_map<int,string> output_data; 


void scheduler(vector<Person_Record> &records)
{    
    for (int hour = 0; hour < 24; hour++)
    {   
        cout<<endl<<"ENTERED THE SLOT CHECKING LOOP."<<hour+1<<endl;
         
        int length = 0;
  
        for (const auto &record : records)
        { 
            length += record.time_slots[hour + 1];
        }
        cout<<"The length here is: "<<length<<endl<<endl;

        if (length > 1)
        {
            cout<<"Entered the length>1 condition"<<endl<<endl;
            
            unordered_set<string> common_series;           
            unordered_set<string> temp2;
            unordered_map<string ,int> max_common_series;

            for (const auto &record : records)
            {
                cout<<endl<<"Entered the 'for loop' in length>1 condition"<<endl;

                if (record.time_slots[hour + 1] == 1)
                {
                    for (const auto &series : record.Series_Names)
                    {
                        cout<<"Checking the series and series name is: "<<series<<endl;

                        max_common_series[series] ;
                        if (temp2.count(series) > 0)
                        {
                            common_series.insert(series);
                            max_common_series[series]++;
                            cout<<"common series are: ";
                            for (const auto &common_series_item : common_series) {
                                cout << common_series_item << " ";
                            }
                            cout << endl;
                            cout<<"Max common series are: ";
                            for (const auto &max_common_series_item : max_common_series){
                                cout << max_common_series_item.first << ": " << max_common_series_item.second << " ";
                            }
                            cout<<endl;
                        }
                        else{
                            temp2.insert(series);
                            max_common_series[series]++;
                        }
                    }
                }
            }
            if (common_series.size() >= 1) {
                cout<<"Entered the if condition which checks common_series.size()>1"<<endl;

                string most_common_series;
                int max_compare=0;
                
                for (string value : common_series){
                    cout<<"Entered the loop that checks for the maximum common series"<<endl;
                            for(const auto &data : max_common_series){  
                            int temp_for_max_compare=max_common_series[value];

                            if(temp_for_max_compare > max_compare){
                                max_compare = temp_for_max_compare;
                                most_common_series =value;
                            }
                        }
                        cout<<"The maximum and the series names are: "<<max_compare<<" and "<<most_common_series<<endl<<endl;

                }
                for (auto& record : records) { 
                        if (record.time_slots[hour + 1] == 1)
                        {
                            if (record.Series_Names.count(most_common_series) > 0) 
                            {
                            output_data[hour+1]+=record.Person_Name +" ("+ most_common_series +") ";
                            record.Series_Names.erase(most_common_series);
                            }
                            record.time_slots[hour + 1] = 0;
                            record.time_slots[0]--;
                            
                        }
                        cout<<"The data stored in the string is: "<<output_data[hour+1]<<endl<<endl; 
                        cout<<"Total available slots for person name "<<record.Person_Name<<" are: "<<record.time_slots[0]<<endl;
                        cout<<"The remaining available series for this person: ";
                        for(const auto & series_value : record.Series_Names){
                            cout<<series_value<<" ";
                        }
                        cout<<endl<<endl;
                } 
            }
            else
            {
                cout<<"Entered the else condition which checks the no common series case"<<endl;
               Person_Record*temp;
                int min=24;
                for (auto &record : records)
                {  if (record.time_slots[hour + 1] == 1)
                    {
                        if(record.time_slots[0]<min)
                        {
                            min=record.time_slots[0];
                            temp=&record;
                        }
                    }
                }
                string common_series_name = *temp->Series_Names.begin();

                 output_data[hour+1]=temp->Person_Name +" ("+ common_series_name +") ";   
                 temp->Series_Names.erase(common_series_name);

                 

                for (auto &record : records){  
                    if (record.time_slots[hour + 1] == 1)
                    {
                        record.time_slots[hour + 1] = 0;
                        record.time_slots[0]--;
                    }
                }
                cout<<"The data stored in the string is: "<<output_data[hour+1]<<endl<<endl; 
                        cout<<"Total available slots for person name "<<temp->Person_Name<<" are: "<<temp->time_slots[0]<<endl;
                        cout<<"The remaining available series for this person: ";
                        for(const auto & series_value : temp->Series_Names){
                            cout<<series_value<<" ";
                        }
                        cout<<endl<<endl;
            }
            cout<<"the else condition which checks the no common series case came to end"<<endl;
        }
        else 
        { 
            cout<<"Entered the else where continue is happening."<<endl;
           continue;
           
        }
    }
    for (int hour = 0; hour < 24; hour++)
    {
        cout<<endl<<"ENTERED THE SLOT CHECKING LOOP."<<hour+1<<endl;
        int length = 0; 
        for (const auto &record : records)
        { 
            length += record.time_slots[hour + 1];
        }
        cout<<"The length here is: "<<length<<endl;
        
        if (length == 1)
        {
            cout<<"Entered the condition 'if (length == 1)'"<<endl;
            for (auto &record : records)
            {
                cout<<"Entered the loop 'for (auto &record : records)' "<<endl;
                if (record.time_slots[hour + 1] == 1)
                {
                    if(record.Series_Names.size())
                    {
                        cout<<"Entered the 'if(record.Series_Names.size())' condition"<<endl;

                    string common_series_name = *record.Series_Names.begin();
                    output_data[hour+1]=record.Person_Name +" ("+ common_series_name +") ";   
                    record.Series_Names.erase(common_series_name);
                    }
                    record.time_slots[hour + 1] = 0;
                    record.time_slots[0]--;

                    cout<<"The data stored in the string is: "<<output_data[hour+1]<<endl<<endl;
                        cout<<"Total available slots for person name "<<record.Person_Name<<" are: "<<record.time_slots[0]<<endl;
                        cout<<"The remaining available series for this person: ";
                        for(const auto & series_value : record.Series_Names){
                            cout<<series_value<<" ";
                        }
                        cout<<endl<<endl;
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

void print_final_schedule()
{
    const string RED_COLOR = "\033[31m";
    const string GREEN_COLOR = "\033[32m";
    const string RESET_COLOR = "\033[0m";
    const string CYAN_COLOR = "\033[36m";
    const string BLUE_COLOR = "\033[34m";
   cout << CYAN_COLOR << "FINAL SCHEDULE: " << RESET_COLOR << endl;
   for(int hour=1;hour<25;hour++)
   {
    cout << GREEN_COLOR << "SLOT "<<hour<<": " << RESET_COLOR;
    if(output_data[hour-1].empty())
      {
        cout << RED_COLOR << "NO ONE HAS BEEN ALLOCATED TO THIS SLOT" << RESET_COLOR << endl;
      }
    else
    {
        cout << BLUE_COLOR << output_data[hour-1] << RESET_COLOR << endl;
    }
   }
}

void misses(vector<Person_Record> &records)
{
    int total_misses=0;
     for (const auto &record : records)
    {
        total_misses+=record.Series_Names.size();
    }
   cout<<"\n THE TOTAL NUMBER OF SERIES MISSED: "<<total_misses<<endl; 
}

int main()
{   
    vector<string> available_series;
    series_file_read(available_series);vector<Person_Record> records;
    slot_file_read(records);
    scheduler(records);
    cout<<"scheduling successful";

    print_final_schedule();

    misses(records);

    return 0;
}
