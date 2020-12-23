#include <algorithm>
#include <vector>
#include "shared.h"

using namespace std;

int main() {
    print_header("10.1");

    auto input_file_stream = open_input(10);
//    auto input_file_stream = open_debug(10);

    size_t value;
    vector<size_t> value_list;
    value_list.push_back(0);
    while(input_file_stream >> value) {
        value_list.push_back(value);
    }

    sort(value_list.begin(), value_list.end());
    map<const size_t, size_t> delta_counts;
    for (size_t i = 1; i < value_list.size(); i++) {
        auto delta = value_list[i] - value_list[i-1];
        delta_counts[delta]++;
    }
    delta_counts[3]++;

    const size_t arbitrary_result = delta_counts[1] * delta_counts[3];
    std::cout << "result: " << arbitrary_result << std::endl;
}