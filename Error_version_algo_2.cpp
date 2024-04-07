#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <unordered_map>
#include <unordered_set>

using namespace std;

struct TimeSlot {
    string start;
    string end;
};

struct Person {
    string name;
    unordered_set<string> series;
    vector<TimeSlot> availability;
};

void parseSeries(const string& seriesFile, unordered_set<string>& allSeries) {
    ifstream inFile(seriesFile);
    if (!inFile) {
        cerr << "Error: Unable to open series file." << endl;
        exit(1);
    }

    string line;
    getline(inFile, line); // Read the whole line
    istringstream iss(line);
    string series;
    while (getline(iss, series, ',')) {
        allSeries.insert(series);
    }

    inFile.close();
}

void parseData(const string& dataFile, unordered_map<string, Person>& people, unordered_set<string>& allSeries) {
    ifstream inFile(dataFile);
    if (!inFile) {
        cerr << "Error: Unable to open data file." << endl;
        exit(1);
    }

    string line;
    while (getline(inFile, line)) {
        istringstream iss(line);
        string name, series;
        getline(iss, name, ',');
        Person person;
        person.name = name;
        
        getline(iss, series, ',');
        istringstream ss(series);
        string favorite;
        while (ss >> favorite) {
            person.series.insert(favorite);
            allSeries.insert(favorite);
        }

        string slot;
        while (getline(iss, slot, ',')) {
            TimeSlot timeSlot;
            if (slot == "1") {
                timeSlot.start = to_string(person.availability.size());
                timeSlot.end = to_string(person.availability.size() + 1);
            }
            person.availability.push_back(timeSlot);
        }
        people[name] = person;
    }

    inFile.close();
}

void scheduleTVShows(const unordered_map<string, Person>& people, const unordered_set<string>& allSeries) {
    vector<vector<string>> schedule(24, vector<string>());
    unordered_set<string> scheduled;

    for (const auto& series : allSeries) {
        vector<string> candidates;
        for (const auto& person : people) {
            if (person.second.series.find(series) != person.second.series.end()) {
                candidates.push_back(person.first);
            }
        }
        if (!candidates.empty()) {
            bool found = false;
            for (int i = 0; i < 24; ++i) {
                if (schedule[i].empty()) {
                    bool timeSlotAvailable = true;
                    for (const auto& candidate : candidates) {
                        if (people.at(candidate).availability[i].start == "") {
                            timeSlotAvailable = false;
                            break;
                        }
                    }
                    if (timeSlotAvailable) {
                        for (const auto& candidate : candidates) {
                            schedule[i].push_back(candidate + " (" + series + ")");
                            scheduled.insert(series);
                        }
                        found = true;
                    }
                }
                if (found) break;
            }
        }
    }

    cout << "Final Schedule:" << endl;
    for (int i = 0; i < 24; ++i) {
        string slotStart = (i < 10) ? "0" + to_string(i) + ":00" : to_string(i) + ":00";
        string slotEnd = ((i + 1) % 24 < 10) ? "0" + to_string((i + 1) % 24) + ":00" : to_string((i + 1) % 24) + ":00";
        cout << slotStart << " - " << slotEnd << ": ";
        for (const auto& show : schedule[i]) {
            cout << show << " ";
        }
        cout << endl;
    }

    int missed = allSeries.size() - scheduled.size();
    cout << "Misses (unscheduled series): " << missed << endl;
}


int main() {
    unordered_map<string, Person> people;
    unordered_set<string> allSeries;

    string dataFile = "slots.csv";
    string seriesFile = "series.csv";

    parseSeries(seriesFile, allSeries);
    parseData(dataFile, people, allSeries);
    scheduleTVShows(people, allSeries);

    return 0;
}
