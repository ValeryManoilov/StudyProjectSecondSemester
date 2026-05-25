#include <fstream>
#include <iostream>
#include <windows.h>
#include "json.hpp"
#include "Person.h"

using json = nlohmann::json;

int main() {
    SetConsoleCP(CP_UTF8);
    SetConsoleOutputCP(CP_UTF8);

    Person person, person1, person2;
    person1.read("C:\\Users\\ValeryManoilov\\CLionProjects\\FinalProject\\data.json", 0);
    person2.read("C:\\Users\\ValeryManoilov\\CLionProjects\\FinalProject\\data.json", 1);
    // std::cout << person1.compare(person2);
    // person.read();
    // person1.write();
    // double days = person.dayBeforeBirthday();
    // std::cout << "Дней до дня рождения: " << days << std::endl;
}