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

int simulation(std::vector<std::vector<char>>& unmodified, std::vector<char>& movements) {

    std::vector<std::vector<char>> grid(unmodified.size(), vector<char>());
    for (int i = 0; i < unmodified.size(); i++) {
        for (int j = 0; j < unmodified[0].size(); j++) {
            char c = unmodified[i][j];
            if (c == '#') {
                grid[i].push_back('#');
                grid[i].push_back('#');
            } else if (c == 'O') {
                grid[i].push_back('[');
                grid[i].push_back(']');
            } else if (c == '.') {
                grid[i].push_back('.');
                grid[i].push_back('.');
            } else if (c == '@') {
                grid[i].push_back('@');
                grid[i].push_back('.');
            }
        }
    }


    for (const auto vec : grid) {
        for (const auto c : vec) {
            printf("%c ", c);
        }
        printf("\n");
    }
    printf("\n");


    pair<int, int> pos;
    for (int i = 0; i < grid.size(); i++) {
        for (int j = 0; j < grid[0].size(); j++) {
            char c = grid[i][j];
            if (c == '@') {
                pos.first = i;
                pos.second = j;
                goto exit;
            }
        }
    }
    printf("No robot found!\n");
    return 0;

exit:
    printf("@ found in position (%d %d)\n", pos.first, pos.second);

    for (const char movement : movements) {
        pair<int, int> dir;
        if (movement == '<') {
            dir = {0, -1};
        } else if (movement == '>') {
            dir = {0, 1};
        } else if (movement == 'v') {
            dir = {1, 0};
        } else if (movement == '^') {
            dir = {-1, 0};
        } else {
            throw std::runtime_error(std::format("Unexpected value: {}\n", movement));
        }
        printf("Moving %c\n", movement);

        int x = pos.first;
        int y = pos.second;
        // printf("%c -- (%d %d)\n", grid[x][y], x, y);

        if ((movement == '^' || movement == 'v') && (grid[x+dir.first][y+dir.second] == '[' || grid[x+dir.first][y+dir.second] == ']')) {
            vector<pair<int, int>> positions;
            unordered_set<int> visited;
            positions.push_back({x, y});
            visited.insert(x * grid.size() + y);
            int i = 0;
            bool possible = true;
            while (true) {
                if (i >= positions.size()) break;
                const auto [a, b] = positions[i];
                int ta = a + dir.first;
                int tb = b + dir.second;
                const char next = grid[ta][tb];
                if (next == '#') {
                    possible = false;
                    break;
                } else if (next == '[') {
                    if (!visited.contains(ta * grid.size() + tb)) {
                        visited.insert(ta * grid.size() + tb);
                        positions.push_back({ta, tb});
                    }
                    if (!visited.contains(ta * grid.size() + tb + 1)) {
                        visited.insert(ta * grid.size() + tb + 1);
                        positions.push_back({ta, tb + 1});
                    }
                } else if (next == ']') {
                    if (!visited.contains(ta * grid.size() + tb)) {
                        visited.insert(ta * grid.size() + tb);
                        positions.push_back({ta, tb});
                    }
                    if (!visited.contains(ta * grid.size() + tb - 1)) {
                        visited.insert(ta * grid.size() + tb - 1);
                        positions.push_back({ta, tb - 1});
                    }
                }
                i++;
            }
            if (!possible) continue;
            for (int i = positions.size() - 1; i >= 0; i--) {
                grid[positions[i].first + dir.first][positions[i].second + dir.second] = grid[positions[i].first][positions[i].second];
                grid[positions[i].first][positions[i].second] = '.';
            }
        } else {
            bool empty_space = true;
            while (grid[x][y] != '.') {
                x += dir.first;
                y += dir.second;
                // printf("%c -- (%d %d)\n", grid[x][y], x, y);
                if (grid[x][y] == '#') {
                    empty_space = false;
                    break;
                }
            }
            if (!empty_space) continue;
            while (x != pos.first || y != pos.second) {
                // printf("%c (%d %d) -- %c (%d %d)\n", grid[x][y], x, y, grid[x-dir.first][y-dir.second], x-dir.first, y-dir.second);
                grid[x][y] = grid[x-dir.first][y-dir.second];
                grid[x-dir.first][y-dir.second] = '.';
                x = x - dir.first;
                y = y - dir.second;
            }
        }
        pos.first += dir.first;
        pos.second += dir.second;

        // for (const auto vec : grid) {
        //     for (const auto c : vec) {
        //         printf("%c ", c);
        //     }
        //     printf("\n");
        // }
        // printf("\n");
    }


    int sum = 0;
    for (int i = 0; i < grid.size(); i++) {
        for (int j = 0; j < grid[0].size(); j++) {
            char c = grid[i][j];
            if (c == '[') {
                sum += 100 * i + j;
            }
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

    std::vector<char> directions;
    bool stage = false;
    while (std::getline(inputFile, line)) {
        if (line == "") {
            stage = true;
            continue;
        }
        std::vector<char> row(line.begin(), line.end());
        if (!stage) {
            data.push_back(row);
        } else {
            directions.insert(directions.end(), row.begin(), row.end());
        }
    }

    inputFile.close();

    // Call the antenna function with the 2D vector
    int result = simulation(data, directions);

    // Output the result
    std::cout << "Result from simulation: " << result << std::endl;

    return 0;
}