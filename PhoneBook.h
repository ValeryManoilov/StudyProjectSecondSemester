#ifndef FINALPROJECT_PHONEBOOK_H
#define FINALPROJECT_PHONEBOOK_H

#include "Person.h"
#include <string>

class PhoneBook {
private:

    struct Node {
        Person data;
        Node* next;
    };

    Node* head;
    friend void split(Node* source, Node** front, Node** back);
    friend Node* merge(Node* a, Node* b);
    friend void mergeSort(Node** headRef);

public:
    friend std::ostream& operator<<(std::ostream& os, const PhoneBook& book);
    friend std::istream& operator>>(std::istream& is, PhoneBook& book);
    PhoneBook();

    ~PhoneBook();

    PhoneBook(const PhoneBook& other);

    void add(const Person& person);

    void clear();

    void printAll() const;

    void sort();

    void addToSorted(const Person& person);

    void write(const std::string& c_name,
               const std::string& c_surname,
               const std::string& c_patronymic,
               const std::string& c_day,
               const std::string& c_month,
               const std::string& c_year,
               const std::string& c_phoneNumber) const;

    void remove(const std::string& c_name,
                const std::string& c_surname,
                const std::string& c_patronymic,
                const std::string& c_day,
                const std::string& c_month,
                const std::string& c_year,
                const std::string& c_phoneNumber);

    void getBirthday() const;

    void save(const std::string& filename) const;

    void load(const std::string& filename);

    friend std::ostream& operator<<(std::ostream& os,
                                    const PhoneBook& book);

    friend std::istream& operator>>(std::istream& is,
                                    PhoneBook& book);
};

#endif