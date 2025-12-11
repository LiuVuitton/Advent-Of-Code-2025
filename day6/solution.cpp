#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>

int main() {
    std::ifstream file("input.txt");
    if (!file.is_open()) {
        std::cerr << "Could not open input.txt\n";
        return 1;
    }

    std::vector<std::vector<int>> numbers;
    std::vector<char> operations;

    std::string line;
    std::vector<std::string> all_lines;

    while (std::getline(file, line))
        if (!line.empty()) all_lines.push_back(line);

    file.close();

    std::string op_line = all_lines.back();
    all_lines.pop_back();

    for (char c : op_line)
        if (c == '+' || c == '*') operations.push_back(c);

    for (auto& num_line : all_lines) {
        std::istringstream iss(num_line);
        std::vector<int> row;
        int n;
        while (iss >> n) row.push_back(n);
        numbers.push_back(row);
    }

    // Part 1
    int m = numbers.size();
    int n = numbers[0].size();
    long long total_val = 0;
    for (int i = 0; i < n; ++i) {
        long long col_val = operations[i] == '+' ? 0 : 1;
        for (int j = 0; j < m; ++j) {
            if (operations[i] == '+') {
                col_val += static_cast<long long>(numbers[j][i]);
            }
            else {
                col_val *= static_cast<long long>(numbers[j][i]);
            }
        }
        total_val += col_val;
    }
    std::cout << "Part 1: " << total_val << "\n";

    // Part 2
    

    return 0;
}
