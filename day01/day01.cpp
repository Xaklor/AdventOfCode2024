#include <iostream>
#include <fstream>
#include <string> 
#include <vector>
#include <algorithm>
#include <sstream>
using namespace std;

int main() {
    string line;
    vector<int> left;
    vector<int> right;
    ifstream input("input.txt");
    while (getline (input, line)) {
        stringstream ss(line);        
        int l, r;
        ss >> l;
        ss >> r;
        left.push_back(l);
        right.push_back(r);
    }
    input.close();
    ranges::sort(left);
    ranges::sort(right);

    // part 1
    int total = 0;
    for (int idx = 0; idx < left.size(); idx++) {
        total += abs(left[idx] - right[idx]);
    }
    cout << "part 1 result: " << total << endl;

    // part 2
    total = 0;
    for (int a: left) {
        int count = 0;
        for (int b: right) {
            if (a == b)
                count += 1;
        }
        total += a * count;
    }
    cout << "part 2 result: " << total << endl;
}