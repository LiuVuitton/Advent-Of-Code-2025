#include <bits/stdc++.h>

int find_combination(const std::vector<std::pair<char, int>>& instructions) {
    int count = 0;
    int dial = 50;
    for (auto [dir, dist] : instructions) {
        switch (dir) {
            case 'R':
                dial = (dial + dist) % 100;
                break;
            case 'L': 
                dial = (dial - dist) % 100;
                break;
            default:
                break;
        }
        if (dial == 0) ++count;
    }
    return count;
}

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

    int pswd = find_combination(instructions);
    std::cout << "The correct combination is " << pswd << "\n";

    return 0;
}
