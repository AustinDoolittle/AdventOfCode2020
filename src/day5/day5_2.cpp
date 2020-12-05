#include <vector>
#include "shared.h"

using namespace std;

size_t do_binary_search(const std::vector<bool>& instructions, const size_t set_size) {
    // true means take higher section, false means lower
    size_t lower_bound = 0, upper_bound = set_size - 1;

    for (const auto instruction : instructions) {
        const size_t range = upper_bound - lower_bound;
        const size_t delta = range / 2 + 1;
        if (instruction) {
            lower_bound += delta;
        } else {
            upper_bound -= delta;
        }
    }

    return lower_bound;
}

std::vector<bool> parse_instruction_string(const string& instruction_string, const char false_char, const char true_char) {
    vector<bool> converted_instructions;
    for (auto instruction : instruction_string) {
        if (instruction == true_char) {
            converted_instructions.push_back(true);
        } else if (instruction == false_char) {
            converted_instructions.push_back(false);
        } else {
            throw runtime_error("Invalid instruction " + std::to_string(instruction));
        }
    }

    return converted_instructions;
}

const size_t ROW_SIZE = 128;
const size_t COLUMN_SIZE = 8;

int main() {
    print_header("5.1");
    auto input_file_stream = open_input(5);

    std::string line;
    std::vector<size_t> seat_ids;
    while (input_file_stream >> line) {
        const string row_string = line.substr(0, 7);
        const string col_string = line.substr(7);

        const auto row_instructions = parse_instruction_string(row_string, 'F', 'B');
        const auto col_instructions = parse_instruction_string(col_string, 'L', 'R');

        const size_t row = do_binary_search(row_instructions, ROW_SIZE);
        const size_t col = do_binary_search(col_instructions, COLUMN_SIZE);

        const size_t current_seat_id = row * 8 + col;
        seat_ids.push_back(current_seat_id);
    }

    std::sort(seat_ids.begin(), seat_ids.end());

    size_t prev_value = *seat_ids.begin() - 1;
    size_t your_seat_id = 0;
    for (auto seat_id : seat_ids) {
        if (seat_id - prev_value != 1) {
            your_seat_id = prev_value + 1;
            break;
        }

        prev_value = seat_id;
    }

    std::cout << "Your seat id: " << your_seat_id << std::endl;

}
