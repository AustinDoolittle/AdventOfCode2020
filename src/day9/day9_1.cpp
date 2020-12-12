#include <vector>
#include <deque>
#include <algorithm>
#include "shared.h"

using namespace std;

class SlidingWindow {
public:
    explicit SlidingWindow(const size_t window_size) : window_size(window_size) { }

    bool is_window_full() {
        return internal_window.size() == window_size;
    }

    bool is_valid_next_value(const size_t next_value) {
        if (!is_window_full()) {
            throw runtime_error("window should be full before you start checking for validity");
        }

        std::vector<size_t> sorted_list(internal_window.begin(), internal_window.end());
        sort(sorted_list.begin(), sorted_list.end());

        auto front_iter = sorted_list.begin();
        auto back_iter = sorted_list.rbegin();
        while (*front_iter < *back_iter) {
            const size_t curr_val = (*front_iter) + (*back_iter);
            if (curr_val == next_value) {
                return true;
            } else if (next_value > curr_val) {
                front_iter++;
            } else {
                back_iter++;
            }
        }

        return false;
    }

    void add_value(const size_t value) {
        if (internal_window.size() == window_size) {
            internal_window.pop_back();
        }
        internal_window.push_front(value);
    }


private:
    const size_t window_size;
    std::deque<const size_t> internal_window;

};

int main() {
    print_header("9.1");

    auto input_file_stream = open_input(9);
    const size_t window_size = 25;

//    auto input_file_stream = open_debug(9);
//    const size_t window_size = 5;

    SlidingWindow window(window_size);
    size_t value;
    while(input_file_stream >> value) {
        if (window.is_window_full() && !window.is_valid_next_value(value)) {
            // the window is full and this
            break;
        }

        window.add_value(value);
    }

    cout << "Invalid value: " << value << std::endl;
}
