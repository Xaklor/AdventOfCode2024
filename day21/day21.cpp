#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <unordered_set>
using namespace std;

struct state { 
    int steps; int bot1; int bot2; int bot3; int progress;
    bool operator==(const state& o) const {
        return this->bot1 == o.bot1 && this->bot2 == o.bot2 && this->bot3 == o.bot3 && this->progress == o.progress;
    }
    size_t operator()(const state& s) const {
        return s.bot1 * 23 + s.bot2 * 29 + s.bot3 * 31 + s.progress * 37;
    };
};

int main() {
    string line;
    ifstream input("input.txt");
    vector<string> codes;
    while(getline(input, line)) {
        codes.emplace_back(line);
    }

    int total = 0;
    for(string code: codes) {
        unordered_set<state, state> visited;
        queue<state> q;
        // for bot3, each number is equal to its position while the A button is position 10
        // for the other keypads they are left to right, top to bottom (^ is 0, > is 4)
        q.push(state{ 0, 1, 1, 10, 0 });
        while(!q.empty()) {
            state s = q.front(); q.pop();
            if(s.progress >= code.size()) {
                total += (stoi(code.substr(0, 3)) * s.steps);
                break;
            }
            if(!visited.contains(s)) {
                visited.insert(s);
                // press ^
                if(s.bot1 == 3 || s.bot1 == 4)                q.push(state{ s.steps + 1, s.bot1 - 3, s.bot2, s.bot3, s.progress });
                // press <
                if(s.bot1 == 1 || s.bot1 == 3 || s.bot1 == 4) q.push(state{ s.steps + 1, s.bot1 - 1, s.bot2, s.bot3, s.progress });
                // press v
                if(s.bot1 == 0 || s.bot1 == 1)                q.push(state{ s.steps + 1, s.bot1 + 3, s.bot2, s.bot3, s.progress });
                // press >
                if(s.bot1 == 0 || s.bot1 == 2 || s.bot1 == 3) q.push(state{ s.steps + 1, s.bot1 + 1, s.bot2, s.bot3, s.progress });
                // press A
                switch(s.bot1) {
                    // A^
                    case 0:
                        if(s.bot2 == 3 || s.bot2 == 4) q.push(state{ s.steps + 1, s.bot1, s.bot2 - 3, s.bot3, s.progress });
                        break;
                    // A button again! here we goooooo!
                    case 1:
                        switch(s.bot2) {
                            // AA^  
                            case 0:
                                if(s.bot3 < 7 && s.bot3 != 0) q.push(state{ s.steps + 1, s.bot1, s.bot2, s.bot3 + 3, s.progress });
                                else if(s.bot3 == 10) q.push(state{ s.steps + 1, s.bot1, s.bot2, 3, s.progress });
                                else if(s.bot3 == 0) q.push(state{ s.steps + 1, s.bot1, s.bot2, 2, s.progress });
                                break;
                            // A button again! here we goooooo!
                            case 1:
                                // AAA
                                if(code[s.progress] - '0' == s.bot3 || (code[s.progress] == 'A' && s.bot3 == 10))
                                    q.push(state{ s.steps + 1, s.bot1, s.bot2, s.bot3, s.progress + 1 });
                                break;
                            // AA<
                            case 2:
                                if(s.bot3 != 1 && s.bot3 != 4 && s.bot3 != 7 && s.bot3 != 10 && s.bot3 != 0) 
                                    q.push(state{ s.steps + 1, s.bot1, s.bot2, s.bot3 - 1, s.progress });
                                else if(s.bot3 == 10) q.push(state{ s.steps + 1, s.bot1, s.bot2, 0, s.progress });
                                break;
                            // AAv
                            case 3:
                                if(s.bot3 > 3 && s.bot3 != 10) q.push(state{ s.steps + 1, s.bot1, s.bot2, s.bot3 - 3, s.progress });
                                else if(s.bot3 == 2) q.push(state{ s.steps + 1, s.bot1, s.bot2, 0, s.progress });
                                else if(s.bot3 == 3) q.push(state{ s.steps + 1, s.bot1, s.bot2, 10, s.progress });
                                break;
                            // AA>
                            case 4:
                                if(s.bot3 != 0 && s.bot3 != 10 && s.bot3 != 3 && s.bot3 != 6 && s.bot3 != 9) 
                                    q.push(state{ s.steps + 1, s.bot1, s.bot2, s.bot3 + 1, s.progress });
                                else if(s.bot3 == 0) q.push(state{ s.steps + 1, s.bot1, s.bot2, 10, s.progress });
                                break;
                        }
                        break;
                    case 2:
                        // A<
                        if(s.bot2 == 1 || s.bot2 == 3 || s.bot2 == 4) q.push(state{ s.steps + 1, s.bot1, s.bot2 - 1, s.bot3, s.progress });
                        break;
                    case 3:
                        // Av
                        if(s.bot2 == 0 || s.bot2 == 1)                q.push(state{ s.steps + 1, s.bot1, s.bot2 + 3, s.bot3, s.progress });
                        break;
                    case 4:
                        // A>
                        if(s.bot2 == 0 || s.bot2 == 2 || s.bot2 == 3) q.push(state{ s.steps + 1, s.bot1, s.bot2 + 1, s.bot3, s.progress });
                        break;
                }
            }
        }
    }
    cout << total << endl;
}