#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>

int max_output_joltage(const std::string& bank) {
    int n = bank.size();
    auto it = std::max_element(bank.begin(), bank.end());
    
    if (it + 1 != bank.end()) {
        char max_after = *std::max_element(it + 1, bank.end());
        return 10 * (*it - '0') + (max_after - '0');
    }

    char max_before = *std::max_element(bank.begin(), it);
    return 10 * (max_before - '0') + (*it - '0');
}


int total_output_joltage(const std::vector<std::string>& banks) {
    int total = 0;
    for (const std::string& bank : banks) {
        total += max_output_joltage(bank);
    }
    return total;
}

int main() {
    std::ifstream f("input.txt");

    if (!f.is_open()) {
        std::cerr << "Error: could not open input.txt\n";
        return 1;
    }

    std::string line;
    std::vector<std::string> banks;

    while (std::getline(f, line)) {
        if (!line.empty())
            banks.push_back(line);
    }

    int result = total_output_joltage(banks);
    std::cout << result << "\n";

    return 0;
}
