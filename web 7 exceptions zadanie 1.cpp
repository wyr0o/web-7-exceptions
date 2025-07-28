#include <iostream>
#include <string>
#include <stdexcept>
#include <Windows.h>

class BadLengthException : public std::exception {
private:
    std::string message;
public:
    BadLengthException(const std::string& msg) : message(msg) {}
    const char* what() const noexcept override {
        return message.c_str();
    }
};

int function(std::string str, int forbidden_length) {
    int length = str.length();
    if (length == forbidden_length) {
        throw BadLengthException("Вы ввели слово запретной длины! До свидания");
    }
    return length;
}

int main() {
    SetConsoleOutputCP(1251);
    SetConsoleCP(1251);
    int forbidden_len;
    std::cout << "Введите запретную длину: ";
    std::cin >> forbidden_len;

    while (true) {
        std::string word;
        std::cout << "Введите слово: ";
        std::cin >> word;

        try {
            int len = function(word, forbidden_len);
            std::cout << "Длина слова \"" << word << "\" равна " << len << std::endl;
        }
        catch (const std::exception& e) {
            std::cout << e.what() << std::endl;
            break;
        }
    }

    return 0;
}