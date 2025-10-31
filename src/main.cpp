#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <algorithm> 
#include <cctype>
#include <locale>
#include <cstdio>
#include <iomanip>
#include <map>
#include <queue>
#include "BinaryHeap.h"
#include "Crime.h"
#include <vector>

using namespace std;


string trim(const string& s) {
    string result = s;
    // remove leading whitespace and \r
    result.erase(result.begin(), find_if(result.begin(), result.end(),
        [](unsigned char ch){ return !isspace(ch) && ch != '\r'; }));
    // remove trailing whitespace and \r
    result.erase(find_if(result.rbegin(), result.rend(),
        [](unsigned char ch){ return !isspace(ch) && ch != '\r'; }).base(), result.end());
    return result;
}



int safeStoi(const string& s){
    try{
        return stoi(s);
    }catch(...){
        return 0;
    }
}

double safeStod(const string& s){
    try{
        return stod(s);
    }catch(...){
        return 0.0;
    }
}

Crime parseLine(const string& line){
    Crime c; //create crime object
    stringstream ss(line); //instantiate stringstream
    string cell; //each of the cell is a string

    getline(ss, c.INCIDENT_NUMBER, ',');
    getline(ss, c.OFFENSE_CODE, ',');
    getline(ss, c.OFFENSE_CODE_GROUP, ',');
    getline(ss, c.OFFENSE_DESCRIPTION, ',');
    getline(ss, c.DISTRICT, ',');
    getline(ss, c.REPORTING_AREA, ',');
    getline(ss, c.SHOOTING, ',');
    getline(ss, c.OCCURRED_ON_DATE, ',');

    getline(ss, cell, ',');
    c.YEAR = safeStoi(cell);
    getline(ss, cell, ',');
    c.MONTH = safeStoi(cell);
    // getline(ss, cell, ',');
    // cout << "DAY_OF_WEEK raw: " << "[" << cell << "]" << endl;
    // c.DAY_OF_WEEK = trim(cell);
    // getline(ss, cell, ',');
    // // cout << "HOUR raw: " << "[" << cell << "]" << endl;
    // c.HOUR = safeStoi(trim(cell));
    // --------DAY OF WEEK -------------
    getline(ss, cell, ',');
    c.DAY_OF_WEEK = trim(cell);
// -------- TIME from OCCURRED_ON_DATE -----
    int h = 0, m = 0;
    size_t sp = c.OCCURRED_ON_DATE.find(' ');
    if (sp != string::npos) {
        string t = c.OCCURRED_ON_DATE.substr(sp + 1);  // "19:27:00"
        size_t c1 = t.find(':');
        size_t c2 = t.find(':', c1 + 1);
        if (c1 != string::npos) {
            h = safeStoi(t.substr(0, c1));
            if (c2 != string::npos)
            m = safeStoi(t.substr(c1 + 1, c2 - c1 - 1));        }
    }
    c.time = {h, m};
// ----------------------------------------------

    getline(ss, c.UCR_PART, ',');
    getline(ss, c.STREET, ',');
    getline(ss, cell, ',');
    c.Lat = safeStod(cell);
    getline(ss, cell, ','); 
    c.Long = safeStod(cell);

    //read rest of the line as Location
    getline(ss, c.Location);
    return c;
}

string toUpper(string s){
    transform(s.begin(), s.end(), s.begin(), ::toupper);
    return s;
}


int main(int argc, char* argv[]) {
    const string filename = "src/crime.csv";
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Failed to open file: " << filename << endl;
        return 1;
    }

    map<string, vector<Crime>> districtMap;
    string filter;  // ← DECLARED HERE
    string line;
    getline(file, line);  // skip header

    // READ + BUILD districtMap + EARLY FILTER
    while (getline(file, line)) {
        Crime c = parseLine(line);
        string d = trim(c.DISTRICT);
        if (d.empty()) d = "UNKNOWN";  // ← fixed "UNKOWN"

        // EARLY FILTER
        if (!filter.empty() && toUpper(d) != filter)
            continue;

        districtMap[d].push_back(c);
    }
    file.close();

    // SET FILTER FROM COMMAND LINE
    if (argc > 1) {
        filter = toUpper(argv[1]);
        cout << "Filtering for District: " << argv[1] << "\n\n";
    }

    // BUILD DISTRICT PRIORITY QUEUE
    priority_queue<string, vector<string>, greater<string>> districtPQ;
    for (const auto& p : districtMap) {
        if (filter.empty() || toUpper(p.first) == filter)
            districtPQ.push(p.first);
    }

    if (districtPQ.empty()) {
        cout << "No crimes found for district: "
             << (argc > 1 ? argv[1] : "any") << "\n";  // ← fixed /n
        return 0;
    }

    // PRINT EACH DISTRICT WITH BINARY HEAP
    while (!districtPQ.empty()) {
        string district = districtPQ.top(); districtPQ.pop();
        cout << "District " << district << "\n";
        cout << "Binary heap sorted by district:\n";  // ← fixed typo

        BinaryHeap heap;
        for (const auto& c : districtMap[district])
            heap.push(c);

        while (!heap.empty()) {
            Crime c = heap.pop();
            cout << "  " << c.OFFENSE_DESCRIPTION << " - " << c.time.str() << "\n";
        }
        cout << "\n";
    }

    return 0;
}
