#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <unordered_set>
#include <unordered_map>
#include <queue>
#include <stack>
#include <climits>
#include <algorithm>

using namespace std;

/*
+---+---+---+
| 7 | 8 | 9 |
+---+---+---+
| 4 | 5 | 6 |
+---+---+---+
| 1 | 2 | 3 |
+---+---+---+
    | 0 | A |
    +---+---+
*/
/*
    +---+---+
    | ^ | A |
+---+---+---+
| < | v | > |
+---+---+---+
*/


unordered_map<string, unordered_map<string, unordered_set<string>>> get_dir_map(std::vector<string>& input) {
    unordered_map<string, unordered_map<string, unordered_set<string>>> dir_map;
    vector<vector<string>> dir_keys = {
        {"X", "^", "A"},
        {"<", "v", ">"},
    };

    for (int i = 0; i < dir_keys.size(); i++) {
        for (int j = 0; j < dir_keys[0].size(); j++) {
            string val = dir_keys[i][j];

            queue<tuple<int, int, string>> q;
            q.push({i, j, ""});

            unordered_set<string> visited;
            while(q.size()) {
                auto [x, y, path] = q.front();
                q.pop();


                if (x < 0 || y < 0 || x >= dir_keys.size() || y >= dir_keys[0].size()) continue;

                const string value = dir_keys[x][y];
                if (value == "X") continue;
                if (visited.contains(value) && dir_map.at(val).at(value).begin()->size() != path.size()) continue;
                visited.insert(value);
                // printf("%d %d %s\n", x, y, path.c_str());
                dir_map[val][value].insert(path);

                q.push({x+1, y, path + "v"});
                q.push({x-1, y, path + "^"});
                q.push({x, y+1, path + ">"});
                q.push({x, y-1, path + "<"});
            }
        }
    } 
    return dir_map;
}

unordered_map<string, unordered_map<string, unordered_set<string>>> get_num_map(std::vector<string>& input) {
    unordered_map<string, unordered_map<string, unordered_set<string>>> num_map;
    vector<vector<string>> num_keys = {
        {"7", "8", "9"},
        {"4", "5", "6"},
        {"1", "2", "3"},
        {"X", "0", "A"},
    };

    for (int i = 0; i < num_keys.size(); i++) {
        for (int j = 0; j < num_keys[0].size(); j++) {
            string val = num_keys[i][j];

            queue<tuple<int, int, string>> q;
            q.push({i, j, ""});

            unordered_set<string> visited;
            while(q.size()) {
                auto [x, y, path] = q.front();
                q.pop();


                if (x < 0 || y < 0 || x >= num_keys.size() || y >= num_keys[0].size()) continue;

                const string value = num_keys[x][y];
                if (value == "X") continue;

                if (visited.contains(value) && num_map.at(val).at(value).begin()->size() != path.size()) continue;
                visited.insert(value);
                // printf("%d %d %s\n", x, y, path.c_str());
                num_map[val][value].insert(path);

                q.push({x+1, y, path + "v"});
                q.push({x-1, y, path + "^"});
                q.push({x, y+1, path + ">"});
                q.push({x, y-1, path + "<"});
            }
        }
    }
    return num_map;
}

int num_hits = 0;
unordered_map<string, long long> cache;
unordered_map<string, unordered_map<string, unordered_set<string>>> num_map;
unordered_map<string, unordered_map<string, unordered_set<string>>> dir_map;


long long get_min_cost(std::string sequence, int depth, bool numeric) {

    if (cache.find(sequence + to_string(depth)) != cache.end()) {
        num_hits++;
        return cache.at(sequence + to_string(depth));
    }

    long long ret = 0;
    string old_sequence = sequence;
    sequence = "A" + sequence;
    for (int i = 1; i < sequence.size(); i++) {
        const string a = string(1, sequence[i-1]);
        const string b = string(1, sequence[i]);
        unordered_set<string> paths;
        if (numeric) {
            paths = num_map.at(a).at(b);
        } else {
            paths = dir_map.at(a).at(b);
        }

        // printf("%s %s %d\n", a.c_str(), b.c_str(), (int)paths.size());
        // for (const auto& path : paths) {
        //     printf("%s .. %d\n", path.c_str(), path.size());
        // }
        // printf("\n");

        if (depth == 0) {
            long long mini = LONG_LONG_MAX;
            for (const auto path : paths) {
                mini = min(mini, (long long)path.size() + 1);
            }
            ret += mini;
        } else {
            long long mini = LONG_LONG_MAX;
            for (const auto path : paths) {
                mini = min(mini, get_min_cost(path + "A", depth-1, false));
            }
            ret += mini;
        }
        // printf("Ret: %d\n", ret);
    }
    cache[old_sequence + to_string(depth)] = ret;
    return ret;
}

long long fastest(std::vector<string>& input) {
    num_map = get_num_map(input);
    dir_map = get_dir_map(input);

    long long sum = 0;
    for (const auto str : input) {
        long long length = get_min_cost(str, 25, true);
        long long num_value = stoi(str.substr(0, 3));
        // printf("%d %d\n", length, num_value);
        sum += length * num_value;
        // printf("%d\n", sum);
        // break;
    }

    printf("Num hits: %d\n", num_hits);

    return sum;
}

int main() {
    std::ifstream inputFile("input.txt");
    if (!inputFile) {
        std::cerr << "Error: Unable to open input.txt" << std::endl;
        return 1;
    }

    std::vector<string> data;
    std::string line;
    while (std::getline(inputFile, line)) {
        data.push_back(line);
    }

    inputFile.close();

    // Call the antenna function with the 2D vector
    long long result = fastest(data);

    // Output the result
    std::cout << "Result from fastest: " << result << std::endl;

    return 0;
}

// with help from https://github.com/Fadi88/AoC/blob/master/2024/day21/code.py

/*
v<<A>>^AvA^Av<<A>>^AA<vA<A>>^AAvAA<^A>A<vA>^AA<A>Av<<A>A>^AAAvA<^A>A
<v<A>>^AvA^A<vA<AA>>^AAvA<^A>AAvA^A<vA>^AA<A>A<v<A>A>^AAAvA<^A>A
*/