#include <iostream>
#include <fstream>
#include <vector>
#include <string>

// Function declaration
int wordSearch(std::vector<std::vector<char>>& input);

int main() {
    // Open the file
    std::ifstream inputFile("input.txt");
    if (!inputFile) {
        std::cerr << "Error: Unable to open input.txt" << std::endl;
        return 1;
    }

    // Store the file contents into a 2D vector
    std::vector<std::vector<char>> data;
    std::string line;
    while (std::getline(inputFile, line)) {
        std::vector<char> row(line.begin(), line.end());
        data.push_back(row);
    }

    inputFile.close();

    // Call the wordSearch function with the 2D vector
    int result = wordSearch(data);

    // Output the result
    std::cout << "Result from wordSearch: " << result << std::endl;

    return 0;
}

int dfs(const std::string word, std::vector<std::vector<char>>& input, int pos, int i, int j) {

    if (word[pos] != input[i][j]) return 0;

    if (pos == word.size() - 1) {
        // printf("Finished :[%d %d]\n", i, j);
        return 1;
    }

    int count = 0;

    const char val = input[i][j];
    input[i][j] = '.';

    const std::vector<int> dirs = {1, 1, 0, -1, -1, 0, 1, -1, 1};
    for (int k = 0; k < 8; k++) {
        int x = i + dirs[k];
        int y = j + dirs[k+1];

        if (x < 0 || y < 0 || x >= input.size() || y >= input[0].size() || input[x][y] == '.') continue;

        count += dfs(word, input, pos + 1, x, y);
    }
    input[i][j] = val;
    return count;
}

int wordSearch(std::vector<std::vector<char>>& input) {
    int count = 0;

    static const std::string search_word = "XMAS";

    for (int i = 0; i < input.size(); i++) {
        for (int j = 0; j < input[0].size(); j++) {
            if (search_word[0] == input[i][j]) {
                // const int addition = dfs(search_word, input, 0, i, j);
                // count += addition;
                // printf("Addition: %d i: %d j: %d\n", addition, i, j);
                const std::vector<int> dirs = {1, 1, 0, -1, -1, 0, 1, -1, 1};
                for (int k = 0; k < 8; k++) {
                    int pos = 0;
                    int x = i;
                    int y = j;
                    while (search_word[pos] == input[x][y]) {
                        if (pos == search_word.size() - 1) {
                            count++;
                            break;
                        }
                        x += dirs[k];
                        y += dirs[k+1];
                        pos++;

                        if (x < 0 || y < 0 || x >= input.size() || y >= input[0].size()) break;

                    }                
                }

            }
        }
    }

    return count;
}