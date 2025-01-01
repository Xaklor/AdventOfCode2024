#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

long get_bananas(long, long, long, long, long);

int main() {
    string line;
    ifstream input("input.txt");
    vector<long> secrets;
    while(getline(input, line)) {
        secrets.emplace_back(stol(line));
    }

    long p1_total = 0;
    for(long secret: secrets) {
        p1_total += get_bananas(42, 0, 0, 0, secret);
    }
    cout << p1_total << endl;

    long p2_total = 0;
    for(long a = -9; a < 10; a++) {
        for(long b = -9; b < 10; b++) {
            for(long c = -9; c < 10; c++) {
                for(long d = -9; d < 10; d++) {
                    long result = 0;
                    for(long secret: secrets) {
                        result += get_bananas(a, b, c, d, secret);
                    }
                    p2_total = max(p2_total, result);
                }
            }
        }
    }
    cout << p2_total << endl;
}

// returns the number of bananas you get for the given sequence, if a is 42 it gives the 2000th secret instead (for p1)
long get_bananas(long a, long b, long c, long d, long secret) {
    vector<long> prices { secret % 10 };
    for(long i = 0; i < 4; i++) {
        secret ^= secret << 6;
        secret %= 16777216;
        secret ^= secret >> 5;
        secret %= 16777216;
        secret ^= secret << 11;
        secret %= 16777216;
        prices.emplace_back(secret % 10);
    }

    for(long _ = 0; _ < 1996; _++) {
        if(prices[1] - prices[0] == a && prices[2] - prices[1] == b && prices[3] - prices[2] == c && prices[4] - prices[3] == d)
            return prices[4];

        secret ^= secret << 6;
        secret %= 16777216;
        secret ^= secret >> 5;
        secret %= 16777216;
        secret ^= secret << 11;
        secret %= 16777216;
        prices[0] = prices[1];
        prices[1] = prices[2];
        prices[2] = prices[3];
        prices[3] = prices[4];
        prices[4] = secret % 10;
    }

    if(a == 42) return secret;
    else return 0;
}