#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_set>
#include <unordered_map>
#include <string>

// Count how many times beams split
int count_splits(const std::vector<std::string>& grid, int start_col);
// Part 2: Count total timelines after quantum splitting
long long count_timelines(const std::vector<std::string>& grid, int start_col);

int main() {
    std::ifstream input_file("input.txt");
    if (!input_file.is_open()) {
        std::cerr << "Error: could not open input.txt\n";
        return 1;
    }

    std::vector<std::string> grid;
    std::string line;

    while (std::getline(input_file, line)) {
        if (!line.empty()) {
            grid.push_back(line);
        }
    }

    input_file.close();

    int start_col = grid[0].find('S');

    int part1_result = count_splits(grid, start_col);
    long long part2_result = count_timelines(grid, start_col);

    std::cout << "Part 1: " << part1_result << "\n";
    std::cout << "Part 2: " << part2_result << "\n";

    return 0;
}

// Count how many times beams split
int count_splits(const std::vector<std::string>& grid, int start_col) {
    int split_count = 0;

    std::unordered_set<int> active_positions;
    active_positions.insert(start_col);

    for (size_t row = 1; row < grid.size(); ++row) {
        const std::string& current_row = grid[row];
        std::unordered_set<int> next_positions;

        for (int col : active_positions) {
            char cell = current_row[col];

            if (cell == '^') {
                if (col > 0)
                    next_positions.insert(col - 1);
                if (col + 1 < current_row.size())
                    next_positions.insert(col + 1);

                ++split_count;
            } 
            else if (cell == '.') {
                next_positions.insert(col);
            }
        }

        active_positions = std::move(next_positions);
    }

    return split_count;
}

// Part 2: Count total timelines after quantum splitting
long long count_timelines(const std::vector<std::string>& grid, int start_col) {
    std::unordered_map<int, long long> active_timelines;
    active_timelines[start_col] = 1;

    for (size_t row = 1; row < grid.size(); ++row) {
        const std::string& current_row = grid[row];
        std::unordered_map<int, long long> next_timelines;

        for (auto [col, count] : active_timelines) {
            char cell = current_row[col];

            if (cell == '^') {
                if (col > 0)
                    next_timelines[col - 1] += count;
                if (col + 1 < current_row.size())
                    next_timelines[col + 1] += count;
            }
            else if (cell == '.') {
                next_timelines[col] += count;
            }
        }

        active_timelines = std::move(next_timelines);
    }

    long long total = 0;
    for (auto [col, count] : active_timelines)
        total += count;

    return total;
}