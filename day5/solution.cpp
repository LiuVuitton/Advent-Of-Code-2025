#include <vector>
#include <iostream>
#include <fstream>
#include <algorithm>

// Check if a value falls inside any of the given sorted & merged ranges
bool is_in_range(const std::vector<std::pair<long long, long long>>& ranges,
                 long long value);
// Merge overlapping ranges into non-overlapping intervals
std::vector<std::pair<long long, long long>>
merge_ranges(std::vector<std::pair<long long, long long>>& ranges);
// Count how many values fall within the merged ranges
long long count_values_in_ranges(
        const std::vector<std::pair<long long, long long>>& merged_ranges,
        const std::vector<long long>& values);
// Count total size of all merged ranges
long long count_total_range_size;

int main() {
    std::ifstream f("input.txt");

    if (!f.is_open()) {
        std::cerr << "Error: could not open input.txt\n";
        return 1;
    }

    std::vector<std::pair<long long, long long>> raw_ranges;
    std::vector<long long> ingredient_ids;

    std::string line;
    while (std::getline(f, line)) {
        if (line.empty()) continue;

        size_t dash_pos = line.find('-');
        if (dash_pos != std::string::npos) {
            long long start = std::stoll(line.substr(0, dash_pos));
            long long end   = std::stoll(line.substr(dash_pos + 1));
            raw_ranges.emplace_back(start, end);
        } else {
            ingredient_ids.push_back(std::stoll(line));
        }
    }
    f.close();
    
    // Merge all fresh ID ranges
    auto merged_ranges = merge_ranges(raw_ranges);

    // Part 1
    long long part1 = count_values_in_ranges(merged_ranges, ingredient_ids);
    std::cout << "Part 1: " << part1 << "\n";

    // Part 2
    long long part2 = count_total_range_size(merged_ranges);
    std::cout << "Part 2: " << part2 << "\n";

    return 0;
}

bool is_in_range(const std::vector<std::pair<long long, long long>>& ranges,
                 long long value) {
    int lo = 0;
    int hi = ranges.size();

    while (lo < hi) {
        int mid = lo + (hi - lo) / 2;
        long long start = ranges[mid].first;
        long long end   = ranges[mid].second;

        if (start <= value && value <= end) {
            return true;
        }
        if (value > end) {
            lo = mid + 1;
        } else {
            hi = mid;
        }
    }
    return false;
}

std::vector<std::pair<long long, long long>>
merge_ranges(std::vector<std::pair<long long, long long>>& ranges) {
    std::sort(ranges.begin(), ranges.end());

    std::vector<std::pair<long long, long long>> merged;
    long long current_start = ranges[0].first;
    long long current_end   = ranges[0].second;

    for (auto [start, end] : ranges) {
        if (start <= current_end + 1) {
            current_end = std::max(current_end, end);
        } else {
            merged.emplace_back(current_start, current_end);
            current_start = start;
            current_end   = end;
        }
    }

    merged.emplace_back(current_start, current_end); // final flush
    return merged;
}

long long count_values_in_ranges(
        const std::vector<std::pair<long long, long long>>& merged_ranges,
        const std::vector<long long>& values) {
    long long count = 0;
    for (long long v : values) {
        if (is_in_range(merged_ranges, v)) {
            ++count;
        }
    }
    return count;
}

long long count_total_range_size(
        const std::vector<std::pair<long long, long long>>& merged_ranges) {
    long long total = 0;
    for (auto [start, end] : merged_ranges) {
        total += (end - start + 1);
    }
    return total;
}