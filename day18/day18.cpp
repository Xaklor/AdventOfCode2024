#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <string.h>
#include <unordered_set>
using namespace std;

struct point {
    int x; int y; int steps;
    bool operator==(const point& o) const {
        return this->x == o.x && this->y == o.y;
    }
    size_t operator()(const point& p) const {
        return p.x + 17 * p.y;
    };
};

int pathfind(unordered_set<point, point>);

int main() {
    string line;
    ifstream input("input.txt");
    unordered_set<point, point> p1input;
    vector<point> p2input;
    int count = 0;
    while(getline(input, line)) {
        int x = stoi(line.substr(0, line.find(',')));
        int y = stoi(line.substr(line.find(',') + 1));
        p2input.emplace_back(point{ x, y, 0 });
        if(count < 1024) {
            p1input.insert(point{ x, y, 0 });
            count++;
        }
    }

    // part 1
    cout << pathfind(p1input) << endl;

    // part 2
    unordered_set<point, point> bytes(p1input);
    int idx = 1024;
    while(pathfind(bytes) != -1 && idx < p2input.size())
        bytes.insert(p2input[idx++]);
    cout << p2input[idx - 1].x << ',' << p2input[idx - 1].y << endl;
}

// attempts to pathfind between start and finish, returns the number of steps in the shortest path if possible, and -1 otherwise
int pathfind(unordered_set<point, point> bytes) {
    queue<point> q;
    q.push(point{ 0, 0, 0 });
    bool visited[71][71]; memset(visited, 0, sizeof(visited));
    while(!q.empty()) {
        point p = q.front(); q.pop();
        if(p.x == 70 && p.y == 70){
            return p.steps;
        }
        if(p.x >= 0 && p.x <= 70 && p.y >= 0 && p.y <= 70 && !visited[p.x][p.y] && !bytes.contains(p)) {
            visited[p.x][p.y] = true;
            q.push(point{ p.x - 1, p.y, p.steps + 1 });
            q.push(point{ p.x + 1, p.y, p.steps + 1 });
            q.push(point{ p.x, p.y - 1, p.steps + 1 });
            q.push(point{ p.x, p.y + 1, p.steps + 1 });
        }
    }
    return -1;
}