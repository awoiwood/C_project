#include <iostream>
#include <string>


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

    std::cout << "Enter your name: ";
    std::getline(std::cin, name);

    while (true) {
        std::cout << "Enter your age: ";
        std::getline(std::cin, input);
        if (is_integer(input)) {
            age = std::stoi(input);
            break;
        } else {
            std::cout << "Invalid input. Please enter a whole number.\n";
        }
    }

    std::cout << "What is your favorite color? ";
    std::getline(std::cin, fav_color);

    std::cout << "Hello, " << name << "! You are " << age << " years old. ";
    std::cout << "Your favorite color is " << fav_color << "." << std::endl;

    return 0;
}