#include "Parser.h"
#include <iostream>
#include <string>

int main() {
    std::string input;
    while (true) {
        std::cout << "mysh> ";
        std::getline(std::cin, input);

        if (input == "exit" || input == "quit") break;
        if (input.empty()) continue;

        try {
            auto commands = Parser::parse(input);

            // Print parsed commands (for testing)
            for (size_t i = 0; i < commands.size(); i++) {
                std::cout << "Command " << (i + 1) << ":\n";
                std::cout << "  Arguments: ";
                for (const auto& arg : commands[i].args) {
                    std::cout << "[" << arg << "] ";
                }
                std::cout << "\n";
            }
        }
        catch (const std::exception& e) {
            std::cerr << "Error: " << e.what() << "\n";
        }
    }
    return 0;
}