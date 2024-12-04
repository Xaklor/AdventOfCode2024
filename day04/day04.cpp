#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

bool validate_xmas(int, int, int, vector<string>);
bool validate_x_mas(int, int, vector<string>);

int main() {
    string line;
    ifstream input1("input.txt");
    vector<string> grid = vector<string>();
    while (getline (input1, line)) {
        grid.emplace_back(line);
    }
    input1.close();

    // part 1
    int w = grid.size();
    int h = grid[0].size();
    int total = 0;
    for (int i = 0; i < w; i++) {
        for (int j = 0; j < h; j++){
            if (grid[i][j] == 'X') {
            if (j >= 3 && validate_xmas(i, j, 0, grid))
                total += 1;
            if (i <= w - 4 && j >= 3 && validate_xmas(i, j, 1, grid))
                total += 1;
            if (i <= w - 4 && validate_xmas(i, j, 2, grid))
                total += 1;
            if (i <= w - 4 && j <= h - 4 && validate_xmas(i, j, 3, grid))
                total += 1;
            if (j <= h - 4 && validate_xmas(i, j, 4, grid))
                total += 1;
            if (i >= 3 && j <= h - 4 && validate_xmas(i, j, 5, grid))
                total += 1;
            if (i >= 3 && validate_xmas(i, j, 6, grid))
                total += 1;
            if (i >= 3 && j >= 3 && validate_xmas(i, j, 7, grid))
                total += 1;
            }
        }
    }
    cout << total << endl;

    // part 2
    total = 0;
    for (int i = 1; i < w - 1; i++) {
        for (int j = 1; j < h - 1; j++){
            if (grid[i][j] == 'A' && validate_x_mas(i, j, grid))
                total += 1;
        }
    }
    cout << total << endl;
}

// direction: 0-7, N, NE, E, SE, S, SW, W, NW
bool validate_xmas(int i, int j, int direction, vector<string> grid) {
    switch (direction) {
        case 0:
            return grid[i][j] == 'X' && grid[i][j - 1] == 'M' && grid[i][j - 2] == 'A' && grid[i][j - 3] == 'S';
        case 1:
            return grid[i][j] == 'X' && grid[i + 1][j - 1] == 'M' && grid[i + 2][j - 2] == 'A' && grid[i + 3][j - 3] == 'S';
        case 2:
            return grid[i][j] == 'X' && grid[i + 1][j] == 'M' && grid[i + 2][j] == 'A' && grid[i + 3][j] == 'S';
        case 3:
            return grid[i][j] == 'X' && grid[i + 1][j + 1] == 'M' && grid[i + 2][j + 2] == 'A' && grid[i + 3][j + 3] == 'S';
        case 4:
            return grid[i][j] == 'X' && grid[i][j + 1] == 'M' && grid[i][j + 2] == 'A' && grid[i][j + 3] == 'S';
        case 5:
            return grid[i][j] == 'X' && grid[i - 1][j + 1] == 'M' && grid[i - 2][j + 2] == 'A' && grid[i - 3][j + 3] == 'S';
        case 6:
            return grid[i][j] == 'X' && grid[i - 1][j] == 'M' && grid[i - 2][j] == 'A' && grid[i - 3][j] == 'S';
        case 7:
            return grid[i][j] == 'X' && grid[i - 1][j - 1] == 'M' && grid[i - 2][j - 2] == 'A' && grid[i - 3][j - 3] == 'S';
    }
    return false;
}

bool validate_x_mas(int i, int j, vector<string> grid) {
    char nw = grid[i - 1][j - 1];
    char ne = grid[i + 1][j - 1];
    char se = grid[i + 1][j + 1];
    char sw = grid[i - 1][j + 1];
    return (nw == 'M' && ne == 'M' && se == 'S' && sw == 'S') || 
           (nw == 'S' && ne == 'M' && se == 'M' && sw == 'S') || 
           (nw == 'S' && ne == 'S' && se == 'M' && sw == 'M') || 
           (nw == 'M' && ne == 'S' && se == 'S' && sw == 'M');
}