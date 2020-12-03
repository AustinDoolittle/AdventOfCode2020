#include <iostream>
#include <fstream>

int main() {
    const std::string input_file = "./day2/input.1";

    std::cout << "===== Advent of Code Day 2.1 =====" << std::endl;

    std::cout << "Reading file from " << input_file << std::endl;


    std::ifstream input_file_stream(input_file);

    //  sample input
    //  9-10 b: bbktbbbxhfbpb
    //  2-10 x: xxnxxxwxxsx
    int lower_limit, upper_limit;
    char character, scrap;
    std::string password;

    int valid_count = 0;
    while (input_file_stream >> lower_limit >> scrap >> upper_limit >> character >> scrap >> password) {
        int curr_count = 0;
        for (const char password_char : password) {
            if (password_char == character) {
                curr_count++;
            }
        }

        if (curr_count >= lower_limit && curr_count <= upper_limit) {
            valid_count++;
        }
    }

    std::cout << "Found " << valid_count << " valid passwords" << std::endl;

    return 0;
}


