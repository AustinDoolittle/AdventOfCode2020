#include <iostream>
#include <fstream>
#include <vector>

size_t calc_num_trees(const std::vector<const std::vector<bool>>& forest, const size_t slope_x, const size_t slope_y) {
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

    return tree_count;
}

int main() {
    const std::string input_file = "./day3/input";
    const char tree_char = '#';
    const std::vector<size_t> x_slopes = {1, 3, 5, 7, 1};
    const std::vector<size_t> y_slopes = {1, 1, 1, 1, 2};

    std::cout << "===== Advent of Code Day 3.2 =====" << std::endl;

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

    size_t tree_count_prod = 1;
    for (size_t i = 0; i < x_slopes.size(); i++) {
        const auto curr_x_slope = x_slopes[i];
        const auto curr_y_slope = y_slopes[i];

        const size_t tree_count = calc_num_trees(forest, curr_x_slope, curr_y_slope);
        std::cout << "Slope X: " << curr_x_slope << ", Slope Y: " << curr_y_slope;
        std::cout << ", Tree count: " << tree_count << std::endl;

        tree_count_prod *= tree_count;
    }

    std::cout << "Tree count product: " << tree_count_prod << std::endl;
}