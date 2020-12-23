#include <stdlib.h>
#include <vector>
#include "shared.h"

enum AbsoluteDirection {
    NORTH = 0,
    EAST = 1,
    SOUTH = 2,
    WEST = 3
};

static const std::map<char, AbsoluteDirection> CHAR_TO_ABSOLUTE_DIRECTION {
    {'N', NORTH},
    {'E', EAST},
    {'S', SOUTH},
    {'W', WEST}
};

enum RelativeDirection {
    LEFT = 0,
    RIGHT = 1,
    FORWARD = 2
};

static const std::map<char, RelativeDirection> CHAR_TO_RELATIVE_DIRECTION {
    {'L', LEFT},
    {'R', RIGHT},
    {'F', FORWARD}
};


struct Instruction {
    char direction;
    int magnitude;
};

class Ship {
public:
    void move_absolute(AbsoluteDirection direction, int magnitude) {
        switch(direction) {
            case NORTH:
                waypoint_offset_longitude += magnitude;
                break;
            case EAST:
                waypoint_offset_latitude += magnitude;
                break;
            case SOUTH:
                waypoint_offset_longitude -= magnitude;
                break;
            case WEST:
                waypoint_offset_latitude -= magnitude;
                break;
        }
    }

    void move_relative(RelativeDirection direction, int magnitude) {
        switch (direction) {
            case LEFT:
            case RIGHT:
                rotate_waypoint(direction, magnitude);
                break;
            case FORWARD:
                move_to_waypoint(magnitude);
                break;
        }
    }

    int get_manhattan_distance_from_origin() const {
        return std::abs(latitude) + std::abs(longitude);
    }

private:
    static const int NUM_DIRECTIONS = 4;
    int latitude = 0;  // x-axis
    int longitude = 0;  // y-axis
    int waypoint_offset_latitude = 10;
    int waypoint_offset_longitude = 1;

    void move_to_waypoint(int repetitions) {
        for (auto i = 0; i < repetitions; i++) {
            latitude += waypoint_offset_latitude;
            longitude += waypoint_offset_longitude;
        }
    }

    void rotate_waypoint(RelativeDirection direction, int magnitude) {
        int num_rotations = (magnitude / 90) % NUM_DIRECTIONS;
        if (direction == LEFT) {
            num_rotations = NUM_DIRECTIONS - num_rotations;
        }

        const auto prev_lat = waypoint_offset_latitude;
        const auto prev_long = waypoint_offset_longitude;
        if (num_rotations == 1) {
            waypoint_offset_latitude = prev_long;
            waypoint_offset_longitude = -prev_lat;
        } else if (num_rotations == 2) {
            waypoint_offset_latitude = -prev_lat;
            waypoint_offset_longitude = -prev_long;
        } else if (num_rotations == 3) {
            waypoint_offset_latitude = -prev_long;
            waypoint_offset_longitude = prev_lat;
        } else {
            throw std::runtime_error("Invalid rotation");
        }
    }
};

int main() {
    print_header("12.1");

    auto input_file_stream = open_input(12);
//    auto input_file_stream = open_debug(12);

    char instruction_char;
    int magnitude;
    Ship ship;
    while (input_file_stream >> instruction_char >> magnitude) {
        if (CHAR_TO_ABSOLUTE_DIRECTION.count(instruction_char) != 0) {
            const auto direction = CHAR_TO_ABSOLUTE_DIRECTION.at(instruction_char);
            ship.move_absolute(direction, magnitude);
        } else if (CHAR_TO_RELATIVE_DIRECTION.count(instruction_char) != 0) {
            const auto direction = CHAR_TO_RELATIVE_DIRECTION.at(instruction_char);
            ship.move_relative(direction, magnitude);
        } else {
            throw std::runtime_error("Something went horribly wrong");
        }
    }

    std::cout << "Manhattan Distance: " << ship.get_manhattan_distance_from_origin() << std::endl;

    return 0;
}