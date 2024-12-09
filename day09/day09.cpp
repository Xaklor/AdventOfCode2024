#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

struct block {
    int id, size;
};

int main() {
    string line;
    ifstream input("input.txt");
    getline(input, line);
    input.close();

    // part 1
    vector<int> files;
    int ID = 0;
    for(int i = 0; i < line.size(); i++) {
        if(i % 2 == 0) {
            for(int count = 0; count < line[i] - '0'; count++) {
                files.push_back(ID);
            }
            ID++;
        } else {
            for(int count = 0; count < line[i] - '0'; count++) {
                files.push_back(-1);
            }
        }
    }

    int i = 0;
    int j = files.size() - 1;
    long total = 0;
    while(i < j) {
        if(files[i] == -1) {
            files[i] = files[j];
            files[j] = -1;
            while(files[j] == -1)
                j--;
        }
        total += files[i] * i;
        i++;
    }

    // the last element wasn't counted during processing
    total += files[j] * j; 
    cout << total << endl;
    
    // part 2
    vector<block> drive;
    ID = 0;
    for(int i = 0; i < line.size(); i++) {
        if(i % 2 == 0) {
            drive.push_back(block{ ID, line[i] - '0' });
            ID++;
        } else
            drive.push_back(block{ -1, line[i] - '0' });
    }

    for(int i = drive.size() - 1; i >= 0; i--) {
        block current = drive[i];
        if(current.id != -1) {
            int j = 0;
            bool searching = true;
            while(searching && j < i) {
                if(drive[j].id == -1 && drive[j].size >= current.size) {
                    drive[j].size -= current.size;
                    if(drive[j].size == 0) 
                        drive.erase(drive.begin() + j);
                    else
                        i++;

                    drive.insert(drive.begin() + j, current);
                    drive[i].id = -1;
                    searching = false;
                } else j++;
            }
        }
    }

    total = 0;
    int pos = 0;
    for(int i = 0; i < drive.size(); i++) {
        if(drive[i].id != -1) {
            for(int count = 0; count < drive[i].size; count++) {
                total += drive[i].id * pos;
                pos++;
            }
        } else pos += drive[i].size;
    }

    cout << total << endl;
}