#include <iostream>
#include <fstream>
#include <string> 
#include <vector>
#include <algorithm>
#include <sstream>
using namespace std;

bool dampener_check(vector<int> report, int idx, bool asc, bool desc);
bool verify(vector<int>, int, bool);

int main() {
    string line;
    ifstream input("input.txt");
    vector<vector<int>> reports = vector<vector<int>>();
    while (getline (input, line)) {
        stringstream ss(line);
        vector<int> report = vector<int>();
        int num;
        while (ss.eof() == 0) {
            ss >> num;
            report.emplace_back(num);
        }
        reports.emplace_back(report);
    }
    input.close();

    // part 1
    int safe = 0;
    for (vector<int> report: reports) {
        if (verify(report, 0, true))
            safe += 1;
    }
    cout << safe << endl;

    // part 2
    safe = 0;
    for (vector<int> report: reports) {
        for (int idx = 0; idx < report.size(); idx++) {
            if (verify(report, idx, false)) {
                safe += 1;
                break;
            }
        }
    }
    cout << safe << endl;
}

// checks if the report is safe, removing idx
bool verify(vector<int> report, int idx, bool p1) {
    if (!p1)
        report.erase(report.begin() + idx);
    
    bool ascending  = true;
    bool descending = true;
    bool gradual = true;
    for (int idx = 1; idx < report.size(); idx++) {
        int dist = abs(report[idx - 1] - report[idx]);
        if (dist > 3 || dist < 1) {
            gradual = false;
            break;
        }
        if (report[idx - 1] > report[idx])
            ascending = false;
        if (report[idx - 1] < report[idx])
            descending = false;
    }

    return (ascending || descending) && gradual;
}
