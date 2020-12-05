#include <fstream>

std::ifstream open_input(int day) {
    const std::string input_file = "./day" + std::to_string(day) + "/input";
    std::ifstream fs = std::ifstream(input_file);
    if (!fs) {
        throw std::runtime_error("Could not open file");
    }
    return fs;
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
