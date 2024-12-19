#include <iostream>
#include <sstream>
#include <algorithm>
#include <fstream>
#include <vector>
#include <string>
#include <unordered_set>
#include <unordered_map>
#include <queue>
#include <stack>
#include <format>

using namespace std;

// Function to split a string by spaces and remove commas
vector<string> splitString(const string& str) {
    vector<string> result;
    stringstream ss(str);
    string word;
    while (ss >> word) {
        // Remove commas from the word
        word.erase(remove(word.begin(), word.end(), ','), word.end());
        result.push_back(word);
    }
    return result;
}

bool check(const unordered_set<string>& dict, string s) {
    int n = s.size();
    int max_size = 0;
    for (const string word : dict) {
        max_size = max(max_size, (int)word.size());
    }

    vector<bool> dp(n + 1, false);
    dp[0] = true;
    for (int i = 0; i < n; i++) {
        if (dp[i] == false) continue;
        for (int l = 1; l <= min(n - i, max_size); l++) {
            string check = s.substr(i, l);
            if (dict.contains(check)) {
                dp[i + l] = true;
            }
        }
    }
    return dp[n];
}

int main() {
    ifstream inputFile("input.txt");
    if (!inputFile) {
        cerr << "Error: Could not open the file." << endl;
        return 1;
    }

    string line;

    // Read the first line as the vector of words
    getline(inputFile, line);
    vector<string> words = splitString(line);

    // Read the next lines as queries
    vector<string> queries;
    while (getline(inputFile, line)) {
        if (!line.empty()) {
            queries.push_back(line);
        }
    }

    inputFile.close();

    // Output the parsed data (for debugging purposes)
    cout << "Words:" << endl;
    for (const auto& word : words) {
        cout << word << " ";
    }
    cout << endl;

    cout << "Queries:" << endl;
    for (const auto& query : queries) {
        cout << query << endl;
    }

    int num_possible = 0;
    unordered_set<string> dict(words.begin(), words.end());
    for (const auto& query : queries) {
        bool possible = check(dict, query);
        if (possible == true) num_possible++;
    }

    printf("Total Possible: %d\n", num_possible);

    return 0;
}
