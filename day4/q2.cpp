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
        std::cerr << "Error: Unable to open test2.txt" << std::endl;
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

int wordSearch(std::vector<std::vector<char>>& input) {
    int count = 0;

    static const std::string search_word = "XMAS";

    for (int i = 0; i <= input.size() - 3; i++) {
        for (int j = 0; j <= input[0].size() - 3; j++) {
            const char val = input[i][j];
            if (val == 'X' || val == 'A') continue;
            bool check1 = val != input[i+2][j+2];
            bool check5 = input[i+2][j+2] == 'S' || input[i+2][j+2] == 'M';

            bool check2 = input[i+2][j] != input[i][j+2];
            bool check3 = input[i+2][j] == 'S' && input[i][j+2] == 'M';
            bool check4 = input[i+2][j] == 'M' && input[i][j+2] == 'S';

            bool check6 = input[i+1][j+1] == 'A';

            // if (i == 1 && j == 5) {
            //     for (int x = 0; x < 3; x++) {
            //         for (int y = 0; y < 3; y++) {
            //             printf("%c ", input[i + x][j + y]);
            //         }
            //         printf("\n");
            //     }
            //     printf("%d %d %d %d %d %d\n", check1, check2, check3, check4, check5, check6);
            // }

            if (check1 && check2 && check6 && check5 && (check3 || check4)) {
                // printf("[%d %d]\n", i, j);
                count++;
            }
        }
    }

    return count;
}