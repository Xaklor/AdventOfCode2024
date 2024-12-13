#include <iostream>
#include <fstream>
#include <vector>
#include <stack>
#include <string.h>
using namespace std;

struct point { int x, y; };

int main() {
    string line;
    ifstream input("input.txt");
    vector<string> grid;
    while(getline(input, line)) {
        grid.emplace_back(line);
    }
    input.close();

    bool visited[grid.size()][grid[0].size()];
    memset(visited, 0, sizeof(visited));

    int p1_total = 0;
    int p2_total = 0;
    for(int i = 0; i < grid.size(); i++) {
        for(int j = 0; j < grid[0].size(); j++) {
            if(!visited[i][j]) {
                // begin new flood fill
                int area = 0;
                int perimeter = 0;
                int corners = 0;
                char crop = grid[i][j];
                stack<point> s;
                s.push(point{ i, j });
                while(!s.empty()) {
                    point p = s.top(); s.pop();
                    if(!visited[p.x][p.y] && grid[p.x][p.y] == crop) {
                        visited[p.x][p.y] = true;
                        area++;
                        bool west  = p.x > 0 && grid[p.x - 1][p.y] == crop;
                        bool north = p.y > 0 && grid[p.x][p.y - 1] == crop;
                        bool east  = p.x < grid.size() - 1    && grid[p.x + 1][p.y] == crop;
                        bool south = p.y < grid[0].size() - 1 && grid[p.x][p.y + 1] == crop;
                        bool northwest = p.x > 0 && p.y > 0 && grid[p.x - 1][p.y - 1] == crop;
                        bool northeast = p.x < grid.size() - 1 && p.y > 0     && grid[p.x + 1][p.y - 1] == crop;
                        bool southwest = p.x > 0 && p.y < grid[0].size() - 1  && grid[p.x - 1][p.y + 1] == crop;
                        bool southeast = p.x < grid.size() - 1 && p.y < grid[0].size() - 1 && grid[p.x + 1][p.y + 1] == crop;
                        if(west && !visited[p.x - 1][p.y])
                            s.push(point{ p.x - 1, p.y });
                        if(north && !visited[p.x][p.y - 1])
                            s.push(point{ p.x, p.y - 1 });
                        if(east && !visited[p.x + 1][p.y])
                            s.push(point{ p.x + 1, p.y });
                        if(south && !visited[p.x][p.y + 1])
                            s.push(point{ p.x, p.y + 1 });
                        if(!west)  perimeter++;
                        if(!north) perimeter++;
                        if(!east)  perimeter++;
                        if(!south) perimeter++;
                        if(!west && !north) corners++;
                        if(!east && !north) corners++;
                        if(!west && !south) corners++;
                        if(!east && !south) corners++;
                        if(north && west && !northwest) corners++;
                        if(north && east && !northeast) corners++;
                        if(south && west && !southwest) corners++;
                        if(south && east && !southeast) corners++;
                    }
                }
                p1_total += area * perimeter;
                p2_total += area * corners;
            }
        }
    }
    cout << p1_total << endl;
    cout << p2_total << endl;
}
