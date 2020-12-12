#include <vector>
#include <deque>
#include <algorithm>
#include "shared.h"

using namespace std;

class SlidingWindow {
public:

    size_t get_sum_of_window() {
        size_t sum = 0;
        for (const auto val : internal_window) {
            sum += val;
        }
        return sum;
    }

    void pop_value() {
        internal_window.pop_back();
    }

    void add_value(const size_t value) {
        internal_window.push_front(value);
    }

    size_t get_smallest_plus_largest() {
        size_t min_value = SIZE_T_MAX;
        size_t max_value = 0;
        for (auto val : internal_window) {
            if (val < min_value) {
                min_value = val;
            }

            if (val > max_value) {
                max_value = val;
            }
        }
        return min_value + max_value;
    }


private:
    std::deque<const size_t> internal_window;

};

int main() {
    print_header("9.2");

    auto input_file_stream = open_input(9);
    const size_t target_value = 1930745883;

//    auto input_file_stream = open_debug(9);
//    const size_t target_value = 127;

    SlidingWindow window;
    size_t value;
    auto window_sum = window.get_sum_of_window();
    while (window_sum != target_value) {
        if (window_sum < target_value) {
            input_file_stream >> value;
            window.add_value(value);
        } else {
            window.pop_value();
        }

        window_sum = window.get_sum_of_window();
    }

    cout << "Min + Max value: " << window.get_smallest_plus_largest() << std::endl;
}
