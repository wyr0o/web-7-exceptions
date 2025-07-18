#include <iostream>
#include <string>
#include <Windows.h>

int function(std::string str, int forbidden_length) {
    int length = str.length();
    if (length == forbidden_length) {
        throw std::string("Вы ввели слово запретной длины! До свидания");
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
        catch (std::string& error_msg) {
            std::cout << error_msg << std::endl;
            break;
        }
    }

    return 0;
}