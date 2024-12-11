#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <cmath>

using namespace std;

vector<long long> splitNumbers(const vector<long long>& numbers) {
    vector<long long> newNumbers;
    for (long long number : numbers) {
        if (number == 0) {
            newNumbers.push_back(1);
        } else {
            string numberStr = to_string(number);
            size_t length = numberStr.length();
            if (length % 2 == 0) {
                newNumbers.push_back(stoi(numberStr.substr(0, length / 2)));
                newNumbers.push_back(stoi(numberStr.substr(length / 2)));
            } else {
                newNumbers.push_back(number * 2024);
            }
        }
    }
    return newNumbers;
}

int main() {
    ifstream inputFile("input.txt");
    string line;

    if (!inputFile) {
        cerr << "Error opening file." << endl;
        return 1;
    }

    getline(inputFile, line);
    inputFile.close();

    vector<long long> numbers;
    stringstream ss(line);
    string temp;

    while (ss >> temp) {
        numbers.push_back(stoi(temp));
    }

    cout << "Initial numbers: ";
    for (long long num : numbers) {
        cout << num << " ";
    }
    cout << endl;

    for (long long i = 1; i <= 75; ++i) {
        numbers = splitNumbers(numbers);

        if (i < 7) {
            cout << "Iteration " << i << ": ";
            for (long long num : numbers) {
                cout << num << " ";
            }
            cout << endl;
        }

        cout << i << ": " << numbers.size() << endl;
    }

    return 0;
}
