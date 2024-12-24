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

int fastest(std::vector<string>& input) {
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

                if (visited.contains(value) && num_map[val][value].begin()->size() != path.size()) continue;
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

    for (const auto [str, set] : num_map["3"]) {
        for (const auto path : set)
            cout << str << " " << path << endl;
    }

// return 0;


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
                if (visited.contains(value) && dir_map[val][value].begin()->size() == path.size()) {
                    dir_map[val][value].insert(path);
                    continue;
                }
                if (visited.contains(value)) continue;
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

    for (const auto [str, set] : dir_map["A"]) {
        for (const auto path : set)
            cout << str << " " << path << endl;
    }

    int count = 0;
    for (auto code : input) {
        // if (code != "379A") continue;
        code = code;       // what robot 1 needs to press
        string hash1 = ""; // what robot 2 needs to press
        string hash2 = ""; // what robot 3 needs to press
        string hash3 = ""; // what you need to press

        vector<string> hash1s;
        hash1s.push_back("");

        // cout << "Start" << endl;

        code = "A" + code;
        for (int i = 1; i < code.size(); i++) {
            const auto paths = num_map[string(1, code[i-1])][string(1, code[i])];
            vector<string> new_set;
            for (string str : hash1s) {
                for (const auto path : paths) {
                    new_set.push_back(str + path + "A");
                }
                
            }
            hash1s = new_set;
        }
        // cout << "Hash1:" << endl;
        // for (const auto path : hash1s) {
        //     cout << path << endl;
        //     // ^A^<<^A>>AvvvA
        //     // ^A^^<<A>>AvvvA
        //     // ^A<<^^A>>AvvvA
        //     if (path == "^A<<^^A>>AvvvA")
        //         throw std::runtime_error("Smth");
        // }


        vector<string> hash2s;
        for (auto hash1 : hash1s) {
            vector<string> temp;
            temp.push_back("");
            hash1 = "A" + hash1;
            for (int i = 1; i < hash1.size(); i++) {
                const auto paths = dir_map[string(1, hash1[i-1])][string(1, hash1[i])];
                vector<string> new_temp;
                for (string str : temp) {
                    for (const auto path : paths) {
                        new_temp.push_back(str + path + "A");
                    }
                }
                temp = new_temp;
            }
            hash2s.insert(hash2s.end(), temp.begin(), temp.end());
        }

        // Print all hash2 paths
        // cout << "Hash2:" << endl;
        // for (const auto path : hash2s) {
        //     // cout << path << endl;
        //     if (path == "<A>Av<<AA>^AA>AvAA^A<vAAA>^A")
        //         throw std::runtime_error("Smth");
        // }

        // Generate hash3 from hash2
        vector<string> hash3s;
        for (auto hash2 : hash2s) {
            vector<string> temp;
            temp.push_back("");
            hash2 = "A" + hash2;
            for (int i = 1; i < hash2.size(); i++) {
                const auto paths = dir_map[string(1, hash2[i-1])][string(1, hash2[i])];
                vector<string> new_temp;
                for (string str : temp) {
                    for (const auto path : paths) {
                        new_temp.push_back(str + path + "A");
                    }
                }
                temp = new_temp;
            }
            hash3s.insert(hash3s.end(), temp.begin(), temp.end());
        }

        int min_size = INT_MAX;
        for (const auto path : hash3s) {
            min_size = min(min_size, (int)path.size());
        }

        // for (const auto path : hash3s) {
        //     if (path.size() == min_size)
        //         cout << path << endl;
        // }


        // Final stats
        int size = stoi(code.substr(1, 3)) * min_size;
        printf("Hash3 Size: %d | Code Value: %d | Total: %d\n", min_size, stoi(code.substr(1, 3)), size);

        count += size;
        // break;
    }

    return count;
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
    int result = fastest(data);

    // Output the result
    std::cout << "Result from fastest: " << result << std::endl;

    return 0;
}



/*
v<<A>>^AvA^Av<<A>>^AA<vA<A>>^AAvAA<^A>A<vA>^AA<A>Av<<A>A>^AAAvA<^A>A
<v<A>>^AvA^A<vA<AA>>^AAvA<^A>AAvA^A<vA>^AA<A>A<v<A>A>^AAAvA<^A>A
*/