#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

int main() {
    string line;
    ifstream input("input.txt");
    vector<vector<long>> machines;
    while(getline(input, line)) {
        vector<long> machine;
        machine.emplace_back(stol(line.substr(12, 2)));
        machine.emplace_back(stol(line.substr(18, 2)));

        getline(input, line);
        machine.emplace_back(stol(line.substr(12, 2)));
        machine.emplace_back(stol(line.substr(18, 2)));

        getline(input, line);
        machine.emplace_back(stol(line.substr(9, line.find(','))));
        machine.emplace_back(stol(line.substr(line.find('Y') + 2)));
        machine.emplace_back(stol(line.substr(9, line.find(','))) + 10000000000000);
        machine.emplace_back(stol(line.substr(line.find('Y') + 2)) + 10000000000000);

        getline(input, line);
        machines.emplace_back(machine);
    }
    input.close();

    long p1_total = 0;
    long p2_total = 0;
    for(vector<long> machine: machines) {
        // formula for solving systems of equations: 
        // X = (BF - EC) / (DB - EA), Y = (C - AX) / B where
        // AX + BY = C
        // DX + EY = F

        // part 1
        if(((machine[2] * machine[5]) - (machine[3] * machine[4])) % ((machine[1] * machine[2]) - (machine[3] * machine[0])) == 0) {
            long a = ((machine[2] * machine[5]) - (machine[3] * machine[4])) / ((machine[1] * machine[2]) - (machine[3] * machine[0]));
            if((machine[4] - (a * machine[0])) % machine[2] == 0) {
                long b = (machine[4] - (a * machine[0])) / machine[2];
                p1_total += 3 * a + b;
            }
        }
        // part 2
        if(((machine[2] * machine[7]) - (machine[3] * machine[6])) % ((machine[1] * machine[2]) - (machine[3] * machine[0])) == 0) {
            long a = ((machine[2] * machine[7]) - (machine[3] * machine[6])) / ((machine[1] * machine[2]) - (machine[3] * machine[0]));
            if((machine[6] - (a * machine[0])) % machine[2] == 0) {
                long b = (machine[6] - (a * machine[0])) / machine[2];
                p2_total += 3 * a + b;
            }
        }
    }
    cout << p1_total << endl;
    cout << p2_total << endl;
}