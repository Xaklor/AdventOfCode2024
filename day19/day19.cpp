#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_set>
#include <string.h>
using namespace std;

int main() {
    string line;
    ifstream input("input.txt");
    unordered_set<string> towels;
    getline(input, line);
    while(line != "") {
        towels.insert(line.substr(0, line.find(',')));
        line = line.substr(line.find(',') + 1);
    }
    getline(input, line);

    vector<string> patterns;
    while(getline(input, line)) {
        patterns.emplace_back(line);
    }

    int possible = 0; long total = 0;
    for(int _ = 0; _ < patterns.size(); _++) {
        string pattern = patterns[_];
        bool t1[pattern.size() + 1]; memset(t1, 0, sizeof(t1));
        long t2[pattern.size() + 1]; memset(t2, 0, sizeof(t2));
        t1[pattern.size()] = true;
        t2[pattern.size()] = 1;
        for(int i = pattern.size() - 1; i >= 0; i--) {
            for(int j = 1; j <= pattern.size() - i; j++) {
                if(towels.contains(pattern.substr(i, j))) {
                    t1[i] |= t1[i + j];
                    t2[i] += t2[i + j];
                }
            }
        }
        if(t1[0]) possible++;
        total += t2[0];
    }
    cout << possible << endl;
    cout << total << endl;
}