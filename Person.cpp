#include "Person.h"
#include <fstream>
#include <iostream>
#include <time.h>
#include "json.hpp"

Person::Person() {
    name = "pass";
    surname = "pass";
    patronymic = "pass";
    day = 0;
    month = 0;
    year = 0;
    phoneNumber = "pass";
};

Person::Person(std::string p_name,
    std::string p_surname,
    std::string p_patronymic,
    const short p_day,
    const short p_month,
    const short p_year,
    std::string p_phoneNumber)
{
    name = std::move(p_name);
    surname = std::move(p_surname);
    patronymic = std::move(p_patronymic);
    day = p_day;
    month = p_month;
    year = p_year;
    phoneNumber = std::move(p_phoneNumber);
}

void Person::read() {
    const std::time_t t = std::time(nullptr);
    const std::tm* now = std::localtime(&t);
    const auto now_year = now->tm_year + 1900;
    const auto now_month = now->tm_mon + 1;
    const auto now_day = now->tm_mday;

    std::cout << "Введите фамилию: ";
    std::cin >> surname;

    std::cout << "Введите имя: ";
    std::cin >> name;

    std::cout << "Введите отчество: ";
    std::cin >> patronymic;

    do  {
        std::cout << "Введите год рождения: ";
        std::cin >> year;
        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(32767, '\n');
            std::cout << "Ошибка! Введите число от 1900 до " << now_year << std::endl;
        }
    }
    while (year < 1900 || year > now_year);

    do  {
        std::cout << "Введите месяц рождения (число от 1 до 12): ";
        std::cin >> month;
        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(32767, '\n');
            std::cout << "Ошибка! Введите число от 1 до 12";
        }
    }
    while (month < 1 || month > 12 || (year == now_year && month > now_month));

    switch (month) {

        case 1: case 3: case 5: case 7: case 8: case 10: case 12:
            do {
                std::cout << "Введите день рождения (число от 1 до 31): ";
                std::cin >> day;
                if (std::cin.fail()) {
                    std::cin.clear();
                    std::cin.ignore(32767, '\n');
                    std::cout << "Ошибка! Введите число от 1 до 31";
                }
            }
            while (day < 1 || day > 31 || (year == now_year && day > now_day));
            break;

        case 4: case 6: case 9: case 11:
            do {
                std::cout << "Введите день рождения (число от 1 до 30): ";
                std::cin >> day;
                if (std::cin.fail()) {
                    std::cin.clear();
                    std::cin.ignore(32767, '\n');
                    std::cout << "Ошибка! Введите число от 1 до 30";
                }
            }
            while (day < 1 || day > 30 || (year == now_year && day > now_day));
            break;
        case 2:
            if (year % 4 == 0) {
                do {
                    std::cout << "Введите день рождения (число от 1 до 29): ";
                    std::cin >> day;
                    if (std::cin.fail()) {
                        std::cin.clear();
                        std::cin.ignore(32767, '\n');
                        std::cout << "Ошибка! Введите число от 1 до 29";
                    }
                }
                while (day < 1 || day > 29 || (year == now_year && day > now_day));
            }
            else {
                do {
                    std::cout << "Введите день рождения (число от 1 до 28): ";
                    std::cin >> day;
                    if (std::cin.fail()) {
                        std::cin.clear();
                        std::cin.ignore(32767, '\n');
                        std::cout << "Ошибка! Введите число от 1 до 28";
                    }
                }
                while (day < 1 || day > 28 || (year == now_year && day > now_day));
            }
            break;
        default:
            break;
    }

    do {
        std::cout << "Введите номер телефона: ";
        std::cin >> phoneNumber;
    }
    while (phoneNumber.length() < 10 || phoneNumber.length() > 13);
}

void Person::read(const std::string& filename, const int personNum) {

    using json = nlohmann::json;

    std::ifstream file(filename);

    if (!file.is_open()) {
        std::cout << "Ошибка открытия файла\n";
        return;
    }

    json j;
    file >> j;

    surname = j[personNum]["surname"];
    name = j[personNum]["name"];
    patronymic = j[personNum]["patronymic"];
    day = j[personNum]["birth"]["day"];
    month = j[personNum]["birth"]["month"];
    year = j[personNum]["birth"]["year"];
    phoneNumber = j[personNum]["phoneNumber"];

    file.close();
}

bool Person::check(const std::string& c_name,
    const std::string& c_surname,
    const std::string& c_patronymic,
    const std::string& c_day,
    const std::string& c_month,
    const std::string& c_year,
    const std::string& c_phoneNumber) const {

    if (c_name != "*" && c_name != name) {
        return false;
    }
    if (c_surname != "*" && c_surname != surname) {
        return false;
    }
    if (c_patronymic != "*" && c_patronymic != patronymic) {
        return false;
    }
    if (c_day != "*" && std::stoi(c_day) != day) {
        return false;
    }
    if (c_month != "*" && std::stoi(c_month) != month) {
        return false;
    }
    if (c_year != "*" && std::stoi(c_year) != year) {
        return false;
    }
    if (c_phoneNumber != "*" && c_phoneNumber != phoneNumber) {
        return false;
    }
    return true;
}

double Person::dayBeforeBirthday() const {
    const time_t now_time = time(0);
    const tm* timeInfo = localtime(&now_time);
    tm birthday = *timeInfo;

    birthday.tm_mday = day;
    birthday.tm_mon = month - 1;

    birthday.tm_year = timeInfo->tm_year;

    time_t birthday_time = mktime(&birthday);

    if (difftime(birthday_time, now_time) < 0) {
        birthday.tm_year += 1;
        birthday_time = mktime(&birthday);
    }

    return difftime(birthday_time, now_time) / 86400.0;
}

void Person::write() const {
    std::cout << "===Данные об объекте===" << std::endl;
    std::cout << "Имя: " << name << std::endl;
    std::cout << "Фамилия: " << surname << std::endl;
    std::cout << "Отчество: " << patronymic << std::endl;
    std::cout << "День рождения: " << day << "." << month << "." << year << std::endl;
    std::cout << "Номер телефона: " << phoneNumber << std::endl;
}

int Person::compare(const Person& otherPerson) const {
    if (surname != otherPerson.surname) {
        return surname < otherPerson.surname ? -1 : 1;
    }
    if (name != otherPerson.name) {
        return name < otherPerson.name ? -1 : 1;
    }
    if (patronymic != otherPerson.patronymic) {
        return patronymic < otherPerson.patronymic ? -1 : 1;
    }

    if (year != otherPerson.year) {
        return year - otherPerson.year;
    }

    if (month != otherPerson.month) {
        return month - otherPerson.month;
    }

    if (day != otherPerson.day) {
        return day - otherPerson.day;
    }
    return 0;
}