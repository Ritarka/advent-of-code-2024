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
    vector<string> max_clique;
    unordered_set<string> visited;
    for (const auto [key, set] : adj) {
        vector<string> clique;
        clique.push_back(key);
        for (auto it = adj.upper_bound(key); it != adj.end(); it++) {
            const auto [sub_key, sub_set] = *it;
            if (key == sub_key) continue;
            if (!set.contains(sub_key)) continue;

            bool acceptable = true;
            for (const auto neighbor : clique) {
                if (!sub_set.contains(neighbor)) acceptable = false;
            }
            if (!acceptable) continue;

            clique.push_back(sub_key);
        }
        if (clique.size() > max_clique.size()) {
            max_clique = clique;
        }
    }

    sort(max_clique.begin(), max_clique.end());
    string hash = "";
    for (int i = 0; i < max_clique.size() - 1; i++) {
        hash += max_clique[i] + ",";
    }
    hash += max_clique[max_clique.size()-1];
    cout << hash << endl;

    return 0;
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