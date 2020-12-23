#include <fstream>
#include <map>
#include <iostream>


std::ifstream _open_input(const int day, const std::string filename) {
    const std::string input_file = "./day" + std::to_string(day) + "/" + filename;
    std::ifstream fs = std::ifstream(input_file);
    if (!fs) {
        throw std::runtime_error("Could not open file " + filename);
    }

    if (fs.peek() == std::ifstream::traits_type::eof()) {
        throw std::runtime_error("File at " + filename + " is empty!");
    }

    return fs;
}

std::ifstream open_input(const int day) {
    return _open_input(day, "input");
}

std::ifstream open_debug(const int day) {
    return _open_input(day, "debug");
}


void print_header(const std::string& day) {
    std::cout << "======= Advent of Code Day " << day << " =======" << std::endl;
}


void print_map(std::map<std::string, std::string>& map) {
    for(const auto& elem : map)
    {
        std::cout << elem.first << ": " << elem.second << " ";
    }
    std::cout << std::endl;
}
