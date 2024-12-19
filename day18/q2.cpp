#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <unordered_set>
#include <unordered_map>
#include <queue>
#include <stack>
#include <format>

using namespace std;

int simulation(std::vector<std::vector<char>>& grid) {

    // for (const auto bec : grid) {
    //     for (const auto c : bec) {
    //         printf("%c ", c);
    //     }
    //     printf("\n");
    // }
    // printf("\n");

    int size = grid.size();

    queue<tuple<int, int, int>> q;
    unordered_set<int> visited;
    q.push({0, 0, 0});
    while (q.size()) {
        const auto [x, y, dist] = q.front();
        q.pop();
        int hash = x * size + y;

        if (visited.contains(hash)) continue;
        visited.insert(hash);

        if (x == size - 1 && y == size - 1) return dist;

        const vector<int> dirs = {1, 0, -1, 0, 1};
        for (int i = 0; i < 4; i++) {
            int nx = x + dirs[i];
            int ny = y + dirs[i + 1];

            if (nx < 0 || ny < 0 || nx >= size || ny >= size) continue;
            if (grid[nx][ny] != '.') continue;
            q.push({nx, ny, dist + 1});
        }
    }

    // for (const auto bec : grid) {
    //     for (const auto c : bec) {
    //         printf("%c ", c);
    //     }
    //     printf("\n");
    // }
    // printf("\n");


    return -1;
}

int main() {
    std::ifstream inputFile("input.txt");
    if (!inputFile) {
        std::cerr << "Error: Unable to open input.txt" << std::endl;
        return 1;
    }

    std::string line;

    // int size = 7;
    // int num = 12;

    int size = 71;
    int num = 1024;
    vector<vector<char>> grid(size, vector<char>(size, '.'));

    std::vector<char> directions;
    int count = 0;
    while (std::getline(inputFile, line)) {
        int x = stoi(line.substr(0, line.find(',')));
        int y = stoi(line.substr(line.find(',')+1));

        grid[y][x] = '#';

        if (count < num) {
            count++;
            continue;
        }

        printf("Testing count : %d\n", count);

        int result = simulation(grid);
        if (result == -1) {
            printf("%d %d\n", x, y);
            break;
        }
        count++;
    }

    inputFile.close();

    // std::cout << "Result from simulation: " << result << std::endl;

    return 0;
}