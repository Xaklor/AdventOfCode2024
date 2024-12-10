#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <string.h>
using namespace std;

struct point { int x, y; char h; };

int main() {
    string line;
    ifstream input("input.txt");
    vector<string> grid;
    while(getline(input, line)) {
        grid.emplace_back(line);
    }
    input.close();

    int total1 = 0;
    int total2 = 0;
    for(int i = 0; i < grid.size(); i++) {
        for(int j = 0; j < grid[0].size(); j++) {
            if(grid[i][j] == '0') {
                bool visited[grid.size()][grid[0].size()];
                memset(visited, 0, sizeof(visited));
                queue<point> q;
                q.push(point{ i, j, '0' });
                while(!q.empty()) {
                    point p = q.front();
                    q.pop();
                    if(p.h == '9') {
                        total2 += 1;
                        if(!visited[p.x][p.y]) {
                            visited[p.x][p.y] = true;
                            total1 += 1;
                        }
                    }

                    else {
                        if(p.x > 0 && grid[p.x - 1][p.y] == p.h + 1)
                            q.push(point{p.x - 1, p.y, grid[p.x - 1][p.y]});
                        if(p.y > 0 && grid[p.x][p.y - 1] == p.h + 1)
                            q.push(point{p.x, p.y - 1, grid[p.x][p.y - 1]});
                        if(p.x < grid.size() - 1 && grid[p.x + 1][p.y] == p.h + 1)
                            q.push(point{p.x + 1, p.y, grid[p.x + 1][p.y]});
                        if(p.y < grid[0].size() - 1 && grid[p.x][p.y + 1] == p.h + 1)
                            q.push(point{p.x, p.y + 1, grid[p.x][p.y + 1]});
                    }
                }
            }
        }
    }

    cout << total1 << endl;
    cout << total2 << endl;
}