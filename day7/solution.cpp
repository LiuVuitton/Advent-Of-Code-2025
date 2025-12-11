#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_set>
#include <unordered_map>
#include <string>

int main() {
    std::ifstream input_file("input.txt");
    if (!input_file.is_open()) {
        std::cerr << "Error: could not open input.txt\n";
        return 1;
    }

    std::vector<std::string> tachyon_manifold;
    std::string line;
    while (std::getline(input_file, line)) {
        if (!line.empty()) {
            tachyon_manifold.push_back(line);
        }
    }
    input_file.close();

    // Part 1
    int start_pos = tachyon_manifold[0].find('S');

    int split_counter = 0;
    std::unordered_set<int> active_beam_positions;
    active_beam_positions.insert(start_pos);

    for (size_t row = 1; row < tachyon_manifold.size(); ++row) {
        const std::string &current_row = tachyon_manifold[row];
        std::unordered_set<int> next_active_positions;

        for (int col : active_beam_positions) {
            char cell = current_row[col];

            if (cell == '^') {
                if (col > 0) next_active_positions.insert(col - 1);
                if (col + 1 < current_row.size()) next_active_positions.insert(col + 1);
                ++split_counter;
            } else if (cell == '.') {
                next_active_positions.insert(col);
            }
        }

        active_beam_positions = std::move(next_active_positions);
    }

    std::cout << "Part 1: " << split_counter << "\n";
    
    return 0;
}
