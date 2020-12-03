#include <iostream>
#include <fstream>
#include <vector>

int main() {
    const std::string input_file = "./day3/input";
    const char tree_char = '#';
    const size_t slope_x = 3;
    const size_t slope_y = 1;

    std::cout << "===== Advent of Code Day 3.1 =====" << std::endl;

    std::ifstream input_file_stream(input_file);

    std::vector<const std::vector<bool>> forest;

    std::string line;
    while(input_file_stream >> line) {
        std::vector<bool> new_row;
        new_row.reserve(line.size());

        for (const auto position : line) {
            new_row.push_back(position == tree_char);
        }

        forest.push_back(new_row);
    }

    if (forest.empty()) {
        throw std::runtime_error("Forest map cannot be empty");
    }

    size_t row_size = forest[0].size();

    size_t current_x = 0;
    size_t current_y = 0;
    size_t tree_count = 0;
    while (current_y < forest.size()) {
        if (forest[current_y][current_x]) {
            tree_count += 1;
        }
        current_x = (current_x + slope_x) % row_size;
        current_y += slope_y;
    }

    std::cout << "Tree count: " << tree_count << std::endl;
}