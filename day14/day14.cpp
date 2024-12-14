#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <unordered_set>
using namespace std;

int mod(int, int);
struct point {
    int x; int y;
    bool operator==(const point& o) const {
        return this->x == o.x && this->y == o.y;
    }
    size_t operator()(const point& p) const {
        return p.x + 17 * p.y;
    };
};

int main() {
    string line;
    ifstream input("input.txt");
    vector<vector<int>> robots;
    while(getline(input, line)) {
        int x = stoi(line.substr(2));
        int y = stoi(line.substr(line.find(',') + 1));
        int vx = stoi(line.substr(line.find("v=") + 2));
        int vy = stoi(line.substr(line.find_last_of(',') + 1));
        robots.emplace_back(vector<int> {x, y, vx, vy});
    }
    input.close();

    int q1 = 0;
    int q2 = 0;
    int q3 = 0;
    int q4 = 0;
    // part 1
    for(vector<int> robot: robots) {
        int x = mod(robot[0] + (100 * robot[2]), 101);
        int y = mod(robot[1] + (100 * robot[3]), 103);
        if(x < 50 && y < 51) q1++;
        if(x > 50 && y < 51) q2++;
        if(x < 50 && y > 51) q3++;
        if(x > 50 && y > 51) q4++;
    }
    cout << q1 * q2 * q3 * q4 << endl;

    // part 2
    int a = 13;
    int b = 79;
    while(a != b) {
        if(a < b) a += 101;
        else b += 103;
    }
    cout << a << endl;

    // part 2 output viewer
    bool enabled = false;
    if(enabled) {
        int steps = 7083;
        while(true) {
            unordered_set<point, point> positions;
            for(vector<int> robot: robots) {
                int x = mod(robot[0] + (steps * robot[2]), 101);
                int y = mod(robot[1] + (steps * robot[3]), 103);
                positions.insert(point{x, y});
            }
            for(int i = 0; i < 103; i++) {
                for(int j = 0; j < 101; j++) {
                    if(positions.contains(point{j, i})) cout << '#';
                    else cout << '.';
                }
                cout << endl;
            }
            cout << "steps: " << steps << endl;
            cout << "continue?" << endl;
            cin.get();
            steps++;
        }
    }
}

// c++'s barbaric misrepresentation of the modulo operator has pushed me to this
int mod(int n, int m) {
    if(n % m == 0) return 0;
    if(n < 0) return m - abs(n % m);
    else return n % m;
}