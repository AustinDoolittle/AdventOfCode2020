#include <vector>
#include <unordered_set>
#include "shared.h"

using namespace std;

enum InstructionEnum {
    NOP,
    ACC,
    JMP
};

struct Instruction {
    const InstructionEnum instruction;
    const int value;
};



int main() {
    print_header("8.1");

    auto input_file_stream = open_input(8);
//    auto input_file_stream = open_debug(8);

    vector<Instruction> tape;
    string instruction_str;
    int value;
    InstructionEnum instruction_type;
    while (input_file_stream >> instruction_str >> value) {
        if (instruction_str == "acc") {
            instruction_type = InstructionEnum::ACC;
        } else if (instruction_str == "jmp") {
            instruction_type = InstructionEnum::JMP;
        } else if (instruction_str == "nop") {
            instruction_type = InstructionEnum::NOP;
        } else {
            throw runtime_error("invalid instruction " + instruction_str);
        }

        tape.push_back({instruction_type, value});
    }

    size_t instruction_ptr = 0;
    int accumulator = 0;
    bool cycle_detected = false;
    unordered_set<int> visited_instructions;
    while(!cycle_detected) {
        if (visited_instructions.count(instruction_ptr)) {
            cycle_detected = true;
            continue;
        }

        visited_instructions.insert(instruction_ptr);
        const auto instruction = tape[instruction_ptr];
        switch (instruction.instruction) {
            case InstructionEnum::JMP:
                instruction_ptr += instruction.value;
                break;
            case InstructionEnum::ACC:
                accumulator += instruction.value;
            case InstructionEnum::NOP:
                instruction_ptr++;
                break;
        }
    }

    std::cout << "Accumulator: " << accumulator << std::endl;
}