#include "PhoneBook.h"
#include <iostream>
#include <sstream>
#include <windows.h>

int main() {
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
    PhoneBook book;
    std::string line;

    std::cout << "PhoneBook CLI. Введите 'help' для списка команд.\n";

    while (true) {
        std::cout << "> ";
        std::getline(std::cin, line);

        if (line.empty()) continue;

        std::istringstream iss(line);
        std::string cmd;
        iss >> cmd;

        if (cmd == "help") {
            std::cout <<
                "Команды:\n"
                "help - список команд\n"
                "clear - очистить список\n"
                "load <filename> - загрузить из файла\n"
                "save <filename> - сохранить в файл\n"
                "add - добавить элемент\n"
                "sort - отсортировать список\n"
                "find <фамилия> <имя> <отчество> <день> <месяц> <год> <телефон> - найти элементы (* - любое значение)\n"
                "delete <фамилия> <имя> <отчество> <день> <месяц> <год> <телефон> - удалить элементы\n"
                "birthday - ближайший день рождения\n"
                "exit - выход\n";
        }

        else if (cmd == "exit") {
            break;
        }

        else if (cmd == "clear") {
            book.clear();
            std::cout << "Список очищен\n";
        }

        else if (cmd == "load") {
            std::string filename;
            iss >> filename;

            if (filename.empty()) {
                std::cout << "Укажи файл\n";
                continue;
            }

            book.load(filename);
            std::cout << "Загружено из " << filename << "\n";
        }

        else if (cmd == "save") {
            std::string filename;
            iss >> filename;

            if (filename.empty()) {
                std::cout << "Укажи файл\n";
                continue;
            }

            book.save(filename);
            std::cout << "Сохранено в " << filename << "\n";
        }

        else if (cmd == "add") {
            std::cout << "Ввод нового человека:\n";

            Person p;
            p.read();

            book.add(p);

            std::cout << "Добавлено\n";
        }

        else if (cmd == "sort") {
            book.sort();
            std::cout << "Отсортировано\n";
        }

        else if (cmd == "find") {
            std::string name = "*";
            std::string surname = "*";
            std::string patronymic = "*";
            std::string day = "*";
            std::string month = "*";
            std::string year = "*";
            std::string phoneNumber = "*";

            iss >> surname >> name >> patronymic >> day >> month >> year >> phoneNumber;

            std::cout << "Результаты поиска:\n";
            book.write(name, surname, patronymic, day, month, year, phoneNumber);
        }

        else if (cmd == "delete") {
            std::string name = "*";
            std::string surname = "*";
            std::string patronymic = "*";
            std::string day = "*";
            std::string month = "*";
            std::string year = "*";
            std::string phoneNumber = "*";

            iss >> surname >> name >> patronymic >> day >> month >> year >> phoneNumber;

            if (surname == "*" && name == "*" && patronymic == "*" &&
                day == "*" && month == "*" && year == "*" && phoneNumber == "*") {
                std::cout << "Укажите параметры для удаления\n";
                std::cout << "Пример: delete Иванов Иван\n";
                continue;
                }

            book.remove(name, surname, patronymic, day, month, year, phoneNumber);
            std::cout << "Удаление выполнено\n";
        }

        else if (cmd == "birthday") {
            book.getBirthday();
        }

        else {
            std::cout << "Неизвестная команда. help для списка.\n";
        }
    }

    return 0;
}