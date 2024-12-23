#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <unordered_set>
#include <unordered_map>
#include <map>
#include <queue>
#include <stack>
#include <climits>
#include <algorithm>

using namespace std;


int subgroups(std::vector<string>& input) {
    map<string, unordered_set<string>> adj;
    for (string line : input) {
        string a = line.substr(0, line.find("-"));
        string b = line.substr(line.find("-")+1);

        // cout << a << "  " << b << endl;
        adj[a].insert(b);
        adj[b].insert(a);
    }

    int count = 0;
    unordered_set<string> visited;
    for (const auto [key, set] : adj) {
        for (auto it = adj.upper_bound(key); it != adj.end(); it++) {
            const auto [sub_key, sub_set] = *it;
            if (key == sub_key) continue;
            if (!set.contains(sub_key)) continue;
            for (const auto elem : sub_set) {
                if (set.contains(elem)) {
                    vector<string> elems = {key, sub_key, elem};
                    sort(elems.begin(), elems.end());
                    string hash = "";
                    bool has_t = false;
                    for (const auto str : elems) {
                        hash += str;
                        if (str[0] == 't') has_t = true;
                    }
                    if (visited.contains(hash) || !has_t) continue;
                    count++;
                    printf("%s,%s,%s\n", key.c_str(), sub_key.c_str(), elem.c_str());
                    visited.insert(hash);
                }
            }
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

    std::vector<string> data;
    std::string line;
    while (std::getline(inputFile, line)) {
        data.push_back(line);
    }

    inputFile.close();

    // Call the antenna function with the 2D vector
    int result = subgroups(data);

    // Output the result
    std::cout << "Result from subgroups: " << result << std::endl;

    return 0;
}