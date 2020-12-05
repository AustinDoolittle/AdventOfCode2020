#include <iostream>
#include <algorithm>
#include <fstream>
#include <vector>
#include <iterator>
#include "shared.h"

int main() {
    const int target_val = 2020;

    print_header("1.1");
    auto input_file_stream = open_input(1);

    int a;
    std::vector<int> values;
    while (input_file_stream >> a) {
        values.push_back(a);
    }

    std::sort(values.begin(), values.end());

    auto begin_iter = values.begin();
    auto end_iter = values.rbegin();
    auto current_val = *begin_iter + *end_iter;
    while (current_val != target_val && begin_iter != values.end() && end_iter != values.rend()) {
        if (current_val < target_val) {
            begin_iter++;
        } else {
            end_iter++;
        }
        current_val = *begin_iter + *end_iter;
    }

    if (current_val != target_val) {
        std::cout << "No valid pair in the input file" << std::endl;
        std::exit(1);
    }

    std::cout << "Found a valid pair!" << std::endl;
    std::cout << *begin_iter << " + " << *end_iter << " = " << current_val << std::endl;
    std::cout << *begin_iter << " + " << *end_iter << " = " << *begin_iter * *end_iter << std::endl;
}
