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

int ex;
int ey;
int score = INT_MAX;

void dfs(int x, int y, char dir, int dist, unordered_map<string, int>& visited, std::vector<std::vector<char>>& input) {
    if (x == ex && y == ey) {
        printf("Min: %d %d\n", dist, score);
        score = min(dist, score);

        // for (int i = 0; i < input.size(); i++) {
        //     for (int j = 0; j < input[0].size(); j++) {
        //         printf("%c ", input[i][j]);
        //     }
        //     printf("\n");
        // }
        // printf("\n");

        return;
    } else if (input[x][y] == '#') return;

    string hash = to_string(x * input.size() + y);
    if (visited.find(hash) != visited.end()y) return;
    visited[hash] = dist;
    vector<char> dirs = {'<', '>', 'v', '^'};

    for (int i = 0; i < input.size(); i++) {
        for (int j = 0; j < input[0].size(); j++) {
            printf("%c ", input[i][j]);
        }
        printf("\n");
    }
    printf("\n");


    input[x][y] = dir;

    int dx = 0;
    int dy = 0;
    if (dir == '>') {
        dy = 1;
    } else if (dir == '<') {
        dy = -1;
    } else if (dir == 'v') {
        dx = 1;
    } else if (dir == '^') {
        dx = -1;
    } 
    dfs(x + dx, y + dy, dir, dist + 1, visited, input);

    if (dir == '>') {
        dfs(x, y, 'v', dist + 1000, visited, input);
        dfs(x, y, '^', dist + 1000, visited, input);
    } else if (dir == '<') {
        dfs(x, y, '^', dist + 1000, visited, input);
        dfs(x, y, 'v', dist + 1000, visited, input);
    } else if (dir == 'v') {
        dfs(x, y, '<', dist + 1000, visited, input);
        dfs(x, y, '>', dist + 1000, visited, input);
    } else if (dir == '^') {
        dfs(x, y, '<', dist + 1000, visited, input);
        dfs(x, y, '>', dist + 1000, visited, input);
    }

    input[x][y] = '.';
}


int fastest(std::vector<std::vector<char>>& input) {
    int sx;
    int sy;

    for (int i = 0; i < input.size(); i++) {
        for (int j = 0; j < input[0].size(); j++) {
            if (input[i][j] == 'S') {
                sx = i;
                sy = j;
            } else if (input[i][j] == 'E') {
                ex = i;
                ey = j;
            }
        }
    }

    printf("Start: %d %d\n", sx, sy);
    printf("End: %d %d\n", ex, ey);

    unordered_map<string, int> visited;
    dfs(sx, sy, '>', 0, visited, input);
    // st.push({sx, sy, '>', 0});

    return score;
}


int main() {
    std::ifstream inputFile("test1.txt");
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