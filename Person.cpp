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
    short p_day,
    short p_month,
    short p_year,
    std::string p_phoneNumber)
{
    name = p_name;
    surname = p_surname;
    patronymic = p_patronymic;
    day = p_day;
    month = p_month;
    year = p_year;
    phoneNumber = p_phoneNumber;
}

void Person::read() {
    std::cout << "Введите фамилию: ";
    std::getline(std::cin, surname);

    std::cout << "Введите имя: ";
    std::getline(std::cin, name);

    std::cout << "Введите отчество: ";
    std::getline(std::cin, patronymic);

    do  {
        std::cout << "Введите месяц рождения (число от 1 до 12): ";
        std::cin >> month;
        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(32767, '\n');
            std::cout << "Ошибка! Введите число.\n";
        }
    }
    while (month < 1 || month > 12);

    do  {
        std::cout << "Введите год рождения: ";
        std::cin >> year;
        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(32767, '\n');
            std::cout << "Ошибка! Введите число.\n";
        }
    }
    while (year < 1900 || year > 2100);

    switch (month) {
        case 1:
        case 3:
        case 5:
        case 7:
        case 8:
        case 10:
        case 12:
            do {
                std::cout << "Введите день рождения (число от 1 до 31): ";
                std::cin >> day;
                if (std::cin.fail()) {
                    std::cin.clear();
                    std::cin.ignore(32767, '\n');
                    std::cout << "Ошибка! Введите число.\n";
                }
            }
            while (day < 1 || day > 31);
            break;
        case 4:
        case 6:
        case 9:
        case 11:
            do {
                std::cout << "Введите день рождения (число от 1 до 30): ";
                std::cin >> day;
                if (std::cin.fail()) {
                    std::cin.clear();
                    std::cin.ignore(32767, '\n');
                    std::cout << "Ошибка! Введите число.\n";
                }
            }
            while (day < 1 || day > 30);
            break;
        case 2:
            if (year % 4 == 0) {
                do {
                    std::cout << "Введите день рождения (число от 1 до 29): ";
                    std::cin >> day;
                    if (std::cin.fail()) {
                        std::cin.clear();
                        std::cin.ignore(32767, '\n');
                        std::cout << "Ошибка! Введите число.\n";
                    }
                }
                while (day < 1 || day > 29);
            }
            else {
                do {
                    std::cout << "Введите день рождения (число от 1 до 28): ";
                    std::cin >> day;
                    if (std::cin.fail()) {
                        std::cin.clear();
                        std::cin.ignore(32767, '\n');
                        std::cout << "Ошибка! Введите число.\n";
                    }
                }
                while (day < 1 || day > 28);
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

void Person::read(std::string filename, int personNum) {
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

bool Person::check(std::string c_name,
    std::string c_surname,
    std::string c_patronymic,
    std::string c_day,
    std::string c_month,
    std::string c_year,
    std::string c_phoneNumber)
{
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

double Person::dayBeforeBirthday() {
    time_t now_time = time(0);
    tm* timeinfo = localtime(&now_time);
    tm birthday = *timeinfo;

    birthday.tm_mday = day;
    birthday.tm_mon = month - 1;

    birthday.tm_year = timeinfo->tm_year;

    time_t birthday_time = mktime(&birthday);

    if (difftime(birthday_time, now_time) < 0) {
        birthday.tm_year += 1;
        birthday_time = mktime(&birthday);
    }

    return difftime(birthday_time, now_time) / 86400.0;
}

void Person::write() {
    std::cout << "===Данные об объекте===" << std::endl;
    std::cout << "Имя: " << name << std::endl;
    std::cout << "Фамилия: " << surname << std::endl;
    std::cout << "Отчество: " << patronymic << std::endl;
    std::cout << "День рождения: " << day << "." << month << "." << year << std::endl;
    std::cout << "Номер телефона: " << phoneNumber << std::endl;
}

int Person::compare(Person otherPerson) {
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