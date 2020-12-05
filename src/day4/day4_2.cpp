#include <iostream>
#include <sstream>
#include <unordered_set>
#include <map>
#include "shared.h"

using namespace std;

const std::unordered_set<std::string> REQUIRED_VALUES {
        "byr",
        "iyr",
        "eyr",
        "hgt",
        "hcl",
        "ecl",
        "pid"
};

const std::unordered_set<std::string> VALID_EYE_COLORS {
        "amb",
        "blu",
        "brn",
        "gry",
        "grn",
        "hzl",
        "oth"
};

class InvalidEntryException : exception {};

void validate_entry(const string& key, const string& value) {
    if (key == "byr") {
        const auto year = stoi(value);
        if (year < 1920 || year > 2002) {
            throw InvalidEntryException();
        }
    } else if (key == "iyr") {
        const auto year = stoi(value);
        if (year < 2010 || year > 2020) {
            throw InvalidEntryException();
        }
    } else if (key == "eyr") {
        const auto year = stoi(value);
        if (year < 2020 || year > 2030) {
            throw InvalidEntryException();
        }
    } else if (key == "hgt") {
        stringstream parse_helper(value);
        int count;
        string units;
        parse_helper >> count >> units;
        if (units == "cm") {
            if (count < 150 || count > 193) {
                throw InvalidEntryException();
            }
        } else if (units == "in") {
            if (count < 59 || count > 76) {
                throw InvalidEntryException();
            }
        } else {
            throw InvalidEntryException();
        }
    } else if (key == "hcl") {
        stringstream parse_helper(value);
        char garbage;
        size_t cast;
        string hex_string;
        parse_helper >> garbage >> hex_string;

        if (hex_string.length() != 6) {
            throw InvalidEntryException();
        }

        try {
            cast = std::stoi(hex_string, 0, 16);
        } catch (invalid_argument& e) {
            throw InvalidEntryException();
        }
    } else if (key == "ecl") {
        if (VALID_EYE_COLORS.count(value) == 0) {
            throw InvalidEntryException();
        }
    } else if (key == "pid") {
        int pin;

        try {
            pin = stoi(value);
        } catch (invalid_argument&) {
            throw InvalidEntryException();
        }

        if (value.size() != 9) {
            throw InvalidEntryException();
        }
    }
}


bool is_map_valid(const map<string, string> in_map) {
    size_t match_count = 0;
    for (const auto& it : in_map) {
        if (REQUIRED_VALUES.count(it.first)) {
            match_count++;
        }

        try {
            validate_entry(it.first, it.second);
        } catch (InvalidEntryException&) {
            return false;
        }
    }

    return match_count >= REQUIRED_VALUES.size();
}


std::tuple<std::string, std::string> split_string_on_delimiter(const std::string& input_string, const char delimiter) {
    const size_t delimiter_idx = input_string.find(delimiter);
    const std::string key = input_string.substr(0, delimiter_idx);
    const std::string value = input_string.substr(delimiter_idx + 1);

    return std::make_tuple(key, value);
}

int main() {
    const char delimiter = ':';

    print_header("4.2");
    auto input_file_stream = open_input(4);

    size_t valid_passport_count = 0;
    std::string line;
    std::map<std::string, std::string> current_passport;
    while (std::getline(input_file_stream, line)) {
        if (line.empty()) {
            if (is_map_valid(current_passport)) {
                valid_passport_count++;
            }

            current_passport.clear();
        } else {
            std::stringstream ss(line);
            std::string passport_entry;
            while (ss >> passport_entry) {
                const auto split_string = split_string_on_delimiter(passport_entry, delimiter);
                current_passport[std::get<0>(split_string)] = std::get<1>(split_string);
            }
        }
    }

    if (is_map_valid(current_passport)) {
        valid_passport_count++;
    }


    std::cout << "Found " << valid_passport_count << " valid passports" << std::endl;
}
