#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <unordered_set>
#include <unordered_map>
#include <queue>
#include <stack>
#include <climits>

using namespace std;

int fastest(std::vector<std::vector<char>>& input) {
    int sx;
    int sy;

    int ex;
    int ey;

    for (int i = 0; i < input.size(); i++) {
        const auto vec = input[i];
        for (int j = 0; j < input[0].size(); j++) {
            char c = vec[j];
            if (c == 'S') {
                sx = i;
                sy = j;
            } else if (c == 'E') {
                ex = i;
                ey = j;
            }
        }
    }

    input[sx][sy] = '.';
    input[ex][ey] = '.';

    int count = 0;
    unordered_map<int, int> mp;
    queue<pair<int, int>> q;
    q.push({sx, sy});
    while (q.size()) {
        const auto [x, y] = q.front();
        q.pop();
        if (input[x][y] != '.') continue;
        if (mp.find(x * input.size() + y) != mp.end()) continue;
        mp[x * input.size() + y] = count;
        count++;

        q.push({x+1, y});
        q.push({x-1, y});
        q.push({x, y+1});
        q.push({x, y-1});
    }
    count--;

    unordered_map<int, int> shortcuts;
    const int n = input.size();
    const int m = input[0].size();
    for (int i = 1; i < n-1; i++) {
        for (int j = 1; j < m-1; j++) {
            if (input[i][j] != '#') continue;
            int diff = INT_MAX;
            if (input[i+1][j] != '#' && input[i-1][j] != '#') {
                diff = abs(mp[(i+1) * m  + j] - mp[(i-1) * m  + j]);
            }
            if (input[i][j+1] != '#' && input[i][j-1] != '#') {
                diff = min(diff, abs(mp[i * m  + j + 1] - mp[i * m  + j - 1]));
            }
            if (diff != INT_MAX)
                shortcuts[diff-2]++;
        }
    }

    int sum = 0;
    for (const auto [time, count] : shortcuts) {
        printf("%d %d\n", count, time);
        if (time >= 100) {
            sum += count;
        }
    }

    return sum;
}

int main() {
    std::ifstream inputFile("input.txt");
    if (!inputFile) {
        std::cerr << "Error: Unable to open input.txt" << std::endl;
        return 1;
    }

    std::vector<std::vector<char>> data;
    std::string line;
    while (std::getline(inputFile, line)) {
        std::vector<char> row(line.begin(), line.end());
        data.push_back(row);
    }

    inputFile.close();

    // Call the antenna function with the 2D vector
    int result = fastest(data);

    // Output the result
    std::cout << "Result from fastest: " << result << std::endl;

    return 0;
}