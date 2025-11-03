// src/main.cpp — Boston Crime Database Analyzer
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <algorithm>
#include <cctype>
#include <map>
#include <queue>
#include <limits>
#include <cstdio>
#include "Crime.h"
#include "BinaryHeap.h"
#include "TernaryHeap.h"

using namespace std;

string trim(const string& s) {
    string r = s;
    r.erase(r.begin(), find_if(r.begin(), r.end(),
        [](unsigned char ch){ return !isspace(ch) && ch != '\r'; }));
    r.erase(find_if(r.rbegin(), r.rend(),
        [](unsigned char ch){ return !isspace(ch) && ch != '\r'; }).base(), r.end());
    return r;
}

int safeStoi(const string& s) {
    try { return stoi(s); } catch (...) { return 0; }
}

Crime parseLine(const string& line) {
    Crime c;
    stringstream ss(line);
    string cell;

    getline(ss, c.INCIDENT_NUMBER, ',');
    getline(ss, c.OFFENSE_CODE, ',');
    getline(ss, c.OFFENSE_CODE_GROUP, ',');
    getline(ss, c.OFFENSE_DESCRIPTION, ',');
    getline(ss, c.DISTRICT, ',');
    getline(ss, c.REPORTING_AREA, ',');
    getline(ss, c.SHOOTING, ',');
    getline(ss, c.OCCURRED_ON_DATE, ',');

    getline(ss, cell, ','); c.YEAR = safeStoi(cell);
    getline(ss, cell, ','); c.MONTH = safeStoi(cell);
    getline(ss, cell, ','); c.DAY_OF_WEEK = trim(cell);

    // Parse time from OCCURRED_ON_DATE
    int h = 0, m = 0;
    size_t sp = c.OCCURRED_ON_DATE.find(' ');
    if (sp != string::npos) {
        string t = c.OCCURRED_ON_DATE.substr(sp + 1);
        size_t c1 = t.find(':');
        size_t c2 = t.find(':', c1 + 1);
        if (c1 != string::npos) {
            h = safeStoi(t.substr(0, c1));
            if (c2 != string::npos)
                m = safeStoi(t.substr(c1 + 1, c2 - c1 - 1));
        }
    }
    c.time = {h, m};

    getline(ss, c.UCR_PART, ',');
    getline(ss, c.STREET, ',');
    getline(ss, cell, ','); c.Lat = safeStoi(cell);
    getline(ss, cell, ','); c.Long = safeStoi(cell);
    getline(ss, c.Location);
    return c;
}

string toUpper(string s) {
    transform(s.begin(), s.end(), s.begin(), ::toupper);
    return s;
}

int main(int argc, char* argv[]) {
    // Fast I/O
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // === CLI BANNER ===
    cout << "=======================================\n";
    cout << "   BOSTON CRIME DATABASE ANALYZER\n";
    cout << "=======================================\n\n";

    // === PARSE COMMAND LINE ===
    if (argc < 2) {
        cout << "Usage: main.exe <DISTRICT> [MAX_CRIMES]\n";
        cout << "Examples:\n";
        cout << "  main.exe B2              → show up to 50 crimes\n";
        cout << "  main.exe B2 10           → show top 10 from each heap\n";
        cout << "  main.exe B2 0            → show all crimes\n";
        return 1;
    }

    string requested = toUpper(trim(argv[1]));
    int maxDisplay = 50;  // default
    if (argc >= 3) {
        try {
            maxDisplay = stoi(argv[2]);
            if (maxDisplay <= 0) maxDisplay = INT_MAX;
        } catch (...) {
            maxDisplay = 50;
        }
    }

    cout << "Searching for District: " << argv[1] 
         << (argc >= 3 ? " (max " + string(argv[2]) + ")" : "") << "\n\n";

    // === READ CSV — ONLY REQUESTED DISTRICT ===
    const string filename = "crime.csv";
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "ERROR: Cannot open " << filename << "\n";
        return 1;
    }

    vector<Crime> crimes;
    string line;
    getline(file, line);  // skip header

    while (getline(file, line)) {
        Crime c = parseLine(line);
        string d = trim(c.DISTRICT);
        if (d.empty()) d = "UNKNOWN";
        if (toUpper(d) == requested) {
            crimes.push_back(c);
        }
    }
    file.close();

    // === NO CRIMES FOUND ===
    if (crimes.empty()) {
        cout << "No crimes found for district: " << argv[1] << "\n";
        return 0;
    }

    // === DISPLAY HEADER ===
    cout << "District " << requested << " (" << crimes.size() << " total crimes)\n";
    if (maxDisplay < crimes.size() && maxDisplay != INT_MAX) {
        cout << "Showing top " << maxDisplay << " from each heap.\n";
    } else {
        cout << "Showing all crimes.\n";
    }
    cout << string(60, '-') << "\n\n";

    // === BINARY HEAP: Sorted by TIME ===
    cout << "Binary heap (sorted by TIME):\n";
    BinaryHeap timeHeap;
    for (const auto& c : crimes) timeHeap.push(c);
    
    int count = 0;
    while (!timeHeap.empty() && count < maxDisplay) {
        Crime c = timeHeap.pop();
        cout << "  " << c.time.str() << " - " << c.OFFENSE_DESCRIPTION << "\n";
        ++count;
    }
    if (count == 0) cout << "  (none)\n";
    cout << "\n";

    // === TERNARY HEAP: Sorted by SEVERITY ===
    cout << "Ternary heap (sorted by OFFENSE_CODE severity):\n";
    TernaryHeap sevHeap;
    for (const auto& c : crimes) sevHeap.push(c);
    
    count = 0;
    while (!sevHeap.empty() && count < maxDisplay) {
        Crime c = sevHeap.pop();
        cout << "  [" << c.OFFENSE_CODE << "] " << c.OFFENSE_DESCRIPTION << "\n";
        ++count;
    }
    if (count == 0) cout << "  (none)\n";
    cout << "\n";

    cout << "Analysis complete.\n";
    return 0;
}
