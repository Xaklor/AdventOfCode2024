#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <string.h>
#include <unordered_set>
#include <unordered_map>
using namespace std;

int basic_to_idx(long);
// this is the set of numbers from which you cannot leave while following the split rules, I expect the bulk of the stones to be in this set
const unordered_set<int> basics = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 20, 24, 26, 28, 32, 36, 40, 48, 56, 57, 60, 67, 72, 77, 80, 84, 86, 91, 94, 96,
                                    2024, 2048, 2457, 2608, 2867, 2880, 3277, 3686, 4048, 6032, 6072, 8096, 9184, 9456, 10120, 12144, 14168, 16192, 
                                    18216, 20482880, 24579456, 28676032, 32772608, 36869184 };
int main() {
    string line;
    ifstream input("input.txt");
    vector<long> nonbasic_stones;
    long basic_stones[basics.size()];
    memset(basic_stones, 0, sizeof(basic_stones));

    getline(input, line);
    stringstream ss(line);
    int num;
    while (ss.eof() == 0) {
        ss >> num;
        if(basics.contains(num)) 
            basic_stones[basic_to_idx(num)]++;
        else
            nonbasic_stones.emplace_back(num);
    }

    input.close();

    int steps = 0;
    // change this to 25 for p1
    while(steps < 75) {
        long new_basics[basics.size()];
        memset(new_basics, 0, sizeof(basic_stones));
        for(long type: basics) {
            switch(type) {
                case 0:        new_basics[basic_to_idx(1)]     += basic_stones[basic_to_idx(type)]; break;
                case 1:        new_basics[basic_to_idx(2024)]  += basic_stones[basic_to_idx(type)]; break;
                case 2:        new_basics[basic_to_idx(4048)]  += basic_stones[basic_to_idx(type)]; break;
                case 3:        new_basics[basic_to_idx(6072)]  += basic_stones[basic_to_idx(type)]; break;
                case 4:        new_basics[basic_to_idx(8096)]  += basic_stones[basic_to_idx(type)]; break;
                case 5:        new_basics[basic_to_idx(10120)] += basic_stones[basic_to_idx(type)]; break;
                case 6:        new_basics[basic_to_idx(12144)] += basic_stones[basic_to_idx(type)]; break;
                case 7:        new_basics[basic_to_idx(14168)] += basic_stones[basic_to_idx(type)]; break;
                case 8:        new_basics[basic_to_idx(16192)] += basic_stones[basic_to_idx(type)]; break;
                case 9:        new_basics[basic_to_idx(18216)] += basic_stones[basic_to_idx(type)]; break;
                case 20:       new_basics[basic_to_idx(2)]  += basic_stones[basic_to_idx(type)]; new_basics[basic_to_idx(0)]  += basic_stones[basic_to_idx(type)]; break;
                case 24:       new_basics[basic_to_idx(2)]  += basic_stones[basic_to_idx(type)]; new_basics[basic_to_idx(4)]  += basic_stones[basic_to_idx(type)]; break;
                case 26:       new_basics[basic_to_idx(2)]  += basic_stones[basic_to_idx(type)]; new_basics[basic_to_idx(6)]  += basic_stones[basic_to_idx(type)]; break;
                case 28:       new_basics[basic_to_idx(2)]  += basic_stones[basic_to_idx(type)]; new_basics[basic_to_idx(8)]  += basic_stones[basic_to_idx(type)]; break;
                case 32:       new_basics[basic_to_idx(3)]  += basic_stones[basic_to_idx(type)]; new_basics[basic_to_idx(2)]  += basic_stones[basic_to_idx(type)]; break;
                case 36:       new_basics[basic_to_idx(3)]  += basic_stones[basic_to_idx(type)]; new_basics[basic_to_idx(6)]  += basic_stones[basic_to_idx(type)]; break;
                case 40:       new_basics[basic_to_idx(4)]  += basic_stones[basic_to_idx(type)]; new_basics[basic_to_idx(0)]  += basic_stones[basic_to_idx(type)]; break;
                case 48:       new_basics[basic_to_idx(4)]  += basic_stones[basic_to_idx(type)]; new_basics[basic_to_idx(8)]  += basic_stones[basic_to_idx(type)]; break;
                case 56:       new_basics[basic_to_idx(5)]  += basic_stones[basic_to_idx(type)]; new_basics[basic_to_idx(6)]  += basic_stones[basic_to_idx(type)]; break;
                case 57:       new_basics[basic_to_idx(5)]  += basic_stones[basic_to_idx(type)]; new_basics[basic_to_idx(7)]  += basic_stones[basic_to_idx(type)]; break;
                case 60:       new_basics[basic_to_idx(6)]  += basic_stones[basic_to_idx(type)]; new_basics[basic_to_idx(0)]  += basic_stones[basic_to_idx(type)]; break;
                case 67:       new_basics[basic_to_idx(6)]  += basic_stones[basic_to_idx(type)]; new_basics[basic_to_idx(7)]  += basic_stones[basic_to_idx(type)]; break;
                case 72:       new_basics[basic_to_idx(7)]  += basic_stones[basic_to_idx(type)]; new_basics[basic_to_idx(2)]  += basic_stones[basic_to_idx(type)]; break;
                case 77:       new_basics[basic_to_idx(7)]  += basic_stones[basic_to_idx(type)]; new_basics[basic_to_idx(7)]  += basic_stones[basic_to_idx(type)]; break;
                case 80:       new_basics[basic_to_idx(8)]  += basic_stones[basic_to_idx(type)]; new_basics[basic_to_idx(0)]  += basic_stones[basic_to_idx(type)]; break;
                case 84:       new_basics[basic_to_idx(8)]  += basic_stones[basic_to_idx(type)]; new_basics[basic_to_idx(4)]  += basic_stones[basic_to_idx(type)]; break;
                case 86:       new_basics[basic_to_idx(8)]  += basic_stones[basic_to_idx(type)]; new_basics[basic_to_idx(6)]  += basic_stones[basic_to_idx(type)]; break;
                case 91:       new_basics[basic_to_idx(9)]  += basic_stones[basic_to_idx(type)]; new_basics[basic_to_idx(1)]  += basic_stones[basic_to_idx(type)]; break;
                case 94:       new_basics[basic_to_idx(9)]  += basic_stones[basic_to_idx(type)]; new_basics[basic_to_idx(4)]  += basic_stones[basic_to_idx(type)]; break;
                case 96:       new_basics[basic_to_idx(9)]  += basic_stones[basic_to_idx(type)]; new_basics[basic_to_idx(6)]  += basic_stones[basic_to_idx(type)]; break;
                case 2024:     new_basics[basic_to_idx(20)] += basic_stones[basic_to_idx(type)]; new_basics[basic_to_idx(24)] += basic_stones[basic_to_idx(type)]; break;
                case 2048:     new_basics[basic_to_idx(20)] += basic_stones[basic_to_idx(type)]; new_basics[basic_to_idx(48)] += basic_stones[basic_to_idx(type)]; break;
                case 2457:     new_basics[basic_to_idx(24)] += basic_stones[basic_to_idx(type)]; new_basics[basic_to_idx(57)] += basic_stones[basic_to_idx(type)]; break;
                case 2608:     new_basics[basic_to_idx(26)] += basic_stones[basic_to_idx(type)]; new_basics[basic_to_idx(8)]  += basic_stones[basic_to_idx(type)]; break;
                case 2867:     new_basics[basic_to_idx(28)] += basic_stones[basic_to_idx(type)]; new_basics[basic_to_idx(67)] += basic_stones[basic_to_idx(type)]; break;
                case 2880:     new_basics[basic_to_idx(28)] += basic_stones[basic_to_idx(type)]; new_basics[basic_to_idx(80)] += basic_stones[basic_to_idx(type)]; break;
                case 3277:     new_basics[basic_to_idx(32)] += basic_stones[basic_to_idx(type)]; new_basics[basic_to_idx(77)] += basic_stones[basic_to_idx(type)]; break;
                case 3686:     new_basics[basic_to_idx(36)] += basic_stones[basic_to_idx(type)]; new_basics[basic_to_idx(86)] += basic_stones[basic_to_idx(type)]; break;
                case 4048:     new_basics[basic_to_idx(40)] += basic_stones[basic_to_idx(type)]; new_basics[basic_to_idx(48)] += basic_stones[basic_to_idx(type)]; break;
                case 6032:     new_basics[basic_to_idx(60)] += basic_stones[basic_to_idx(type)]; new_basics[basic_to_idx(32)] += basic_stones[basic_to_idx(type)]; break;
                case 6072:     new_basics[basic_to_idx(60)] += basic_stones[basic_to_idx(type)]; new_basics[basic_to_idx(72)] += basic_stones[basic_to_idx(type)]; break;
                case 8096:     new_basics[basic_to_idx(80)] += basic_stones[basic_to_idx(type)]; new_basics[basic_to_idx(96)] += basic_stones[basic_to_idx(type)]; break;
                case 9184:     new_basics[basic_to_idx(91)] += basic_stones[basic_to_idx(type)]; new_basics[basic_to_idx(84)] += basic_stones[basic_to_idx(type)]; break;
                case 9456:     new_basics[basic_to_idx(94)] += basic_stones[basic_to_idx(type)]; new_basics[basic_to_idx(56)] += basic_stones[basic_to_idx(type)]; break;
                case 10120:    new_basics[basic_to_idx(20482880)] += basic_stones[basic_to_idx(type)]; break;
                case 12144:    new_basics[basic_to_idx(24579456)] += basic_stones[basic_to_idx(type)]; break;
                case 14168:    new_basics[basic_to_idx(28676032)] += basic_stones[basic_to_idx(type)]; break;
                case 16192:    new_basics[basic_to_idx(32772608)] += basic_stones[basic_to_idx(type)]; break;
                case 18216:    new_basics[basic_to_idx(36869184)] += basic_stones[basic_to_idx(type)]; break;
                case 20482880: new_basics[basic_to_idx(2048)] += basic_stones[basic_to_idx(type)]; new_basics[basic_to_idx(2880)] += basic_stones[basic_to_idx(type)]; break;
                case 24579456: new_basics[basic_to_idx(2457)] += basic_stones[basic_to_idx(type)]; new_basics[basic_to_idx(9456)] += basic_stones[basic_to_idx(type)]; break;
                case 28676032: new_basics[basic_to_idx(2867)] += basic_stones[basic_to_idx(type)]; new_basics[basic_to_idx(6032)] += basic_stones[basic_to_idx(type)]; break;
                case 32772608: new_basics[basic_to_idx(3277)] += basic_stones[basic_to_idx(type)]; new_basics[basic_to_idx(2608)] += basic_stones[basic_to_idx(type)]; break;
                case 36869184: new_basics[basic_to_idx(3686)] += basic_stones[basic_to_idx(type)]; new_basics[basic_to_idx(9184)] += basic_stones[basic_to_idx(type)]; break;
            }
        }

        for(int i = 0; i < sizeof(new_basics) / sizeof(new_basics[0]); i++)
            basic_stones[i] = new_basics[i];

        vector<long> new_non_basics;
        for(long stone: nonbasic_stones) {
            string s = to_string(stone);
            if (s.size() % 2 == 0) {
                long left = stol(s.substr(0, s.size() / 2));
                long right = stol(s.substr(s.size() / 2));
                if(basics.contains(left))
                    basic_stones[basic_to_idx(left)]++;
                else
                    new_non_basics.emplace_back(left);
                if(basics.contains(right))
                    basic_stones[basic_to_idx(right)]++;
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
    for(int i = 0; i < sizeof(basic_stones) / sizeof(basic_stones[0]); i++)
        total += basic_stones[i];

    cout << total << endl;
}

int basic_to_idx(long b) {
    switch(b) {
        case 20:       return 10;
        case 24:       return 11;
        case 26:       return 12;
        case 28:       return 13;
        case 32:       return 14;
        case 36:       return 15;
        case 40:       return 16;
        case 48:       return 17;
        case 56:       return 18;
        case 57:       return 19;
        case 60:       return 20;
        case 67:       return 21;
        case 72:       return 22;
        case 77:       return 23;
        case 80:       return 24;
        case 84:       return 25;
        case 86:       return 26;
        case 91:       return 27;
        case 94:       return 28;
        case 96:       return 29;
        case 2024:     return 30;
        case 2048:     return 31;
        case 2457:     return 32;
        case 2608:     return 33;
        case 2867:     return 34;
        case 2880:     return 35;
        case 3277:     return 36;
        case 3686:     return 37;
        case 4048:     return 38;
        case 6032:     return 39;
        case 6072:     return 40;
        case 8096:     return 41;
        case 9184:     return 42;
        case 9456:     return 43;
        case 10120:    return 44;
        case 12144:    return 45;
        case 14168:    return 46;
        case 16192:    return 47;
        case 18216:    return 48;
        case 20482880: return 49;
        case 24579456: return 50;
        case 28676032: return 51;
        case 32772608: return 52;
        case 36869184: return 53;
        default: return b;
    }
}