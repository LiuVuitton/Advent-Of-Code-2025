#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <cmath>


struct Point {
    int x;
    int y;
    Point(int x, int y) : x(x), y(y) {}
};

long long compute_area(const Point& p1, const Point& p2) {
    return 1ll * (std::abs(p1.x - p2.x) + 1) * (std::abs(p1.y - p2.y) + 1);
}

int main() {
    std::ifstream file("input.txt");
    if (!file.is_open()) {
        std::cerr << "Could not open input.txt\n";
        return 1;
    }

    int x, y;
    char comma;
    std::vector<Point> tiles;
    while (file >> x >> comma >> y) {
        tiles.push_back({x, y});
    }

    int n = tiles.size();
    long long area = 0;
    long long max_area = 0;
    for (Point p1 : tiles) {
        for (Point p2 : tiles) {
            max_area = std::max(max_area, compute_area(p1, p2));
        }
    }
    std::cout << "Part 1: " << max_area << "\n";

    return 0;
}