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

int count = 0;
int target_score = 0;

int ex;
int ey;

unordered_set<int> points;

int fastest(std::vector<std::vector<char>>& input) {
    unordered_map<string, int> visited;
    int sx, sy, ex, ey;

    // Find start and end positions
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

    int shortest_distance = INT_MAX;
    vector<vector<tuple<int, int, char>>> all_shortest_paths;

    priority_queue<tuple<int, int, char, int, vector<tuple<int, int, char>>>,
    std::vector<tuple<int, int, char, int, vector<tuple<int, int, char>>>>,
    std::greater<>> st;
    st.push({0, sy, '>', sx, {}}); // Include path in the queue
    while (!st.empty()) {
        auto [dist, y, dir, x, path] = st.top();
        st.pop();

        // Add current node to the path
        path.push_back({x, y, dir});

        // Check if we reached the end
        if (x == ex && y == ey) {
            if (dist < shortest_distance) {
                shortest_distance = dist;
                all_shortest_paths.clear(); // Clear previous paths
            }
            if (dist == shortest_distance) {
                all_shortest_paths.push_back(path); // Add current path
            }
            // const auto copy = input;
            // for (const auto& [px, py, pdir] : path) {
            //     input[px][py] = pdir;
            // }

            // for (const auto vec : input) {
            //     for (char c : vec) {
            //         printf("%c ", c);
            //     }
            //     printf("\n");
            // }
            // printf("\n");

            continue;
        }

        // Skip obstacles or visited nodes
        if (input[x][y] == '#') continue;
        string hash = to_string(x) + "_" + to_string(y) + "_" + dir;
        if (visited.find(hash) != visited.end() && visited[hash] < dist) continue;
        visited[hash] = dist; // Update the shortest distance to this node and direction

        // Prune paths longer than the shortest distance found so far
        if (dist > shortest_distance) continue;

        // Define directions and their movement
        vector<char> dirs = {'<', '>', 'v', '^'};
        int dx = 0, dy = 0;
        if (dir == '>') dy = 1;
        else if (dir == '<') dy = -1;
        else if (dir == 'v') dx = 1;
        else if (dir == '^') dx = -1;

        // Continue moving in the current direction
        st.push({dist + 1, y + dy, dir, x + dx, path});

        // Add turns with penalty
        if (dir == '>') {
            st.push({dist + 1001, y, 'v', x + 1, path});
            st.push({dist + 1001, y, '^', x - 1, path});
        } else if (dir == '<') {
            st.push({dist + 1001, y, '^', x - 1, path});
            st.push({dist + 1001, y, 'v', x + 1, path});
        } else if (dir == 'v') {
            st.push({dist + 1001, y - 1, '<', x, path});
            st.push({dist + 1001, y + 1, '>', x, path});
        } else if (dir == '^') {
            st.push({dist + 1001, y - 1, '<', x, path});
            st.push({dist + 1001, y + 1, '>', x, path});
        }
    }

    // Output all shortest paths
    printf("All shortest paths (distance = %d):\n", shortest_distance);
    int sum = 0;
    unordered_set<int> stuff;
    printf("Num shortest paths: %d\n", (int)all_shortest_paths.size());
    for (const auto& path : all_shortest_paths) {
        sum += path.size();
        for (const auto& [px, py, pdir] : path) {
            input[px][py] = pdir;
            stuff.insert(px * input.size() + py);
        }
    }

    // for (const auto vec : input) {
    //     for (char c : vec) {
    //         printf("%c ", c);
    //     }
    //     printf("\n");
    // }
    // printf("\n");

    // unordered_map<string, int> visited2;
    // vector<int> paths;
    // dfs(sx, sy, '>', 0, visited2, input, paths);


    return stuff.size();
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