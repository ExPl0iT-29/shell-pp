#include <iostream>
#include <string>
#include <unistd.h>

int main() {
    std::string input;

    std::cout << "Current PID: " << getpid() << std::endl;

    while (true) {
        // Display prompt
        std::cout << "mysh> ";
        std::getline(std::cin, input);

        // Exit condition
        if (input == "exit" || input == "quit") {
            break;
        }

        // Echo input (temporary)
        if (!input.empty()) {
            std::cout << "Received: " << input << std::endl;
        }
    }

    std::cout << "Shell terminated." << std::endl;
    return 0;
}
