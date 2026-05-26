#include "PhoneBook.h"
#include <iostream>
#include <fstream>
#include <limits>


PhoneBook::PhoneBook() {
    head = nullptr;
}

PhoneBook::~PhoneBook() {
    clear();
}

PhoneBook::PhoneBook(const PhoneBook& other) {
    head = nullptr;

    Node* current = other.head;

    while (current != nullptr) {
        add(current->data);
        current = current->next;
    }
}

void PhoneBook::add(const Person& person) {

    Node* newNode = new Node;
    newNode->data = person;
    newNode->next = nullptr;

    if (head == nullptr) {
        head = newNode;
        return;
    }

    Node* current = head;

    while (current->next != nullptr) {
        current = current->next;
    }

    current->next = newNode;
}

void PhoneBook::clear() {

    while (head != nullptr) {

        Node* temp = head;

        head = head->next;

        delete temp;
    }
}

void PhoneBook::printAll() const {

    if (head == nullptr) {
        std::cout << "Список пуст\n";
        return;
    }

    Node* current = head;

    while (current != nullptr) {

        current->data.write();
        std::cout << "---------------------\n";

        current = current->next;
    }
}

void split(PhoneBook::Node* source,
           PhoneBook::Node** front,
           PhoneBook::Node** back) {

    PhoneBook::Node* slow = source;
    PhoneBook::Node* fast = source->next;

    while (fast != nullptr) {
        fast = fast->next;
        if (fast != nullptr) {
            slow = slow->next;
            fast = fast->next;
        }
    }

    *front = source;
    *back = slow->next;
    slow->next = nullptr;
}
PhoneBook::Node* merge(PhoneBook::Node* a, PhoneBook::Node* b) {
    if (!a) {
        return b;
    }
    if (!b) {
        return a;
    }

    PhoneBook::Node* result = nullptr;

    if (a->data.compare(b->data) < 0) {
        result = a;
        result->next = merge(a->next, b);
    } else {
        result = b;
        result->next = merge(a, b->next);
    }

    return result;
}

void mergeSort(PhoneBook::Node** headRef) {

    PhoneBook::Node* head = *headRef;

    if (!head || !head->next) {
        return;
    }

    PhoneBook::Node* a = nullptr;
    PhoneBook::Node* b = nullptr;

    split(head, &a, &b);

    mergeSort(&a);
    mergeSort(&b);

    *headRef = merge(a, b);
}

void PhoneBook::sort() {
    mergeSort(&head);
}

void PhoneBook::write(const std::string& c_name,
                      const std::string& c_surname,
                      const std::string& c_patronymic,
                      const std::string& c_day,
                      const std::string& c_month,
                      const std::string& c_year,
                      const std::string& c_phoneNumber) const {

    Node* current = head;

    bool found = false;

    while (current != nullptr) {

        if (current->data.check(c_name,
                                c_surname,
                                c_patronymic,
                                c_day,
                                c_month,
                                c_year,
                                c_phoneNumber)) {

            current->data.write();
            std::cout << "---------------------\n";

            found = true;
                                }

        current = current->next;
    }

    if (!found) {
        std::cout << "Подходящих элементов не найдено\n";
    }
}

void PhoneBook::remove(const std::string& c_name,
                       const std::string& c_surname,
                       const std::string& c_patronymic,
                       const std::string& c_day,
                       const std::string& c_month,
                       const std::string& c_year,
                       const std::string& c_phoneNumber) {

    while (head != nullptr &&
           head->data.check(c_name,
                            c_surname,
                            c_patronymic,
                            c_day,
                            c_month,
                            c_year,
                            c_phoneNumber)) {

        Node* temp = head;

        head = head->next;

        delete temp;
                            }

    if (head == nullptr) {
        return;
    }

    Node* current = head;

    while (current->next != nullptr) {

        if (current->next->data.check(c_name,
                                      c_surname,
                                      c_patronymic,
                                      c_day,
                                      c_month,
                                      c_year,
                                      c_phoneNumber)) {

            Node* temp = current->next;

            current->next = current->next->next;

            delete temp;
                                      }
        else {
            current = current->next;
        }
    }
}

int toDayOfYear(int day, int month) {

    static int daysInMonth[] = {
        0,
        31,28,31,30,31,30,
        31,31,30,31,30,31
    };

    int sum = 0;
    for (int i = 1; i < month; i++) {
        sum += daysInMonth[i];
    }

    return sum + day;
}

void PhoneBook::getBirthday() const {

    if (head == nullptr) {
        std::cout << "Список пуст\n";
        return;
    }

    time_t t = time(nullptr);
    tm* now = localtime(&t);

    int currentDay = toDayOfYear(now->tm_mday, now->tm_mon + 1);

    Node* current = head;

    Node* closestNode = nullptr;
    int minDays = INT_MAX;

    while (current != nullptr) {

        int birthDay = current->data.getDay();
        int birthMonth = current->data.getMonth();

        int birthdayThisYear = toDayOfYear(birthDay, birthMonth);

        int diff = birthdayThisYear - currentDay;

        if (diff < 0) {
            diff += 365;
        }

        if (diff < minDays) {
            minDays = diff;
            closestNode = current;
        }

        current = current->next;
    }

    if (closestNode != nullptr) {
        std::cout << "Ближайший день рождения:\n";
        closestNode->data.write();
        std::cout << "Осталось дней: " << minDays << "\n";
    }
}

void PhoneBook::load(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cout << "Ошибка открытия файла\n";
        return;
    }
    clear();
    while (!file.eof()) {
        std::string surname;
        std::string name;
        std::string patronymic;
        std::string phoneNumber;

        short day;
        short month;
        short year;

        std::getline(file, surname);

        if (surname.empty()) {
            break;
        }
        std::getline(file, name);
        std::getline(file, patronymic);
        file >> day;
        file >> month;
        file >> year;
        file.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::getline(file, phoneNumber);

        Person person(name,
                      surname,
                      patronymic,
                      day,
                      month,
                      year,
                      phoneNumber);

        add(person);
    }
    file.close();
}

std::ostream& operator<<(std::ostream& os,
                         const PhoneBook& book) {
    PhoneBook::Node* current = book.head;
    while (current != nullptr) {
        current->data.write();
        os << "---------------------\n";
        current = current->next;
    }
    return os;
}

std::istream& operator>>(std::istream& is,
                         PhoneBook& book) {
    Person person;
    person.read();
    book.add(person);
    return is;
}

void PhoneBook::save(const std::string &filename) const {
    std::ofstream file(filename);

    if (!file.is_open()) {
        std::cout << "Ошибка открытия файла\n";
        return;
    }

    Node* current = head;

    while (current != nullptr) {

        file << current->data.getSurname() << "\n";
        file << current->data.getName() << "\n";
        file << current->data.getPatronymic() << "\n";
        file << current->data.getDay() << "\n";
        file << current->data.getMonth() << "\n";
        file << current->data.getYear() << "\n";
        file << current->data.getPhoneNumber() << "\n";

        current = current->next;
    }

    file.close();
}

