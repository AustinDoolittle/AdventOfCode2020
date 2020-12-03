#include <iostream>
#include <fstream>

int main() {
    const std::string input_file = "./day2/input.1";

    std::cout << "===== Advent of Code Day 2.2 =====" << std::endl;

    std::cout << "Reading file from " << input_file << std::endl;


    std::ifstream input_file_stream(input_file);

    //  sample input
    //  9-10 b: bbktbbbxhfbpb
    //  2-10 x: xxnxxxwxxsx
    int first_index, second_index;
    char character, scrap;
    std::string password;

    int valid_count = 0;
    while (input_file_stream >> first_index >> scrap >> second_index >> character >> scrap >> password) {
        first_index--;
        second_index--;

        if ((password[first_index] == character) != (password[second_index] == character)) {
            valid_count++;
        }
    }

    std::cout << "Found " << valid_count << " valid passwords" << std::endl;

    return 0;
}


