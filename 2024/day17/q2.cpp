#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <cmath>
#include <string>

using namespace std;

// Function to split a string by spaces and return the nth token
string getToken(const string &line, int n) {
    stringstream ss(line);
    string token;
    for (int i = 0; i <= n && ss >> token; i++);
    return token;
}

// Function to calculate the `get_combo` value
inline long get_combo(long num, long a, long b, long c) {
    if (num < 4) return num;
    if (num == 4) return a;
    if (num == 5) return b;
    if (num == 6) return c;
    return 0; // Should not happen
}

int main() {
    ifstream file("input.txt");
    if (!file.is_open()) {
        cerr << "Error opening file!" << endl;
        return 1;
    }

    string line;
    long a, b, c;

    // Read a, b, c from the first three lines
    getline(file, line); a = stol(getToken(line, 2));
    getline(file, line); b = stol(getToken(line, 2));
    getline(file, line); c = stol(getToken(line, 2));

    // Skip the next line
    getline(file, line);

    // Read program array
    getline(file, line);
    string programStr = getToken(line, 1);
    vector<long> program;
    stringstream ss(programStr);
    string num;
    while (getline(ss, num, ',')) {
        program.push_back(stol(num));
    }

    vector<long> output;
    vector<long> powersOfTwo(8); // Precomputed powers of two for faster division
    for (long i = 0; i < 8; ++i) {
        powersOfTwo[i] = 1L << i; // Efficient calculation of 2^i using bit shifts
    }

    long sa = 1, sb = b, sc = c;

    long l = 0;
    long r = 7;
    for (int i = program.size() - 1; i >= 0; i--) {
        const int target = program[i];
        int length = program.size() - i;
        printf("Testing position: %d with bounds %ld, %ld\n", i, l, r);
        for (long sa = l; sa <= r; sa++) {
            printf("Testing : %d\n", sa);
            long a = sa;
            long b = 0;
            long c = 0;
            int pos = 0;

            while (a) {
                b = a % 8;
                b = b ^ 2;
                c = a >> b;
                b = b ^ 3 ^ c;
                b = b % 8;
                if (b != program[i + pos]) break;
                pos++;
                if (pos == length) {
                    printf("Found target for position %d at a: %ld target %d\n", i, sa, target);
                    l = sa * 8;
                    r = sa * 9 - 1;
                    goto next_level;
                }
                a = a >> 3;
            }
        }
        next_level:;
    }

    // while (output != program) {
    //     output.clear();
    //     a = sa;
    //     b = 0;
    //     c = 0;

    //     if (sa % 10'000'000 == 0) {
    //         cout << sa << endl;
    //     }

    //     if (sa > 610) break;
    //     if (sa > 603 || sa < 536) {
    //         sa++;
    //         continue;
    //     }

    //     printf("\n ");
    //     printf("Sa:%ld -- ", sa);
    //     while (a) {
    //         b = a % 8;
    //         b = b ^ 2;
    //         c = a >> b;
    //         b = b ^ 3 ^ c;
    //         b = b % 8;
    //         printf("%ld ", b);
    //         a = a >> 3;
    //     }
    // end_loop:
    //     sa += 1; // Label for breaking out of the inner loop
    // }

    // cout << sa << endl;
    cout << endl;
    return 0;
}


/*




*/