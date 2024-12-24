#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <unordered_set>
#include <unordered_map>

using namespace std;

int antenna(std::vector<std::vector<char>>& input) {
    unordered_map<char, vector<pair<int, int>>> locations;
    for (int i = 0; i < input.size(); i++) {
        for (int j = 0; j < input[0].size(); j++) {
            const char val = input[i][j];
            if (val == '.') continue;
            locations[val].push_back({i, j});
        }
    }

    for (const auto [antenna, coords] : locations) {
        for (int i = 0; i < coords.size(); i++) {
            const auto [xa, ya] = coords[i];
            for (int j = i+1; j < coords.size(); j++) {
                const auto [xb, yb] = coords[j];
                const auto distx = xa - xb;
                const auto disty = ya - yb;

                // printf("Distx: %d disty: %d\n", distx, disty);

                auto xc = xa;
                auto yc = ya;
                auto xd = xb;
                auto yd = yb;

                while (xc >= 0 && yc >= 0 && xc < input.size() && yc < input[0].size()) {
                    input[xc][yc] = '#';
                    xc += distx;
                    yc += disty;
                }
                while (xd >= 0 && yd >= 0 && xd < input.size() && yd < input[0].size()) {
                    // printf("[%d %d] [%d %d]\n", xc, yc, xd, yd);
                    input[xd][yd] = '#';
                    xd -= distx;
                    yd -= disty;
                }

            }
        }
    }

    int count = 0;
    for (int i = 0; i < input.size(); i++) {
        for (int j = 0; j < input[0].size(); j++) {
            const char val = input[i][j];
            if (val == '#') count++;
        }
    }


    return count;
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
    int result = antenna(data);

    // Output the result
    std::cout << "Result from antenna: " << result << std::endl;

    return 0;
}