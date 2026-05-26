//
// Created by ValeryManoilov on 5/26/2026.
//

#ifndef FINALPROJECT_NODE_H
#define FINALPROJECT_NODE_H

struct Node {
    Person data;
    Node* next;

    Node(const Person& person)
        : data(person), next(nullptr) {}
};


#endif //FINALPROJECT_NODE_H