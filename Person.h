#ifndef FINALPROJECT_PERSON_H
#define FINALPROJECT_PERSON_H

#include <string>

class Person {
private:
    std::string name;
    std::string surname;
    std::string patronymic;
    short day;
    short month;
    short year;
    std::string phoneNumber;

public:
    Person();

    Person(std::string p_name,
        std::string p_surname,
        std::string p_patronymic,
        short p_day,
        short p_month,
        short p_year,
        std::string phoneNumber);

    void read();

    void read(std::string filename, int personNum);

    void write();

    bool check(std::string c_name,
        std::string c_surname,
        std::string c_patronymic,
        std::string c_day,
        std::string c_month,
        std::string c_year,
        std::string c_phoneNumber);

    int compare(Person otherPerson);

    double dayBeforeBirthday();
};

#endif //FINALPROJECT_PERSON_H