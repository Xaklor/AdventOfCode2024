#include <iostream>
#include <fstream>
#include <vector>
#include <regex>
using namespace std;

int main() {
    // part 1
    string line;
    ifstream input1("input.txt");
    vector<string> instructions = vector<string>();
    regex e1 ("mul\\(\\d{1,3},\\d{1,3}\\)");
    while (getline (input1, line)) {
        regex_iterator<string::iterator> iter (line.begin(), line.end(), e1);
        regex_iterator<string::iterator> rend;

        while (iter != rend) {
            instructions.emplace_back(iter->str());
            ++iter;
        }
    }
    input1.close();

    int total = 0;
    for (string entry: instructions) {
        int a = stoi(entry.substr(4, entry.find(",")));
        int b = stoi(entry.substr(entry.find(",") + 1, entry.length()));
        total += a * b;
    }
    cout << total << endl;

    // part 2
    ifstream input2("input.txt");
    instructions = vector<string>();
    regex e2 ("mul\\(\\d{1,3},\\d{1,3}\\)|do\\(\\)|don't\\(\\)");
    while (getline (input2, line)) {
        regex_iterator<string::iterator> iter (line.begin(), line.end(), e2);
        regex_iterator<string::iterator> rend;

        while (iter != rend) {
            instructions.emplace_back(iter->str());
            ++iter;
        }
    }
    input2.close();

    total = 0;
    bool enabled = true;
    for (string entry: instructions) {
        if (enabled && entry.substr(0, 3) == "mul") {
            int a = stoi(entry.substr(4, entry.find(",")));
            int b = stoi(entry.substr(entry.find(",") + 1, entry.length()));
            total += a * b;
        }
        else if (entry.substr(0, 5) == "don't")
            enabled = false;
        else if (entry.substr(0, 2) == "do")
            enabled = true;
    }
    cout << total << endl;
}