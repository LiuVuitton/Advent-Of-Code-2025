#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <unordered_map>
#include <string>
#include <stack>
#include <utility>

int main() {
    std::ifstream infile("input.txt");
    if (!infile.is_open()) {
        std::cerr << "Could not open file\n";
        return 1;
    }

    std::unordered_map<std::string, std::vector<std::string>> word_map;
    std::string line;

    while (std::getline(infile, line)) {
        std::istringstream iss(line);
        std::string key;
        if (std::getline(iss, key, ':')) { // split at the colon
            std::string rest;
            if (std::getline(iss, rest)) {
                std::istringstream words_stream(rest);
                std::string word;
                while (words_stream >> word) {
                    word_map[key].push_back(word);
                }
            }
        }
    }

    // Part 1
    std::stack<std::string> st;
    st.push("you");
    int count = 0;
    while (!st.empty()) {
        std::string curr = st.top(); st.pop();
        if (curr == "out") {
            ++count;
        }
        for (std::string next : word_map[curr]) {
            st.push(next);
        }
    }
    std::cout << "Part 1: " << count << "\n";

    // Part 2
    

    return 0;
}
