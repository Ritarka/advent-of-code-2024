#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <unordered_set>
#include <unordered_map>
#include <queue>
#include <stack>
#include <map>
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

    const int m = input.size();
    const int n = input[0].size();

    int count = 0;
    unordered_map<int, int> mp;
    queue<pair<int, int>> q;
    q.push({sx, sy});
    while (q.size()) {
        const auto [x, y] = q.front();
        q.pop();
        if (input[x][y] != '.') continue;
        if (mp.find(x * n + y) != mp.end()) continue;
        mp[x * n + y] = count;
        count++;

        q.push({x+1, y});
        q.push({x-1, y});
        q.push({x, y+1});
        q.push({x, y-1});
    }
    count--;

    map<int, int> shortcuts;
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            if (input[i][j] != '.') continue;

            for (int u = 0; u < m; u++) {
                for (int v = 0; v < n; v++) {
                    if (input[u][v] != '.') continue;
                    if (u == i && v == j) continue;

                    int man_dist = abs(i - u) + abs(j - v);
                    if (man_dist > 20) continue;

                    int save = mp[u * n + v] - mp[i * n + j] - man_dist;
                    if (save <= 0) continue;
                    shortcuts[save]++; 
                }
            }

        }
    }

    int sum = 0;
    int num = 0;
    for (const auto [time, count] : shortcuts) {
        // printf("%d %d\n", count, time);
        if (time >= 100) {
            sum += count;
        }
    }
    return sum;



    // int num_shortcuts = 0;

    // /// do bfs first and then find all edges
    // map<int, int> shortcuts;
    // for (int i = 0; i < m; i++) {
    //     for (int j = 0; j < n; j++) {
    //         if (input[i][j] != '.') continue;

    //         const int start_time = mp[i * n + j];

    //         unordered_set<int> visited;
    //         visited.insert(i * n + j);

    //         queue<tuple<int, int, int>> q;
    //         const vector<int> dirs = {1, 0, -1, 0, 1};
    //         for (int k = 0; k < 4; k++) {
    //             int nx = i + dirs[k];
    //             int ny = j + dirs[k+1];

    //             // if (input[nx][ny] != '#') continue;
    //             q.push({nx, ny, 1});

    //             while (q.size()) {
    //                 const auto [x, y, dist] = q.front();
    //                 q.pop();

    //                 if (x < 0 || y < 0 || x >= m || y >= n) continue;
                    
    //                 if (visited.find(x * n + y) != visited.end()) continue;
    //                 visited.insert(x * n + y);

    //                 if (dist < 20) {
    //                     q.push({x+1, y, dist+1});
    //                     q.push({x-1, y, dist+1});
    //                     q.push({x, y+1, dist+1});
    //                     q.push({x, y-1, dist+1});
    //                 }

    //                 if (input[x][y] == '.') {
    //                     if (dist > 20) continue;
    //                     const int end_time = mp[x * n + y];
    //                     int time_save = end_time - start_time - dist;

    //                     if (time_save <= 0) continue;
    //                     shortcuts[time_save]++;
    //                     // if (time_save == 74) {
    //                     //     // printf("%d %d\n", start_time, end_time);
    //                     //     printf("(%d %d) -> (%d %d) %d\n", i, j, x, y, k);
    //                     // }
    //                     // continue;
    //                 }


    //             }
    //         }

    //     }
    // }

    // int sum = 0;
    // int num = 0;
    // for (const auto [time, count] : shortcuts) {
    //     printf("%d %d\n", count, time);
    //     if (time >= 100) {
    //         sum += count;
    //     }
    // }

    // return sum;
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