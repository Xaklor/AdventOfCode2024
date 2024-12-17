#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <stack>
#include <string.h>
using namespace std;

struct pqelement { 
    int x; int y; int direction; int score; int px; int py; int pdirection;
    bool operator()(const pqelement& lhs, const pqelement& rhs) const {
        return lhs.score > rhs.score;
    }
};

int main() {
    string line;
    ifstream input("input.txt");
    vector<string> grid;
    while(getline(input, line)) {
        grid.emplace_back(line);
    }
    input.close();

    bool visited[grid[0].size()][grid.size()][4];
    memset(visited, 0, sizeof(visited));
    pqelement previous[grid[0].size()][grid.size()][4][2];
    memset(previous, -1, sizeof(previous));

    int minscore = 999999;
    pqelement end{139, 1, 0, 0, 0, 0, 0};
    priority_queue<pqelement, vector<pqelement>, pqelement> pq;
    pq.push(pqelement{1, 139, 0, 0, -1, -1, 0});
    while(!pq.empty()) {
        pqelement e = pq.top(); pq.pop();
        if(e.x == end.x && e.y == end.y) minscore = min(e.score, minscore);
        if(!visited[e.x][e.y][e.direction]) {
            visited[e.x][e.y][e.direction] = true;
            if(e.px != -1) previous[e.x][e.y][e.direction][0] = pqelement{e.px, e.py, e.pdirection, e.score, 0, 0, 0};
            // east, south, west, north
            switch(e.direction) {
                case 0:
                    if(!visited[e.x + 1][e.y][0] && grid[e.y][e.x + 1] != '#')
                        pq.push(pqelement{e.x + 1, e.y, 0, e.score + 1, e.x, e.y, e.direction});
                    if(!visited[e.x][e.y + 1][0] && grid[e.y + 1][e.x] != '#')
                        pq.push(pqelement{e.x, e.y + 1, 1, e.score + 1001, e.x, e.y, e.direction});
                    if(!visited[e.x][e.y - 1][0] && grid[e.y - 1][e.x] != '#')
                        pq.push(pqelement{e.x, e.y - 1, 3, e.score + 1001, e.x, e.y, e.direction});
                    break;
                case 1:
                    if(!visited[e.x][e.y + 1][1] && grid[e.y + 1][e.x] != '#')
                        pq.push(pqelement{e.x, e.y + 1, 1, e.score + 1, e.x, e.y, e.direction});
                    if(!visited[e.x + 1][e.y][1] && grid[e.y][e.x + 1] != '#')
                        pq.push(pqelement{e.x + 1, e.y, 0, e.score + 1001, e.x, e.y, e.direction});
                    if(!visited[e.x - 1][e.y][1] && grid[e.y][e.x - 1] != '#')
                        pq.push(pqelement{e.x - 1, e.y, 2, e.score + 1001, e.x, e.y, e.direction});
                    break;
                case 2:
                    if(!visited[e.x - 1][e.y][2] && grid[e.y][e.x - 1] != '#')
                        pq.push(pqelement{e.x - 1, e.y, 2, e.score + 1, e.x, e.y, e.direction});
                    if(!visited[e.x][e.y + 1][2] && grid[e.y + 1][e.x] != '#')
                        pq.push(pqelement{e.x, e.y + 1, 1, e.score + 1001, e.x, e.y, e.direction});
                    if(!visited[e.x][e.y - 1][2] && grid[e.y - 1][e.x] != '#')
                        pq.push(pqelement{e.x, e.y - 1, 3, e.score + 1001, e.x, e.y, e.direction});
                    break;
                case 3:
                    if(!visited[e.x][e.y - 1][3] && grid[e.y - 1][e.x] != '#')
                        pq.push(pqelement{e.x, e.y - 1, 3, e.score + 1, e.x, e.y, e.direction});
                    if(!visited[e.x + 1][e.y][3] && grid[e.y][e.x + 1] != '#')
                        pq.push(pqelement{e.x + 1, e.y, 0, e.score + 1001, e.x, e.y, e.direction});
                    if(!visited[e.x - 1][e.y][3] && grid[e.y][e.x - 1] != '#')
                        pq.push(pqelement{e.x - 1, e.y, 2, e.score + 1001, e.x, e.y, e.direction});
                    break;
            }
        // check if this connects to an existing perfect path
        } else if(e.score == previous[e.x][e.y][e.direction][0].score)
            previous[e.x][e.y][e.direction][1] = pqelement{e.px, e.py, e.pdirection, e.score, 0, 0, 0};
    }
    cout << minscore << endl;

    int trace[grid[0].size()][grid.size()];
    memset(trace, 0, sizeof(trace));
    stack<pqelement> s;
    s.push(pqelement{139, 1, 0, 0, 0, 0, 0});
    s.push(pqelement{139, 1, 3, 0, 0, 0, 0});
    while(!s.empty()) {
        pqelement e = s.top(); s.pop();
        trace[e.x][e.y] = 1;
        if(previous[e.x][e.y][e.direction][0].x != -1) s.push(previous[e.x][e.y][e.direction][0]);
        if(previous[e.x][e.y][e.direction][1].x != -1) s.push(previous[e.x][e.y][e.direction][1]);
    }
    int total = 0;
    for(int i = 0; i < grid.size(); i++) {
        for(int j = 0; j < grid[0].size(); j++) {
            total += trace[j][i];
        }
    }
    cout << total << endl;
}