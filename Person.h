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

    void read(const std::string& filename, int personNum);

    void write() const;

    [[nodiscard]] bool check(const std::string& c_name,
        const std::string& c_surname,
        const std::string& c_patronymic,
        const std::string& c_day,
        const std::string& c_month,
        const std::string& c_year,
        const std::string& c_phoneNumber) const;

    int compare(const Person& otherPerson) const;

    [[nodiscard]] double dayBeforeBirthday() const;
};

#endif //FINALPROJECT_PERSON_H