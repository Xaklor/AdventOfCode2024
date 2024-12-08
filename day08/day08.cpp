#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
using namespace std;

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
    vector<string> grid;
    while (getline (input, line))
        grid.emplace_back(line);

    input.close();

    int maxx = grid.size();
    int maxy = grid[0].size();
    unordered_map<char, vector<point>> antennas;
    vector<char> keys;
    for(int x = 0; x < maxx; x++) {
        for(int y = 0; y < maxy; y++) {
            char freq = grid[x][y];
            if(freq != '.') {
                if(!antennas.contains(freq)) {
                    antennas[freq] = vector<point> { point{x, y} };
                    keys.emplace_back(freq);
                } else
                    antennas[freq].emplace_back(point{x, y});
            }
        }
    }

    // part 1
    unordered_set<point, point> anodes;
    for(int i = 0; i < keys.size(); i++) {
        vector<point> freqs = antennas[keys[i]];
        for(int a1 = 0; a1 < freqs.size(); a1++) {
            for(int a2 = a1 + 1; a2 < freqs.size(); a2++) {
                point anode1 = { freqs[a1].x - (freqs[a2].x - freqs[a1].x), freqs[a1].y - (freqs[a2].y - freqs[a1].y) };
                point anode2 = { freqs[a2].x + (freqs[a2].x - freqs[a1].x), freqs[a2].y + (freqs[a2].y - freqs[a1].y) };
                if(anode1.x >= 0 && anode1.x < maxx && anode1.y >= 0 && anode1.y < maxy)
                    anodes.insert(anode1);
                if(anode2.x >= 0 && anode2.x < maxx && anode2.y >= 0 && anode2.y < maxy)
                    anodes.insert(anode2);
            }
        }
    }

    cout << anodes.size() << endl;

    // part 2
    anodes.clear();
    for(int i = 0; i < keys.size(); i++) {
        vector<point> freqs = antennas[keys[i]];
        for(int i = 0; i < freqs.size(); i++) {
            for(int j = i + 1; j < freqs.size(); j++) {
                point p1 = freqs[i];
                point p2 = freqs[j];
                int dist[] = { p2.x - p1.x, p2.y - p1.y };
                while(p1.x >= 0 && p1.y >= 0 && p1.x < maxx && p1.y < maxy) {
                    anodes.insert(p1);
                    p1.x -= dist[0];
                    p1.y -= dist[1];
                }
                while(p2.x >= 0 && p2.y >= 0 && p2.x < maxx && p2.y < maxy) {
                    anodes.insert(p2);
                    p2.x += dist[0];
                    p2.y += dist[1];
                }
            }
        }
    }

    cout << anodes.size() << endl;
}