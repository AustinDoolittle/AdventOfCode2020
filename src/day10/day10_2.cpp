#include <algorithm>
#include <vector>
#include "shared.h"

using namespace std;

size_t enumerate_configurations(vector<size_t>::iterator begin, vector<size_t>::iterator end, const size_t device_joltage, map<size_t, size_t>& cache) {
    size_t sum = 0;
    auto next_iter = next(begin);
    while (next_iter != end) {
        if ((*next_iter - *begin) > 3) {
            break;
        }

        if (cache.count(*next_iter) == 0) {
            cache[*next_iter] = enumerate_configurations(next_iter, end, device_joltage, cache);
        }

        sum += cache[*next_iter];
        next_iter = next(next_iter);
    }

    if (*begin >= (device_joltage - 3)) {
        sum += 1;
    }

    return sum;
}

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

    const size_t device_joltage = value_list.back() + 3;
    map<size_t, size_t> cache;
    const size_t num_configs = enumerate_configurations(value_list.begin(), value_list.end(), device_joltage, cache);
    std::cout << "num possible configs " << num_configs;
}