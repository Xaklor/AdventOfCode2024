#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
using namespace std;

bool verify(int, long, vector<long>, bool);

int main() {
    string line;
    ifstream input("input.txt");
    vector<vector<long>> eqs = vector<vector<long>>();
    while (getline (input, line)) {
        line[line.find(':')] = ' ';
        stringstream ss(line);
        vector<long> eq;
        long num;
        while (ss.eof() == 0) {
            ss >> num;
            eq.emplace_back(num);
        }
        eqs.emplace_back(eq);
    }
    input.close();

    // part 1
    long total = 0;
    for(vector<long> eq: eqs) {
        if(verify(eq.size() - 1, eq[0], eq, true))
            total += eq[0];
    }
    cout << total << endl;

    // part 2
    total = 0;
    for(vector<long> eq: eqs) {
        if(verify(eq.size() - 1, eq[0], eq, false))
            total += eq[0];
    }
    cout << total << endl;
}

bool verify(int idx, long value, vector<long> eq, bool p1) {
    // base case
    if(idx <= 0)
        return value == 0;

    // if * is an option, the current remainder must be divisible by the current element
    bool mult_able = false;
    if(value % eq[idx] == 0)
        mult_able = verify(idx - 1, value / eq[idx], eq, p1);

    // if + is an option, the current remainder must be larger than the current element
    bool sum_able = false;
    if(value >= eq[idx])
        sum_able = verify(idx - 1, value - eq[idx], eq, p1);

    // if || is an option, the current remainder must end with and be longer than the current element
    bool cat_able = false;
    if(!p1) {
        string svalue = to_string(value);
        string token = to_string(eq[idx]);
        if(svalue.ends_with(token) && svalue != token)
            cat_able = verify(idx - 1, stol(svalue.substr(0, svalue.size() - token.size())), eq, p1);
    }

    return mult_able || sum_able || cat_able;
}