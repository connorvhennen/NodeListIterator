/** @file NodeListIterator.hpp
 @brief Declares a List, Iterator, and Node classes
 @author Connor Hennen
 @date November 15, 2016
 */

#ifndef NodeListIterator_hpp
#define NodeListIterator_hpp


#include <iostream>
#include <cmath>
#include <cassert>

class List;
class Iterator;


/** @class Node
 @brief A node class with downsize, maximum, and sort friend functions. It has a deference operator and Node pointers to the next and previous nodes.
 */
class Node {
    friend void downsize(List& names);
    friend unsigned int maximum(List& input);
    friend void sort(List& name);
    
public:
    Node();
    Node(int input);
    
    int operator*();
    
private:
    Node* next;
    Node* previous;
    
    int data;
    
    friend class List;
    friend class Iterator;
};


/** @class Iterator
 @brief This class is designed to go through a linked list and deference the node values. It has serveral overloaded operators and friend functions. Private variables are List and Node pointers.
 */
class Iterator {
    friend void downsize(List& names);
    friend unsigned int maximum(List& input);
    friend void sort(List& name);
    
public:
    friend bool operator==(const Iterator& a, const Iterator& b);
    
    Iterator();
    Iterator(Node* newNode);
    
    Iterator& operator++();
    Iterator operator++(int unused);
    
    Iterator& operator--();
    Iterator operator--(int unused);
    
    int operator*() const;
    
private:
    List* container;
    Node* current;
    
    friend class List; 
};

bool operator!=(const Iterator& a , const Iterator& b);
bool operator==(const Iterator& a , const Iterator& b);

/** @class List
 @brief This class is a list that with several functions (reverse, swap, merge, insert and erase) for modifying the list. Private member variables are pointers to the beginning and the end of the list, and an unsigned int for the size of the list.
 */
class List {
    friend void downsize(List& names);
    friend unsigned int maximum(List& input);
    friend void sort(List& name);
    
public:
    List();
    ~List();
    
    void push_front(int input);
    void push_back(int value);
    
    Iterator insert(Iterator position, int value);
    Iterator erase(Iterator position);
    
    Iterator begin();
    Iterator end();
    
    unsigned int get_size() const;
    
    void reverse();
    void swap(List& other);
    
    void merge (List& a);
    void print();
    
private:
    Node* first;
    Node* last;
    
    unsigned int size;
    
    friend class Iterator;
    
};

#endif
