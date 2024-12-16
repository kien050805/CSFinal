#include <iostream>
#include <exception>
using namespace std;

#ifndef CUSTOMEXCEPTIONS_HPP
#define CUSTOMEXCEPTIONS_HPP

class edge_exception : public exception {
public:
    const char* what() const throw() {
        return "Error: Edge Exception.";
    }
};

class vertex_exception : public exception {
public:
    const char* what() const throw() {
        return "Error: Vertex Exception.";
    }
};

class heap_underflow_exception : public exception {
public:
    const char* what() const throw() {
        return "Error: Heap Underflow Exception.";
    }
};

class Key_exception : public exception {
public:
    const char* what() const throw() {
        return "Error: Key Exception: New Key is greater than current key";
    }
};
#endif