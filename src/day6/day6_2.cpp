#include "shared.h"
#include <set>
#include <vector>
#include <memory>
#include <iterator>

using namespace std;

size_t count_agreed_entries(vector<set<char>>& batch) {
    set<char> accumulator;

    if (!batch.empty()) {
        accumulator = set<char>(batch.back());
        batch.pop_back();
    }

    for (auto& entry : batch) {
        set<char> new_accumulator;
        set_intersection(entry.begin(), entry.end(), accumulator.begin(), accumulator.end(),
                         std::inserter(new_accumulator, new_accumulator.begin()));
        accumulator = new_accumulator;
    }

    batch.clear();
    return accumulator.size();
}

int main() {
    print_header("6.1");
    auto input_file_stream = open_input(6);

    string line;
    vector<set<char>> batch;
    size_t sum_of_agreements = 0;
    while (getline(input_file_stream, line)) {
        if (line.empty()) {
            sum_of_agreements += count_agreed_entries(batch);
        } else {
            set<char> current_entry;
            for (const auto c : line) {
                current_entry.insert(c);
            }
            batch.push_back(current_entry);
        }
    }

    sum_of_agreements += count_agreed_entries(batch);

    std::cout << "Duplicate entries: " << sum_of_agreements << std::endl;
}