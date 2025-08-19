#pragma once

#include <vector>
#include <string>

class Parser {
public:
    struct ParsedCommand {
        std::vector<std::string> args;
        bool background = false;  // For future '&' operator
        std::string output_file;  // For future '>' operator
    };

    static std::vector<ParsedCommand> parse(const std::string& input);

private:
    enum class State {
        Normal,
        SingleQuote,
        DoubleQuote,
        Escape
    };
};