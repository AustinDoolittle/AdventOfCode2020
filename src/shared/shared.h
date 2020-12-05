#include <fstream>

std::ifstream open_input(int day) {
    const std::string input_file = "./day" + std::to_string(day) + "/input";
    return std::ifstream(input_file);
}

void print_header(const std::string& day) {
    std::cout << "======= Advent of Code Day " << day << " =======" << std::endl;
}
