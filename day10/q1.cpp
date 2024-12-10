#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <unordered_set>
#include <unordered_map>

using namespace std;

int rdfs(const std::vector<std::vector<char>>& input, int i, int j, unordered_set<int>& visited) {
    const int val = input[i][j] - '0';
    if (val == 9) {
        if (visited.find(i * input.size() + j) != visited.end()) return 0;
        visited.insert(i * input.size() + j);
        return 1;
    }

    const vector<int> dirs = {1, 0, -1, 0, 1};
    int count = 0;
    for (int k = 0; k < 4; k++) {
        const int x = i + dirs[k];
        const int y = j + dirs[k+1];

        if (x < 0 || y < 0 || x >= input.size() || y >= input[0].size()) continue;
        if (input[x][y] - '0' != val + 1) continue;
        count += rdfs(input, x, y, visited);
    }
    return count;
}

int trailhead(const std::vector<std::vector<char>>& input) {
    int count = 0;
    for (int i = 0; i < input.size(); i++) {
        for (int j = 0; j < input[0].size(); j++) {
            if (input[i][j] != '0') continue;
            unordered_set<int> visited;
            count += rdfs(input, i, j, visited);
            // printf("Count %d\n", count);
        }
    }
    return count;
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
    int result = trailhead(data);

    // Output the result
    std::cout << "Result from trailhead: " << result << std::endl;

    return 0;
}