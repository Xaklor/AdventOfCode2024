#include <iostream>
#include <fstream>
#include <vector>
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

bool movement_check(point, char);
void push_blocks(point, char);
void move_block(point, char);
unordered_set<point, point> walls;
unordered_set<point, point> blocks;
unordered_set<point, point> dwalls;
unordered_set<point, point> lblocks;
unordered_set<point, point> rblocks;
point robot;
point drobot;

int main() {
    string line;
    ifstream input("input.txt");
    getline(input, line);
    int y = 0;
    while(line != "") {
        for(int x = 0; x < line.size(); x++) {
            switch(line[x]) {
                case '#':  walls.insert(point{x, y});  dwalls.insert(point{2 * x, y});  dwalls.insert(point{2 * x + 1, y}); break;
                case 'O': blocks.insert(point{x, y}); lblocks.insert(point{2 * x, y}); rblocks.insert(point{2 * x + 1, y}); break;
                case '@': robot = point{x, y}; drobot = point{2 * x, y}; break;
            }
        }
        y++;
        getline(input, line);
    }
    string instructions;
    while(getline(input, line)) {
        instructions += line;
    }
    input.close();

    // part 1
    for(char instruction: instructions) {
        int step = 1;
        int result = 0;
        switch(instruction) {
            case '<': {
                // scan until we find a wall or empty spot, if wall then we can't push, otherwise we can
                while(result == 0) {
                    if(walls.contains(point{robot.x - step, robot.y})) result = -1;
                    else if(!blocks.contains(point{robot.x - step, robot.y})) result = 1;
                    else step++;
                }
                // if we can push, remove the start block and add a new one at the end (skips pushing each one individually)
                if(result == 1) {
                    blocks.insert(point{robot.x - step, robot.y});
                    blocks.erase(point{robot.x - 1, robot.y});
                    robot.x--;
                }
                break; }
            case '>': {
                while(result == 0) {
                    if(walls.contains(point{robot.x + step, robot.y})) result = -1;
                    else if(!blocks.contains(point{robot.x + step, robot.y})) result = 1;
                    else step++;
                }
                if(result == 1) {
                    blocks.insert(point{robot.x + step, robot.y});
                    blocks.erase(point{robot.x + 1, robot.y});
                    robot.x++;
                }
                break; }
            case '^': {
                while(result == 0) {
                    if(walls.contains(point{robot.x, robot.y - step})) result = -1;
                    else if(!blocks.contains(point{robot.x, robot.y - step})) result = 1;
                    else step++;
                }
                if(result == 1) {
                    blocks.insert(point{robot.x, robot.y - step});
                    blocks.erase(point{robot.x, robot.y - 1});
                    robot.y--;
                }
                break; }
            case 'v': {
                while(result == 0) {
                    if(walls.contains(point{robot.x, robot.y + step})) result = -1;
                    else if(!blocks.contains(point{robot.x, robot.y + step})) result = 1;
                    else step++;
                }
                if(result == 1) {
                    blocks.insert(point{robot.x, robot.y + step});
                    blocks.erase(point{robot.x, robot.y + 1});
                    robot.y++;
                }
                break; }
        }
    }

    int total = 0;
    for(point p: blocks) {
        total += p.x + (p.y * 100);
    }
    cout << total << endl;

    // part 2
    for(char instruction: instructions) {
        switch(instruction) {
            case '<':
                // if we can push, then push and move robot
                if(movement_check(point{drobot.x - 1, drobot.y}, instruction)) {
                    push_blocks(point{drobot.x - 1, drobot.y}, instruction);
                    drobot.x--;
                }
                break;
            case '>':
                if(movement_check(point{drobot.x + 1, drobot.y}, instruction)) {
                    push_blocks(point{drobot.x + 1, drobot.y}, instruction);
                    drobot.x++;
                }
                break;
            case '^':
                if(movement_check(point{drobot.x, drobot.y - 1}, instruction)) {
                    push_blocks(point{drobot.x, drobot.y - 1}, instruction);
                    drobot.y--;
                }
                break;
            case 'v':
                if(movement_check(point{drobot.x, drobot.y + 1}, instruction)) {
                    push_blocks(point{drobot.x, drobot.y + 1}, instruction);
                    drobot.y++;
                }
                break;
        }
    }

    total = 0;
    for(point p: lblocks) {
        total += p.x + (p.y * 100);
    }
    cout << total << endl;

}

// checks if the point p can be pushed according to the double map rules, false if not and true otherwise
bool movement_check(point p, char direction) {
    // if this is a wall we cannot push, return
    if(dwalls.contains(p)) return false;
    // if this is an empty space we can push, return
    else if(!lblocks.contains(p) && !rblocks.contains(p)) return true;
    else switch(direction) {
        case '<':
            // skip ahead two spaces on horizontal to skip other both halves of the box
            return movement_check(point{p.x - 2, p.y}, direction);
        case '>':
            return movement_check(point{p.x + 2, p.y}, direction);
        case '^':
            // have to recursively check both halves of the box to proceed, both halves must be pushable
            if(lblocks.contains(p)) return movement_check(point{p.x, p.y - 1}, direction) && movement_check(point{p.x + 1, p.y - 1}, direction);
            else return movement_check(point{p.x, p.y - 1}, direction) && movement_check(point{p.x - 1, p.y - 1}, direction);
        case 'v':
            if(lblocks.contains(p)) return movement_check(point{p.x, p.y + 1}, direction) && movement_check(point{p.x + 1, p.y + 1}, direction);
            else return movement_check(point{p.x, p.y + 1}, direction) && movement_check(point{p.x - 1, p.y + 1}, direction);
    }
    return false;
}

void push_blocks(point p, char direction) {
    if(lblocks.contains(p) || rblocks.contains(p)) {
        switch(direction) {
            case '<':
                // push all blocks ahead of us first, otherwise we'll mess up all the data ahead of us
                push_blocks(point{p.x - 1, p.y}, direction);
                if(lblocks.contains(p)){ lblocks.erase(p); lblocks.insert(point{p.x - 1, p.y}); }
                else {                   rblocks.erase(p); rblocks.insert(point{p.x - 1, p.y}); }
                break;
            case '>':
                push_blocks(point{p.x + 1, p.y}, direction);
                if(lblocks.contains(p)){ lblocks.erase(p); lblocks.insert(point{p.x + 1, p.y}); }
                else {                   rblocks.erase(p); rblocks.insert(point{p.x + 1, p.y}); }
                break;
            case '^':
                if(lblocks.contains(p)) {
                    // push both halves of the block together
                    push_blocks(point{p.x, p.y - 1}, direction);
                    push_blocks(point{p.x + 1, p.y - 1}, direction);
                    lblocks.erase(p);
                    rblocks.erase(point{p.x + 1, p.y});
                    lblocks.insert(point{p.x, p.y - 1});
                    rblocks.insert(point{p.x + 1, p.y - 1});
                } else {
                    push_blocks(point{p.x, p.y - 1}, direction);
                    push_blocks(point{p.x - 1, p.y - 1}, direction);
                    rblocks.erase(p);
                    lblocks.erase(point{p.x - 1, p.y});
                    rblocks.insert(point{p.x, p.y - 1});
                    lblocks.insert(point{p.x - 1, p.y - 1});
                }
                break;
            case 'v':
                if(lblocks.contains(p)) {
                    push_blocks(point{p.x, p.y + 1}, direction);
                    push_blocks(point{p.x + 1, p.y + 1}, direction);
                    lblocks.erase(p);
                    rblocks.erase(point{p.x + 1, p.y});
                    lblocks.insert(point{p.x, p.y + 1});
                    rblocks.insert(point{p.x + 1, p.y + 1});
                } else {
                    push_blocks(point{p.x, p.y + 1}, direction);
                    push_blocks(point{p.x - 1, p.y + 1}, direction);
                    rblocks.erase(p);
                    lblocks.erase(point{p.x - 1, p.y});
                    rblocks.insert(point{p.x, p.y + 1});
                    lblocks.insert(point{p.x - 1, p.y + 1});
                }
                break;
        }
    }
}