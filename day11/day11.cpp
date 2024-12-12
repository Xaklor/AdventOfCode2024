#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <string.h>
#include <unordered_set>
#include <unordered_map>
using namespace std;

// this is the set of numbers from which you cannot leave while following the split rules, I expect the bulk of the stones to be in this set
const unordered_set<int> basics = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 20, 24, 26, 28, 32, 36, 40, 48, 56, 57, 60, 67, 72, 77, 80, 84, 86, 91, 94, 96,
                                    2024, 2048, 2457, 2608, 2867, 2880, 3277, 3686, 4048, 6032, 6072, 8096, 9184, 9456, 10120, 12144, 14168, 16192, 
                                    18216, 20482880, 24579456, 28676032, 32772608, 36869184 };
int main() {
    string line;
    ifstream input("input.txt");
    vector<long> nonbasic_stones;
    unordered_map<int, long> basic_stones;
    for(int b: basics)
        basic_stones[b] = 0;

    getline(input, line);
    stringstream ss(line);
    int num;
    while (ss.eof() == 0) {
        ss >> num;
        if(basics.contains(num)) 
            basic_stones[num]++;
        else
            nonbasic_stones.emplace_back(num);
    }

    input.close();

    int steps = 0;
    unordered_map<int, long> new_basics;
    // change this to 25 for p1
    while(steps < 75) {
        for(int b: basics)
            new_basics[b] = 0;

        for(long type: basics) {
            switch(type) {
                case 0:        new_basics[1]     += basic_stones[type]; break;
                case 1:        new_basics[2024]  += basic_stones[type]; break;
                case 2:        new_basics[4048]  += basic_stones[type]; break;
                case 3:        new_basics[6072]  += basic_stones[type]; break;
                case 4:        new_basics[8096]  += basic_stones[type]; break;
                case 5:        new_basics[10120] += basic_stones[type]; break;
                case 6:        new_basics[12144] += basic_stones[type]; break;
                case 7:        new_basics[14168] += basic_stones[type]; break;
                case 8:        new_basics[16192] += basic_stones[type]; break;
                case 9:        new_basics[18216] += basic_stones[type]; break;
                case 20:       new_basics[2]  += basic_stones[type]; new_basics[0]  += basic_stones[type]; break;
                case 24:       new_basics[2]  += basic_stones[type]; new_basics[4]  += basic_stones[type]; break;
                case 26:       new_basics[2]  += basic_stones[type]; new_basics[6]  += basic_stones[type]; break;
                case 28:       new_basics[2]  += basic_stones[type]; new_basics[8]  += basic_stones[type]; break;
                case 32:       new_basics[3]  += basic_stones[type]; new_basics[2]  += basic_stones[type]; break;
                case 36:       new_basics[3]  += basic_stones[type]; new_basics[6]  += basic_stones[type]; break;
                case 40:       new_basics[4]  += basic_stones[type]; new_basics[0]  += basic_stones[type]; break;
                case 48:       new_basics[4]  += basic_stones[type]; new_basics[8]  += basic_stones[type]; break;
                case 56:       new_basics[5]  += basic_stones[type]; new_basics[6]  += basic_stones[type]; break;
                case 57:       new_basics[5]  += basic_stones[type]; new_basics[7]  += basic_stones[type]; break;
                case 60:       new_basics[6]  += basic_stones[type]; new_basics[0]  += basic_stones[type]; break;
                case 67:       new_basics[6]  += basic_stones[type]; new_basics[7]  += basic_stones[type]; break;
                case 72:       new_basics[7]  += basic_stones[type]; new_basics[2]  += basic_stones[type]; break;
                case 77:       new_basics[7]  += basic_stones[type]; new_basics[7]  += basic_stones[type]; break;
                case 80:       new_basics[8]  += basic_stones[type]; new_basics[0]  += basic_stones[type]; break;
                case 84:       new_basics[8]  += basic_stones[type]; new_basics[4]  += basic_stones[type]; break;
                case 86:       new_basics[8]  += basic_stones[type]; new_basics[6]  += basic_stones[type]; break;
                case 91:       new_basics[9]  += basic_stones[type]; new_basics[1]  += basic_stones[type]; break;
                case 94:       new_basics[9]  += basic_stones[type]; new_basics[4]  += basic_stones[type]; break;
                case 96:       new_basics[9]  += basic_stones[type]; new_basics[6]  += basic_stones[type]; break;
                case 2024:     new_basics[20] += basic_stones[type]; new_basics[24] += basic_stones[type]; break;
                case 2048:     new_basics[20] += basic_stones[type]; new_basics[48] += basic_stones[type]; break;
                case 2457:     new_basics[24] += basic_stones[type]; new_basics[57] += basic_stones[type]; break;
                case 2608:     new_basics[26] += basic_stones[type]; new_basics[8]  += basic_stones[type]; break;
                case 2867:     new_basics[28] += basic_stones[type]; new_basics[67] += basic_stones[type]; break;
                case 2880:     new_basics[28] += basic_stones[type]; new_basics[80] += basic_stones[type]; break;
                case 3277:     new_basics[32] += basic_stones[type]; new_basics[77] += basic_stones[type]; break;
                case 3686:     new_basics[36] += basic_stones[type]; new_basics[86] += basic_stones[type]; break;
                case 4048:     new_basics[40] += basic_stones[type]; new_basics[48] += basic_stones[type]; break;
                case 6032:     new_basics[60] += basic_stones[type]; new_basics[32] += basic_stones[type]; break;
                case 6072:     new_basics[60] += basic_stones[type]; new_basics[72] += basic_stones[type]; break;
                case 8096:     new_basics[80] += basic_stones[type]; new_basics[96] += basic_stones[type]; break;
                case 9184:     new_basics[91] += basic_stones[type]; new_basics[84] += basic_stones[type]; break;
                case 9456:     new_basics[94] += basic_stones[type]; new_basics[56] += basic_stones[type]; break;
                case 10120:    new_basics[20482880] += basic_stones[type]; break;
                case 12144:    new_basics[24579456] += basic_stones[type]; break;
                case 14168:    new_basics[28676032] += basic_stones[type]; break;
                case 16192:    new_basics[32772608] += basic_stones[type]; break;
                case 18216:    new_basics[36869184] += basic_stones[type]; break;
                case 20482880: new_basics[2048] += basic_stones[type]; new_basics[2880] += basic_stones[type]; break;
                case 24579456: new_basics[2457] += basic_stones[type]; new_basics[9456] += basic_stones[type]; break;
                case 28676032: new_basics[2867] += basic_stones[type]; new_basics[6032] += basic_stones[type]; break;
                case 32772608: new_basics[3277] += basic_stones[type]; new_basics[2608] += basic_stones[type]; break;
                case 36869184: new_basics[3686] += basic_stones[type]; new_basics[9184] += basic_stones[type]; break;
            }
        }

        basic_stones = new_basics;

        vector<long> new_non_basics;
        for(long stone: nonbasic_stones) {
            string s = to_string(stone);
            if (s.size() % 2 == 0) {
                long left = stol(s.substr(0, s.size() / 2));
                long right = stol(s.substr(s.size() / 2));
                if(basics.contains(left))
                    basic_stones[left]++;
                else
                    new_non_basics.emplace_back(left);
                if(basics.contains(right))
                    basic_stones[right]++;
                else    
                    new_non_basics.emplace_back(right);
            } else
                // you can't multiply from a nonbasic to a basic, so this must also be nonbasic
                new_non_basics.emplace_back(stone * 2024);
        }
        nonbasic_stones = new_non_basics;
        steps++;
    }

    long total = nonbasic_stones.size();
    for(int b: basics)
        total += basic_stones[b];

    cout << total << endl;
}
