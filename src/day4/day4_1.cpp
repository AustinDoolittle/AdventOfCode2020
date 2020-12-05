#include <iostream>
#include <sstream>
#include <unordered_set>
#include <map>
#include "shared.h"

bool map_contains_all_keys(const std::map<std::string, std::string>& map, const std::unordered_set<std::string>& keys) {
    size_t contains_count = 0;
    for (const auto& it : map) {
        contains_count += keys.count(it.first);
    }

    std::cout << contains_count << std::endl;
    return contains_count == keys.size();
}

std::tuple<std::string, std::string> split_string_on_delimiter(const std::string& input_string, const char delimiter) {
    const size_t delimiter_idx = input_string.find(delimiter);
    const std::string key = input_string.substr(0, delimiter_idx);
    const std::string value = input_string.substr(delimiter_idx + 1);

    return std::make_tuple(key, value);
}

void print_map(std::map<std::string, std::string>& map) {
    for(const auto& elem : map)
    {
        std::cout << elem.first << ": " << elem.second << " ";
    }
    std::cout << std::endl;
}

int main() {
    const char delimiter = ':';

    print_header("4.1");
    auto input_file_stream = open_input(4);

    const std::unordered_set<std::string> required_values {
        "byr",
        "iyr",
        "eyr",
        "hgt",
        "hcl",
        "ecl",
        "pid"
    };

    size_t valid_passport_count = 0;
    std::string line;
    std::map<std::string, std::string> current_passport;
    while (std::getline(input_file_stream, line)) {
        std::cout << line << std::endl;
        if (line.empty()) {
            print_map(current_passport);
            if (map_contains_all_keys(current_passport, required_values)) {
                std::cout << "Good!";
                valid_passport_count++;
            } else {
                std::cout << "Bad!";
            }

            std::cout << std::endl << std::endl;

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

    std::cout << "Found " << valid_passport_count << " valid passports" << std::endl;
}
