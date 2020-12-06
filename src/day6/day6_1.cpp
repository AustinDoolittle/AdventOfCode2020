#include "shared.h"
#include <set>
#include <vector>

using namespace std;

int main() {
    print_header("6.1");
    auto input_file_stream = open_input(6);

    string line;
    set<char> found_chars;
    size_t sum_of_observed = 0;
    while (getline(input_file_stream, line)) {
        if (line.empty()) {

            sum_of_observed += found_chars.size();
            found_chars.clear();
        } else {
            for (const auto c : line) {
                found_chars.insert(c);
            }
        }
    }

    sum_of_observed += found_chars.size();

    std::cout << "Duplicate entries: " << sum_of_observed << std::endl;
}