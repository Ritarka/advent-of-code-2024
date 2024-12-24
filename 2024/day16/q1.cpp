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
    unordered_set<string> visited;
    int sx;
    int sy;

    int ex;
    int ey;
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

    // ex = 9;
    // ey = 1;

    printf("Start: %d %d\n", sx, sy);
    printf("End: %d %d\n", ex, ey);

    


    int score = INT_MAX;
    priority_queue<tuple<int, int, char, int>,
                    vector<tuple<int, int, char, int>>,
                    std::greater<>> st;
    st.push({0, sy, '>', sx});
    while (st.size()) {
        const auto [dist, y, dir, x] = st.top();
        st.pop();
        printf("%d %d %c %d\n", x, y, dir, dist);

        if (x == ex && y == ey) {
            printf("Min: %d %d\n", dist, score);
            score = min(dist, score);
            continue;
        } else if (input[x][y] == '#') continue;

        string hash = to_string(x * input.size() + y) + to_string(dir);
        if (visited.contains(hash)) continue;
        visited.insert(hash);
        if (dist > score) continue;
        vector<char> dirs = {'<', '>', 'v', '^'};

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
        st.push({dist + 1, y + dy, dir, x + dx});

        if (dir == '>') {
            st.push({dist + 1000, y, 'v', x});
            st.push({dist + 1000, y, '^', x});
        } else if (dir == '<') {
            st.push({dist + 1000, y, '^', x});
            st.push({dist + 1000, y, 'v', x});
        } else if (dir == 'v') {
            st.push({dist + 1000, y, '<', x});
            st.push({dist + 1000, y, '>', x});
        } else if (dir == '^') {
            st.push({dist + 1000, y, '<', x});
            st.push({dist + 1000, y, '>', x});
        } 


    }

    return score;
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