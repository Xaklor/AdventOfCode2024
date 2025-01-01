#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <string.h>
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

struct pqelement {
    int pos; long presses; int botpos;
        bool operator<(const pqelement& o) const {
        return this->presses > o.presses;
    }
};

long expand(int, int, int);
int ctop(char);
const int RECURSION_COUNT = 25;
long memo[5][5][RECURSION_COUNT + 1] {};

int main() {
    string line;
    ifstream input("input.txt");
    vector<string> codes;
    while(getline(input, line)) {
        codes.emplace_back(line);
    }

    cout << expand(1, 0, RECURSION_COUNT) << ", ";
    cout << expand(0, 0, RECURSION_COUNT) << ", ";
    cout << expand(0, 1, RECURSION_COUNT) << ", ";
    cout << expand(1, 2, RECURSION_COUNT) << ", ";
    cout << expand(2, 2, RECURSION_COUNT) << ", ";
    cout << expand(2, 0, RECURSION_COUNT) << ", ";
    cout << expand(0, 1, RECURSION_COUNT) << ", ";
    cout << expand(1, 4, RECURSION_COUNT) << ", ";
    cout << expand(4, 3, RECURSION_COUNT) << ", ";
    cout << expand(3, 3, RECURSION_COUNT) << ", ";
    cout << expand(3, 3, RECURSION_COUNT) << ", ";
    cout << expand(3, 1, RECURSION_COUNT) << ", ";    
    cout << expand(1, 4, RECURSION_COUNT) << ", ";    
    cout << expand(4, 1, RECURSION_COUNT) << endl;    

    long total = 0;
    for(string code: codes) {
        long t = 0; 
        int start = 10;
        int end;
        for(char c: code) {
            end = ctop(c);
            long best = 10000000000000;
            long distances[11]; 
            memset(distances, 50000, sizeof(distances));
            bool visited[11] {0};
            priority_queue<pqelement, vector<pqelement>> pq;   
            pq.push(pqelement{ start, 0, 1 });
            while(!pq.empty()) {
                pqelement e = pq.top(); pq.pop();
                if(e.pos == end) {
                    // presses A
                    t += e.presses + expand(e.botpos, 1, RECURSION_COUNT);
                    // long raineburkett = expand(e.botpos, 1, RECURSION_COUNT);
                    // best = min(best, e.presses + raineburkett);
                }
                if(!visited[e.pos]) {
                    visited[e.pos] = true;
                    if(e.pos % 3 != 0) // tries <
                        pq.push(pqelement{ e.pos - 1, e.presses + expand(e.botpos, 2, RECURSION_COUNT), 2 });
                    if(e.pos % 3 != 2 && e.pos != 10) // tries >
                        pq.push(pqelement{ e.pos + 1, e.presses + expand(e.botpos, 4, RECURSION_COUNT), 4 });
                    if(e.pos > 2 && e.pos < 9) // tries ^
                        pq.push(pqelement{ e.pos - 3, e.presses + expand(e.botpos, 0, RECURSION_COUNT), 0 });
                    if(e.pos >= 9) // ^ edge cases
                        pq.push(pqelement{ e.pos - 2, e.presses + expand(e.botpos, 0, RECURSION_COUNT), 0 });
                    if(e.pos < 6) // tries v
                        pq.push(pqelement{ e.pos + 3, e.presses + expand(e.botpos, 3, RECURSION_COUNT), 3 });
                    if(e.pos == 7 || e.pos == 8) // v edge cases
                        pq.push(pqelement{ e.pos + 2, e.presses + expand(e.botpos, 3, RECURSION_COUNT), 3 });
                }
            }
            // cout << best << ", ";
            // t += best;
            start = end;
        }
        cout << t << endl;
        total += (t * stoi(code.substr(0, 3)));
    }
    // 275231385684876 too high
    // 955833472079928
    cout << total << endl;

    exit(0);

    total = 0;
    for(string code: codes) {
        unordered_set<state, state> visited;
        queue<state> q;
        // for bot3, each number is equal to its position while the A button is position 10
        // for the other keypads they are left to right, top to bottom (^ is 0, > is 4)
        q.push(state{ 0, 1, 1, 10, 0 });
        while(!q.empty()) {
            state s = q.front(); q.pop();
            if(s.progress >= code.size()) {
                cout << s.steps << endl;
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

// positions are left to right, top to bottom (^, A, <, v, >)
long expand(int position, int destination, int layer) {
    if(memo[position][destination][layer] != 0)
        return memo[position][destination][layer];
    if(layer == 0) {
        memo[position][destination][layer] = 1;
        return 1;
    }

    int a, b;
    long result = 0;
    switch(position) {
        // pointing at ^
        case 0: 
            switch(destination) {
            case 0: result = expand(1, 1, layer - 1); break;
            case 1: result = expand(1, 4, layer - 1) + expand(4, 1, layer - 1); break;
            case 2: result = expand(1, 3, layer - 1) + expand(3, 2, layer - 1) + expand(2, 1, layer - 1); break;
            case 3: result = expand(1, 3, layer - 1) + expand(3, 1, layer - 1); break;
            case 4: 
                a = expand(1, 4, layer - 1) + expand(4, 3, layer - 1) + expand(3, 1, layer - 1);
                b = expand(1, 3, layer - 1) + expand(3, 4, layer - 1) + expand(4, 1, layer - 1);
                if(a > b) result = a;
                else result = b;
                break;
        } break;
        // pointing at A
        case 1: 
            switch(destination) {
            case 0: result = expand(1, 2, layer - 1) + expand(2, 1, layer - 1); break;
            case 1: result = expand(1, 1, layer - 1); break;
            case 2: result = expand(1, 4, layer - 1) + expand(4, 3, layer - 1) + expand(3, 2, layer - 1) + expand(2, 1, layer - 1); break;
            case 3: 
                a = expand(1, 3, layer - 1) + expand(3, 2, layer - 1) + expand(2, 1, layer - 1);
                b = expand(1, 2, layer - 1) + expand(2, 3, layer - 1) + expand(3, 1, layer - 1);
                if(a > b) result = a;
                else result = b;
                break;

            case 4: result = expand(1, 3, layer - 1) + expand(3, 1, layer - 1); break;
        } break;
        // pointing at <
        case 2: 
            switch(destination) {
            case 0: result = expand(1, 4, layer - 1) + expand(4, 0, layer - 1) + expand(0, 1, layer - 1); break;
            case 1: result = expand(1, 4, layer - 1) + expand(4, 4, layer - 1) + expand(4, 0, layer - 1) + expand(0, 1, layer - 1); break;
            case 2: result = expand(1, 1, layer - 1); break;
            case 3: result = expand(1, 4, layer - 1) + expand(4, 1, layer - 1); break;
            case 4: result = expand(1, 4, layer - 1) + expand(4, 4, layer - 1) + expand(4, 1, layer - 1); break;
        } break;
        // pointing at v
        case 3: 
            switch(destination) {
            case 0: result = expand(1, 0, layer - 1) + expand(0, 1, layer - 1); break;
            case 1:
                a = expand(1, 0, layer - 1) + expand(0, 4, layer - 1) + expand(4, 1, layer - 1);
                b = expand(1, 4, layer - 1) + expand(4, 0, layer - 1) + expand(0, 1, layer - 1);
                if(a > b) result = a;
                else result = b;
                break;

            case 2: result = expand(1, 2, layer - 1) + expand(2, 1, layer - 1); break;
            case 3: result = expand(1, 1, layer - 1); break;
            case 4: result = expand(1, 4, layer - 1) + expand(4, 1, layer - 1); break;
        } break;
        // pointing at >
        case 4: 
            switch(destination) {
            case 0:
                a = expand(1, 0, layer - 1) + expand(0, 2, layer - 1) + expand(2, 1, layer - 1);
                b = expand(1, 2, layer - 1) + expand(2, 0, layer - 1) + expand(0, 1, layer - 1);
                if(a > b) result = a;
                else result = b;
                break;

            case 1: result = expand(1, 0, layer - 1) + expand(0, 1, layer - 1); break;
            case 2: result = expand(1, 2, layer - 1) + expand(2, 2, layer - 1) + expand(2, 1, layer - 1); break;
            case 3: result = expand(1, 2, layer - 1) + expand(2, 1, layer - 1); break;
            case 4: result = expand(1, 1, layer - 1); break;
        } break;
    }
    memo[position][destination][layer] = result;
    return result;
}

int ctop(char c) {
    switch(c) {
        case '0': return 9; 
        case '1': return 6; 
        case '2': return 7; 
        case '3': return 8; 
        case '4': return 3; 
        case '5': return 4; 
        case '6': return 5; 
        case '7': return 0; 
        case '8': return 1; 
        case '9': return 2; 
        case 'A': return 10;
    }
    return 0;
}