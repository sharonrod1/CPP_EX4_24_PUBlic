#ifndef NODE_HPP
#define NODE_HPP

#include <iostream>
#include <vector>
#include <string>

template<typename T>
class Node {
public:
    T data;
    Node<T>* parent;
    std::vector<Node<T>*> neighbors;
    int id;
    static int id_counter;
    
    Node(T value) : data(value), parent(nullptr), id(id_counter++) {}

    T get_value() const {
        return data;
    }
    int getId() const {
        return id;
    }
};

template<typename T>
int Node<T>::id_counter = 0;

#endif
