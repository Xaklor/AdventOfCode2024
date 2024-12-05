#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <algorithm>
#include <unordered_set>
#include <unordered_map>
using namespace std;

bool wacky_comparator(int, int);
// key must appear before everything in values to be valid
unordered_map<int, unordered_set<int>> rules;

int main () {
    string line;
    ifstream input("input.txt");
    getline(input, line);
    while (line != "") {
        int first = stoi(line.substr(0, 2));
        int second = stoi(line.substr(3, 2));
        if(rules.contains(first))
            rules[first].insert(second);
        else
            rules[first] = unordered_set{second};

        getline(input, line);
    }

    vector<vector<int>> updates;
    while(getline(input, line)) {
        vector<int> update;
        stringstream ss(line);
        int num;
        while(ss >> num){
            update.push_back(num);
            ss.get();
        }

        updates.push_back(update);
    }
    input.close();

    // part 1
    int total = 0;
    for(vector<int> update: updates) {
        if(ranges::is_sorted(update, wacky_comparator))
            total += update[update.size() / 2];
    }
    cout << total << endl;

    // part 2
    total = 0;
    for(vector<int> update: updates) {
        if(!ranges::is_sorted(update, wacky_comparator)){
            ranges::sort(update, wacky_comparator);
            total += update[update.size() / 2];
        }
    }
    cout << total << endl;
}

bool wacky_comparator(int a, int b) {
    if (!rules.contains(a))
        return false;

    return rules[a].contains(b);
}