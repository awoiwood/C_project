// input_utils.h
#ifndef INPUT_UTILS_H
#define INPUT_UTILS_H

#include <string>
#include <vector>
#include <algorithm>
#include <cctype>
#include <iostream>
#include <limits>
#include <functional>
#include <ranges>

namespace input {

    enum class SignPolicy {
        PositiveOnly,
        NegativeOnly,
        AllowAll,
    };

    // Convert a string to lowercase
    inline std::string to_lower(const std::string& str) {
        std::string result = str;
        std::ranges::transform(result, result.begin(),
                               [](unsigned char c) { return std::tolower(c); });
        return result;
    }

    // Check if a string is a valid integer with optional sign policy
    inline bool is_integer(const std::string& str, SignPolicy policy = SignPolicy::AllowAll) {
        if (str.empty()) return false;

        size_t start = 0;
        if (str[0] == '+' || str[0] == '-') {
            if (str.size() == 1) return false; // only sign, no digits
            if (str[0] == '+' && policy == SignPolicy::NegativeOnly) return false;
            if (str[0] == '-' && policy == SignPolicy::PositiveOnly) return false;

            start = 1; //skip over the sign to go to the numbers
        }

        using Diff = std::string::difference_type;
        return std::ranges::all_of(str.begin() + static_cast<Diff>(start), str.end(), [](char ch) {
            return ch >= '0' && ch <= '9';
        });
    }

    // Safely get an integer within a range from user input
    inline int int_is_between(const std::string& prompt, int min, int max) {
        std::string input;
        int value = 0;
        while (true) {
            std::cout << prompt;
            std::getline(std::cin, input);
            if (is_integer(input)) {
                value = std::stoi(input);
                if (value >= min && value <= max) break;
                else std::cout << "Value must be between " << min << " and " << max << ".\n";
            } else {
                std::cout << "Invalid input. Please enter a valid integer.";
                std::cout << "\n";
            }
        }
        return value;
    }
}

#endif // INPUT_UTILS_H
