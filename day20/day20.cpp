#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

struct point { int x; int y; };

int main() {
    string line;
    ifstream input("input.txt");
    vector<string> grid;
    while(getline(input, line)) {
        grid.emplace_back(line);
    }

    int times[grid.size()][grid[0].size()] {};
    point start = { 89, 49 };
    point end   = { 99, 31 };
    point p = start;
    int steps = 1;
    while(!(p.x == end.x && p.y == end.y)) {
        times[p.x][p.y] = steps;
        steps++;
             if(grid[p.x - 1][p.y] != '#' && times[p.x - 1][p.y] == 0) p.x--;
        else if(grid[p.x + 1][p.y] != '#' && times[p.x + 1][p.y] == 0) p.x++;
        else if(grid[p.x][p.y - 1] != '#' && times[p.x][p.y - 1] == 0) p.y--;
        else if(grid[p.x][p.y + 1] != '#' && times[p.x][p.y + 1] == 0) p.y++;
    }
    times[end.x][end.y] = steps;

    long total = 0;
    p = start;
    // range of 2 is p1, range of 20 is p2
    const int CHEAT_RANGE = 20;
    for(int i = 0; i < grid.size(); i++) {
        for(int j = 0; j < grid[0].size(); j++) {
            if(grid[i][j] != '#') {
                for(int x = -CHEAT_RANGE; x <= CHEAT_RANGE; x++) {
                    for(int y = -(CHEAT_RANGE - abs(x)); y <= CHEAT_RANGE - abs(x); y++) {
                        if(i + x >= 0 && i + x < grid.size() && j + y >= 0 && j + y < grid[0].size() &&
                        grid[i + x][j + y] != '#' && times[i + x][j + y] - times[i][j] - (abs(x) + abs(y)) >= 100)
                            total++;
                    }
                }
            }
        }
    }
    cout << total << endl;
}