#include <vector>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <cstdint>

struct Point {
    int x, y, z;
};

long long dist2(const Point& p1, const Point& p2) {
    long long dx = (long long)p1.x - p2.x;
    long long dy = (long long)p1.y - p2.y;
    long long dz = (long long)p1.z - p2.z;
    return dx*dx + dy*dy + dz*dz;
}

// Disjoint Set Union
struct DSU {
    std::vector<int> parent;
    std::vector<int> size;

    DSU(int n) : parent(n), size(n, 1) {
        for (int i = 0; i < n; i++) parent[i] = i;
    }

    int find(int x) {
        if (parent[x] != x) parent[x] = find(parent[x]);
        return parent[x];
    }

    bool unite(int a, int b) {
        a = find(a);
        b = find(b);
        if (a == b) return false;
        if (size[a] < size[b]) std::swap(a, b);
        parent[b] = a;
        size[a] += size[b];
        return true;
    }
};

struct Edge {
    long long d2;
    int a, b;
};

int main() {
    std::ifstream file("input.txt");
    if (!file.is_open()) {
        std::cerr << "Could not open input.txt\n";
        return 1;
    }

    std::vector<Point> points;
    int x, y, z;
    char comma;
    while (file >> x >> comma >> y >> comma >> z) {
        points.push_back({x, y, z});
    }
    file.close();

    // Preprocessing
    int n = points.size();
    std::vector<Edge> edges;
    edges.reserve(n * (n-1) / 2);
    for (int i = 0; i < n; i++) {
        for (int j = i+1; j < n; j++) {
            edges.push_back({dist2(points[i], points[j]), i, j});
        }
    }

    std::sort(edges.begin(), edges.end(), [](auto &a, auto &b){
        return a.d2 < b.d2;
    });

    // Part 1
    int K = 1000;
    DSU dsu1(K);
    for (int i = 0; i < K; i++) {
        dsu1.unite(edges[i].a, edges[i].b);
    }

    std::vector<int> comp_size(n, 0);
    for (int i = 0; i < n; i++) {
        int r = dsu1.find(i);
        comp_size[r]++;
    }

    std::vector<int> sizes;
    for (int s : comp_size)
        if (s > 0) sizes.push_back(s);
    std::sort(sizes.begin(), sizes.end(), std::greater<int>());

    long long part1 = 1LL * sizes[0] * sizes[1] * sizes[2];
    std::cout << "Part 1: " << part1 << "\n";

    // Part 2
    DSU dsu2(n);
    int components = n;
    int lastA = -1;
    int lastB = -1;

    for (auto &e : edges) {
        if (dsu2.unite(e.a, e.b)) {
            components--;
            lastA = e.a;
            lastB = e.b;
            if (components == 1) break;
        }
    }

    long long part2 = 1LL * points[lastA].x * points[lastB].x;
    std::cout << "Part 2: " << part2 << "\n";

    return 0;
}
