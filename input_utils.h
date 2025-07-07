// input_utils.h
#ifndef INPUT_UTILS_H
#define INPUT_UTILS_H
#include <stdexcept>
#include <string>
#include <algorithm>
#include <cctype>
#include <iostream>
#include <limits>

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

     // Check if string fits into long long without overflow
    inline bool fits_in_long_long(const std::string& str) {
        static const std::string max_ll = "9223372036854775807";
        static const std::string min_ll = "9223372036854775808";
        if (str.empty()) return false;
        bool negative = str[0] == '-';
        std::string digits = (str[0] == '+' || str[0] == '-') ? str.substr(1) : str;
        if (digits.length() > 19) return false;
        if (digits.length() < 19) return true;

        return digits <= (negative ? min_ll : max_ll);
    }

    // Safely get an integer within a range from user input0
    inline int int_is_between(const std::string& prompt, const std::string& minstr, const std::string& maxstr) {
        const long long intmin = std::numeric_limits<int>::min();
        const long long intmax = std::numeric_limits<int>::max();
        // Test as a string first and reject if too large
        if (!fits_in_long_long(minstr)) {
            throw std::invalid_argument("Min value: "+minstr+" is too large");
        }
        if (!fits_in_long_long(maxstr)) {
            throw std::invalid_argument("Max value: "+maxstr+" is too large");
        }
        long long min = std::stoll(minstr);
        long long max = std::stoll(maxstr);
        if (min < intmin || max > intmax || min > max) {
            throw std::invalid_argument("Range is invalid or exceeds 32-bit integer limits.");
        }
        std::string input;
        int value = 0;
        while (true) {
            std::cout << prompt;
            std::getline(std::cin, input);
            try {
                if (is_integer(input)) {
                    value = std::stoi(input);
                    if (value >= static_cast<int>(min) && value <= static_cast<int>(max)) {
                        break;
                    } else {
                        std::cout << "Value must be between " << min << " and " << max << ".\n";
                    }
                } else {
                    std::cout << "Invalid input. Please enter a valid integer.\n";
                }
            } catch (const std::exception& e) {
                std::cout << "Conversion error: " << e.what() << "\n";
            }
        }
        return value;
    }
    }

#endif // INPUT_UTILS_H
