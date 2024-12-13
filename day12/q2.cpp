#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <unordered_set>
#include <unordered_map>
#include <queue>
#include <stack>

using namespace std;

int trailhead(std::vector<std::vector<char>>& input) {
    int score = 0;
    for (int i = 0; i < input.size(); i++) {
        for (int j = 0; j < input[0].size(); j++) {
            if (input[i][j] == '.') continue;
            
            const char val = input[i][j];
            stack<pair<int, int>> q;
            q.push({i, j});

            int count = 0;
            int num_sides = 0;
            unordered_set<int> visited;

            while (q.size()) {
                const auto [x, y] = q.top();
                q.pop();
                if (input[x][y] == '.') continue;
                input[x][y] = '.';
                visited.insert(x * input.size() + y);
                count++;

                int okay_sides = 0;
                vector<bool> arr(4, false);

                const vector<int> dirs = {1, 0, -1, 0, 1}; // bottom, left, top, right
                for (int k = 0; k < 4; k++) {
                    const int dx = x + dirs[k];
                    const int dy = y + dirs[k+1];
                    if (dx < 0 || dy < 0 || dx >= input.size() || dy >= input[0].size()) {
                        continue;
                    }

                    if (input[dx][dy] != val && visited.find(dx * input.size() + dy) == visited.end()) {
                        continue; 
                    }
                    okay_sides++;
                    arr[k] = true;
                    q.push({dx, dy});
                }
                int additional_sides = 0;
                if (arr[0] && arr[1]) {
                    additional_sides += (input[x+1][y-1] != val && visited.find((x+1) * input.size() + y - 1) == visited.end());
                }
                if (arr[0] && arr[3]) {
                    additional_sides += (input[x+1][y+1] != val && visited.find((x+1) * input.size() + y + 1) == visited.end());
                } 
                if (arr[2] && arr[1]) {
                    additional_sides += (input[x-1][y-1] != val && visited.find((x-1) * input.size() + y - 1) == visited.end());
                }
                if (arr[2] && arr[3]) {
                    additional_sides += (input[x-1][y+1] != val && visited.find((x-1) * input.size() + y + 1) == visited.end());
                }
                num_sides += additional_sides;
                if (okay_sides == 1)
                    num_sides += 2;
                else if (okay_sides == 0) {
                    num_sides += 4;
                } else if (okay_sides == 2 && (!(arr[2] == true && arr[0] == true) && !(arr[1] == true && arr[3] == true))) {
                    num_sides += 1;
                }
            }
            score += count * num_sides;
            printf("val: %c   %d * %d = %d\n", val, count, num_sides, score);
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
    int result = trailhead(data);

    // Output the result
    std::cout << "Result from trailhead: " << result << std::endl;

    return 0;
}