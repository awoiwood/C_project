#include <iostream>
#include <string>

int main() {
    std::string name;
    int age;
    std::string fav_color;

    std::cout << "Enter your name: ";
    std::getline(std::cin, name);

    std::cout << "Enter your age: ";
    std::cin >> age;
    std::cin.ignore();

    std::cout << "What is your favorite color?";
    std::cin >> fav_color;
    std::cin.ignore();

    std::cout << "Hello, " << name << "! You are " << age << " years old. " << "Your favorite color is " << fav_color << std::endl;

    return 0;
}