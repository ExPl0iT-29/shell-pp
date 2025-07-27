#include "Parser.h"
#include <cctype>
#include <stdexcept>

std::vector<Parser::ParsedCommand> Parser::parse(const std::string& input) {
    std::vector<ParsedCommand> commands;
    ParsedCommand current_cmd;
    std::string current_token;
    State state = State::Normal;
    char quote_char = '\0';

    for (size_t i = 0; i < input.size(); ++i) {
        const char c = input[i];

        switch (state) {
        case State::Normal:
            if (c == '\'') {
                state = State::SingleQuote;
                quote_char = c;
            }
            else if (c == '"') {
                state = State::DoubleQuote;
                quote_char = c;
            }
            else if (c == '\\') {
                state = State::Escape;
            }
            else if (std::isspace(c)) {
                if (!current_token.empty()) {
                    current_cmd.args.push_back(current_token);
                    current_token.clear();
                }
            }
            else if (c == '|') {
                // Handle pipe operator (future milestone)
                if (!current_token.empty()) {
                    current_cmd.args.push_back(current_token);
                    current_token.clear();
                }
                if (!current_cmd.args.empty()) {
                    commands.push_back(current_cmd);
                    current_cmd = ParsedCommand();
                }
            }
            else {
                current_token += c;
            }
            break;

        case State::SingleQuote:
            if (c == '\'') {
                state = State::Normal;
            }
            else {
                current_token += c;
            }
            break;

        case State::DoubleQuote:
            if (c == '"') {
                state = State::Normal;
            }
            else if (c == '\\' && i + 1 < input.size()) {
                // Handle escaped characters in double quotes
                current_token += input[++i];
            }
            else {
                current_token += c;
            }
            break;

        case State::Escape:
            current_token += c;
            state = State::Normal;
            break;
        }
    }

    // Handle final token and command
    if (!current_token.empty()) {
        current_cmd.args.push_back(current_token);
    }

    if (state != State::Normal) {
        throw std::runtime_error("Unclosed quote in input");
    }

    if (!current_cmd.args.empty()) {
        commands.push_back(current_cmd);
    }

    return commands;
}