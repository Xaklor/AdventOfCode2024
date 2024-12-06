#include <iostream>
#include <fstream>
#include <vector>
#include <string.h>
using namespace std;

bool verify(vector<string>);
int startx, starty;

int main() {
    string line;
    ifstream input1("input.txt");
    vector<string> grid = vector<string>();
    while (getline (input1, line)) {
        grid.emplace_back(line);
    }
    input1.close();

    for(int j = 0; j < grid.size(); j++) {
        for(int i = 0; i < grid[0].size(); i++) {
            if(grid[j][i] == '^') {
                startx = i;
                starty = j;
            }                
        }
    }

    // part 1
    // it pains me to repeat so much code but I need the visited array from p1 to solve p2
    bool visited[grid.size()][grid[0].size()];
    memset(visited, 0, sizeof(visited));
    
    // 0-3, north, east, south, west
    int direction = 0;
    int i = startx;
    int j = starty;
    bool patrolling = true;
    int newsteps = 0;
    while(patrolling) {
        if(!visited[j][i])
            newsteps += 1;

        visited[j][i] = true;
        switch(direction) {
            case 0:
                if (j - 1 < 0)
                    patrolling = false;
                else if(grid[j - 1][i] == '#')
                    direction = 1;
                else
                    j -= 1;
                break;
            case 1:
                if (i + 1 >= grid[0].size())
                    patrolling = false;
                else if(grid[j][i + 1] == '#')
                    direction = 2;
                else
                    i += 1;
                break;
            case 2:
                if (j + 1 >= grid.size())
                    patrolling = false;
                else if(grid[j + 1][i] == '#')
                    direction = 3;
                else
                    j += 1;
                break;
            case 3:
                if (i - 1 < 0)
                    patrolling = false;
                else if(grid[j][i - 1] == '#')
                    direction = 0;
                else
                    i -= 1;
                break;
        }
    }

    cout << newsteps << endl;

    // part 2
    int total = 0;
    for(int i = 0; i < grid.size(); i++) {
        for(int j = 0; j < grid[0].size(); j++) {
            if(visited[i][j] && !(i == starty && j == startx)) {
                grid[i][j] = '#';
                if(verify(grid)) {
                    total += 1;
                }

                grid[i][j] = '.';
            }
        }
    }

    cout << total << endl;
}

// repeats the patrol route and returns true if the guard is in a loop, false otherwise
bool verify(vector<string> grid){
    bool visited[grid.size()][grid[0].size()];
    memset(visited, 0, sizeof(visited));
    
    // 0-3, north, east, south, west
    int direction = 0;
    int i = startx;
    int j = starty;
    bool patrolling = true;
    int newsteps = 0;
    int oldsteps = 0;
    while(patrolling) {
        // keeping track of which spaces are repeats and are new, if we hit repeats = new * 2 then we're definitely looping and are done
        if(!visited[j][i]) {
            newsteps += 1;
            oldsteps = 0;
        } else {
            oldsteps += 1;
        }
        if(oldsteps == newsteps * 2) {
            patrolling = false;
            break;
        }

        visited[j][i] = true;
        switch(direction) {
            case 0:
                if (j - 1 < 0)
                    patrolling = false;
                else if(grid[j - 1][i] == '#')
                    direction = 1;
                else
                    j -= 1;
                break;
            case 1:
                if (i + 1 >= grid[0].size())
                    patrolling = false;
                else if(grid[j][i + 1] == '#')
                    direction = 2;
                else
                    i += 1;
                break;
            case 2:
                if (j + 1 >= grid.size())
                    patrolling = false;
                else if(grid[j + 1][i] == '#')
                    direction = 3;
                else
                    j += 1;
                break;
            case 3:
                if (i - 1 < 0)
                    patrolling = false;
                else if(grid[j][i - 1] == '#')
                    direction = 0;
                else
                    i -= 1;
                break;
        }
    }

    return oldsteps == newsteps * 2;
}
