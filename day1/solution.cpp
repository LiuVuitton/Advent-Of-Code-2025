#include <iostream>
#include <fstream>
#include <vector>
#include <utility>

// Part 1
int find_combination(const std::vector<std::pair<char, int>>& instructions);
// Part 2
int count_clicks(const std::vector<std::pair<char, int>>& instructions);

int main() {
    std::ifstream f("input.txt");   // open local file

    if (!f.is_open()) {
        std::cerr << "Error: could not open input.txt\n";
        return 1;
    }

    std::string line;
    std::vector<std::pair<char, int>> instructions;
    while (std::getline(f, line)) {
        if (line.empty()) continue;

        char dir = line[0];
        int dist = stoi(line.substr(1));
        instructions.push_back({dir, dist});
    }
    
    f.close();

    std::cout << "Part 1.\n";
    int pswd = find_combination(instructions);
    std::cout << "The correct combination is " << pswd << "\n";

    std::cout << "Part 2\n";
    int correct_pswd = count_clicks(instructions);
    std::cout  << "The number of clicks is " << correct_pswd << "\n";

    std::cout << (-5 % 100) << "\n";

    return 0;
}

int find_combination(const std::vector<std::pair<char, int>>& instructions) {
    int count = 0;
    int dial = 50;
    for (auto [dir, dist] : instructions) {
        if (dir == 'R') {
            dial = ((dial + dist) % 100 + 100) % 100;
        }
        else if (dir == 'L') {
            dial = ((dial - dist) % 100 + 100) % 100;
        }
        if (dial == 0) ++count;
    }
    return count;
}

int count_clicks(const std::vector<std::pair<char, int>>& instructions) {
    int count = 0;
    int dial = 50;
    int sign = 1;
    for (auto [dir, dist] : instructions) {
        if (dir == 'R') {
            sign = 1;
        }
        else if (dir == 'L') {
            sign = -1;
        }
        for (int i = 0; i < dist; ++i) {
            dial = ((dial + sign) % 100 + 100) % 100;
            if (dial == 0) ++count;
        }
    }
    return count;
}