#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <unordered_set>

// Function declaration
int simulation(std::vector<std::vector<char>> input);

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

    int count = 0;
    // Call the simulation function with the 2D vector
    for (int i = 0; i < data.size(); i++) {
        for (int j = 0; j < data[0].size(); j++) {
            if (data[i][j] == '^') continue;
            const char prev = data[i][j];
            data[i][j] = '#';
            int result = simulation(data);
            if (result == -1) count++;
            data[i][j] = prev;
        }
    }

    // Output the result
    std::cout << "Result from simulation: " << count << std::endl;

    return 0;
}

int simulation(std::vector<std::vector<char>> input) {

    std::unordered_set<std::string> loop;

    int x = 0;
    int y = 0;
    bool found = false;
    for (int i = 0; i < input.size(); i++) {
        for (int j = 0; j < input[0].size(); j++) {
            if (input[i][j] == '^') {
                x = i;
                y = j;
                found = true;
                break;
            }
        }
        if (found) break;
    }

    while (true) {
        int i;
        int j;
        const char curr = input[x][y];
        // printf("%c %d %d\n", curr, x, y);
        if (curr == '^') {
            i = x - 1;
            j = y;
        } else if (curr == '>') {
            i = x;
            j = y + 1;
        } else if (curr == '<') {
            i = x;
            j = y - 1;
        } else if (curr == 'V') {
            i = x + 1;
            j = y;
        } else {
            printf("Got %c at %d %d\n", curr, x, y);
            break;
            // throw std::runtime_error("Should not happen!");
        }

        std::string hash = std::to_string(i) + "i" + std::to_string(j) + "j" + std::to_string(curr);
        if (loop.find(hash) != loop.end()) {
            // for (int i = 0; i < input.size(); i++) {
            //     for (int j = 0; j < input[0].size(); j++) {
            //         printf("%c ", input[i][j]);
            //     }
            //     printf("\n");
            // }
            // printf("\n");

            return -1;
        }
        loop.insert(hash);

        if (i < 0 || j < 0 || i >= input.size() || j >= input[0].size()) {
            input[x][y] = 'X';
            break;
        }
        const char next = input[i][j];
        if (next == '#') {
            i = x;
            j = y;
            if (curr == '^') {
                input[i][j] = '>';
            } else if (curr == '>') {
                input[i][j] = 'V';
            } else if (curr == '<') {
                input[i][j] = '^';
            } else if (curr == 'V') {
                input[i][j] = '<';
            }
        } else {
            input[x][y] = 'X';
            input[i][j] = curr;
        }
        x = i;
        y = j;
    }

    int count = 0;


    return count;
}