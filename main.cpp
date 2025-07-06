#include <iostream>
#include <string>
#include <vector>
#include <algorithm>


std::string to_lower(const std::string& str) {
    std::string result = str;
    std::ranges::transform(result, result.begin(),
                           [](unsigned char c) { return std::tolower(c); });
    return result;
}

bool is_valid_color(const std::string& color, const std::vector<std::string>& colors) {
    return std::ranges::find(colors, color) != colors.end();
}

bool is_integer(const std::string& s) {
    for (char ch : s) {
        if (!std::isdigit(ch)) return false;
    }
    return !s.empty();
}

int main() {
    std::string name;
    std::string input;
    int age;
    std::string fav_color;

    std::vector<std::string> colors = {
        "red", "yellow", "orange", "green", "blue",
        "indigo", "purple", "violet", "white", "black", "pink"
    };

    std::cout << "Enter your name: ";
    std::getline(std::cin, name);

    while (true) {
        std::cout << "Enter your age: ";
        std::getline(std::cin, input);
        if (is_integer(input)) {
            age = std::stoi(input);
            if (age >= 1 && age <= 120) {
                break;
            } else {
                std::cout << "Age must be between 1 and 120.\n";
            }
        } else {
            std::cout << "Invalid input. Please enter a whole number.\n";
        }
    }

    while (true) {
        std::cout << "Enter your favorite color (options: red, yellow, orange, green, blue, indigo, purple, violet, white, black, pink): ";
        std::getline(std::cin, fav_color);

        std::string input_lower = to_lower(fav_color); // normalize case

        if (is_valid_color(input_lower, colors)) {
            fav_color = input_lower;
            break;
        } else {
            std::cout << "Invalid color. Please choose from the list.\n";
        }
    }

    std::cout << "Hello, " << name << "! ";
    std::cout << "You are " << age << " year" << (age == 1 ? "" : "s") << " old. ";
    std::cout << "Your favorite color is " << fav_color << "." << std::endl;

    return 0;
}