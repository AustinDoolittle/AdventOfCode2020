
#include <utility>
#include <vector>
#include <sstream>
#include "shared.h"

using namespace std;

enum Status {
    OCCUPIED,
    EMPTY,
    FLOOR
};


Status char_to_status(const char c) {
    switch(c) {
        case 'L':
            return Status::EMPTY;
        case '.':
            return Status::FLOOR;
        case '#':
            return Status::OCCUPIED;
        default:
            throw std::runtime_error("Invalid status");
    }
}

char status_to_char(const Status s) {
    switch(s) {
        case Status::EMPTY:
            return 'L';
        case Status::OCCUPIED:
            return '#';
        case Status::FLOOR:
            return '.';
    }
}

class SeatingMap {
public:
    explicit SeatingMap(std::vector<std::vector<Status>> statuses) : statuses(std::move(statuses)) { }

    bool step() {
        /** Returns true if board was modified, false otherwise **/

        bool something_changed = false;
        std::vector<std::vector<Status>> new_statuses;
        new_statuses.reserve(statuses.size());
        for (size_t row = 0; row < statuses.size(); row++) {
            std::vector<Status> new_row;
            new_row.reserve(statuses[row].size());
            for (size_t col = 0; col < statuses[row].size(); col++) {
                const auto old_status = statuses[row][col];
                const auto new_status = calculate_new_status(row, col);

                if (new_status != old_status) {
                    something_changed = true;
                }

                new_row.push_back(new_status);
            }

            new_statuses.push_back(new_row);
        }

        statuses = new_statuses;

        return something_changed;
    }

    size_t count_positions_with_status(const Status s) {
        size_t count = 0;
        for (const auto& row : statuses) {
            for (const auto& status : row) {
                if (status == s) {
                    count += 1;
                }
            }
        }
        return count;
    }

    std::string to_string() {
        std::stringstream ss;
        for (const auto& row : statuses) {
            for (const auto& status : row) {
                ss << status_to_char(status);
            }
            ss << std::endl;
        }
        return ss.str();
    }

private:
    std::vector<std::vector<Status>> statuses;
    static const std::vector<std::tuple<int, int>> NEIGHBOR_DELTAS;

    Status calculate_new_status(const size_t row, const size_t col) {
        const auto cell_status = statuses[row][col];

        switch(cell_status) {
            case Status::OCCUPIED:
                if (count_adjacent_occupied_seats(row, col) >= 4) {
                    return Status::EMPTY;
                }
                break;
            case Status::EMPTY:
                if (count_adjacent_occupied_seats(row, col) == 0) {
                    return Status::OCCUPIED;
                }
                break;
            default:
                break;
        }

        return cell_status;
    }

    size_t count_adjacent_occupied_seats(const size_t row, const size_t col) {
        return count_adjacent_seats_with_status(row, col, Status::OCCUPIED);
    }

    size_t count_adjacent_seats_with_status(const size_t row, const size_t col, const Status status) {
        int row_d, col_d;
        size_t sum = 0;
        for (auto position : NEIGHBOR_DELTAS) {
            std::tie(row_d, col_d) = position;
            const size_t new_row = row + row_d;
            if (!bounds_check_row(new_row)) {
                continue;
            }

            const size_t new_col = col + col_d;
            if (!bounds_check_col(new_col)) {
                continue;
            }

            const auto neighbor_status = statuses[new_row][new_col];
            if (neighbor_status == status) {
                sum += 1;
            }
        }

        return sum;
    }

    bool bounds_check_row(const size_t row) {return row >= 0 && row < statuses.size();}

    // Assumes statuses has at least one row
    bool bounds_check_col(const size_t col) {return col >= 0 && col < statuses[0].size();}
};

const std::vector<std::tuple<int, int>> SeatingMap::NEIGHBOR_DELTAS {
    {-1, -1},
    {-1, 0},
    {-1, 1},
    {0, -1},
    {0, 1},
    {1, -1},
    {1, 0},
    {1, 1},
};


int main() {
    print_header("11.1");

    auto input_file_stream = open_input(11);
//    auto input_file_stream = open_debug(11);

    std::string line;
    std::vector<std::vector<Status>> seating_statuses;
    while (input_file_stream >> line) {
        std::vector<Status> new_row;
        for (auto& position_status : line) {
            new_row.push_back(char_to_status(position_status));
        }

        seating_statuses.push_back(new_row);
    }

    SeatingMap seating_map(seating_statuses);

    size_t step_count = 0;
    while (seating_map.step()) {
        step_count += 1;
    }

    const auto occupied_count = seating_map.count_positions_with_status(Status::OCCUPIED);

    std::cout << "Number of steps: " << step_count << std::endl;
    std::cout << "Number of occupied seats: " << occupied_count << std::endl;
    return 0;
}