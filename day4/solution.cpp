#include <string>
#include <fstream>
#include <vector>
#include <iostream>

std::vector<std::pair<int,int>> DIRS = {
    {-1,-1}, {-1,0}, {-1,1},
    {0,-1},          {0,1},
    {1,-1},  {1,0},  {1,1}
};

bool accessible(int r, int c, const std::vector<std::vector<char>>& grid) {
    int m = grid.size();
    int n = grid[0].size();

    if (grid[r][c] != '@') 
        return false;

    int count = 0;
    for (auto [dy, dx] : DIRS) {
        int ny = r + dy;
        int nx = c + dx;
        if (0 <= ny && ny < m &&
            0 <= nx && nx < n)
        {
            if (grid[ny][nx] == '@')
                count++;
        }
    }
    return count < 4;
}

int count_paper_rolls(const std::vector<std::vector<char>>& grid) {
    int m = grid.size();
    int n = grid[0].size();

    int count = 0;
    for (int r = 0; r < m; ++r) {
        for (int c = 0; c < n; ++c) {
            if (accessible(r, c, grid))
                count++;
        }
    }
    return count;
}

int main() {
    std::ifstream f("input.txt");
    if (!f.is_open()) {
        std::cerr << "Error: could not open input.txt\n";
        return 1;
    }

    std::vector<std::vector<char>> grid;
    std::string line;

    while (std::getline(f, line)) {
        if (line.empty()) continue;
        grid.emplace_back(line.begin(), line.end());
    }

    int result = count_paper_rolls(grid);
    std::cout << "Accessible rolls: " << result << "\n";

    return 0;
}
