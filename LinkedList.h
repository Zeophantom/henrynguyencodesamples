//
//  LinkedList.h
//  Linked_List
//
//  Copyright Â© Tali Moreshet. All rights reserved.
//
//  This is an implementation of an ordered Linked List class, which is made up of Nodes.
//  All classes are templated, such that their types may be provided at creation.
//  Nodes contain data (which doubles as key), and pointers to all directions.

#ifndef LinkedList_h
#define LinkedList_h

#include <iostream>
#include <cstdlib>
#include <time.h>

using namespace std;

template<class T>
class Node {
public:
    Node(const T& data);                            // constructor
    T data;                                         // node data, doubles as key
    Node<T> *next;                                  // node next pointer
    Node<T> *prev;                                  // node previous pointer
    Node<T> *up;                                    // node above pointer
    Node<T> *down;                                  // node below pointer
    void printData();                               // prints data value
    void print();                                   // prints entire node object content
};

template <class T>
class LinkedList {
public:
    LinkedList(T minVal, T maxVal);                 // constructor: accepts -infinity, +infinity values,
                                                    //  creates linked list with two corresponding nodes
    ~LinkedList();                                  // destructor
    Node<T>* search(Node<T>* location, T data);     // search for data starting at location, return node <= data
    Node<T>* insert(Node<T>* location, T data);     // insert node with data at new node to be placed directly 
                                                    //  after node with povided location, return new node
    void printData();                               // prints linked list data
    void print();                                   // prints linked list with all nodes pointers
    Node<T>* head;                                  // head of list
};

/********************** From here down is the content of the LinkedList.cpp file: ***********************/

/****** Implementation of Node ******/

// Constructor
template<class T>
Node<T>::Node(const T& data)
{
    this->data = data;
    this->next = nullptr;
    this->prev = nullptr;
    this->up = nullptr;
    this->down = nullptr;
}

// Print node's data value
template <class T>
void Node<T>::printData()
{
    cout << data << " ";
}

// Print entire node object content (data value, object's address, and all pointers)
template <class T>
void Node<T>::print()
{
    cout << " * " << data << ": [addr: " << this << " next: " << this->next << " prev: " << this->prev << " up: " << this->up << " down: " << this->down << "]  ";
}


/****** Implementation of linked list ******/

/*** TO BE COMPLETED ***/

template<class T>
LinkedList<T>::LinkedList(T minVal, T maxVal)
{
    head = new Node<T>(minVal); //set the head of the linked list to minVal and the tail to maxVal
    Node<T>* tail = new Node<T>(maxVal);

    head->next = tail; //make sure the nodes are pointing to each other both ways
    tail->prev = head;
}


//deconstructor
template<class T>
LinkedList<T>::~LinkedList()
{
    Node<T>* temp; //initialize a new node 
    
    while(head != nullptr) //iterate through linked list until head hits nullptr
    {
        temp = head; // set out new temp node to the head
        head = head->next; // move head pointer to the next node
        delete temp; //delete the current node
    }
    
}

//search function
template <class T>
Node<T>* LinkedList<T>::search(Node<T>* location, T data)
{
    Node<T>* currentloc = location; // set the current location pointer to the starting position of user input
    
    while (currentloc->next != nullptr && currentloc->next->data <= data)//iterates through the linked list while the pointer does not point to NULL and checks to see if the value of the user inputed data is less than or equal to the next node
    {
        currentloc = currentloc->next;
    } 
        
    return currentloc; //returns the current node if data is found in the linked list
}

//insert function
template <class T>
Node<T>* LinkedList<T>::insert(Node<T>* location, T data)
{
    Node<T>* newNode = new Node<T>(data); //initialize new node with the user inputted data value
    Node<T>* currentloc = head; // set current location pointer to head of the linked list

    while (currentloc->next !=nullptr && currentloc->next->data < data) //iterate through the linked list and checks to if user data is greater than nodes already in linked list, if it is go to next node, if not insert the node
    {
        currentloc = currentloc->next;
    }

    newNode->next = currentloc->next; //insert node
    newNode->prev = currentloc;

    if (currentloc->next != nullptr) //updates the pointers to make sure the the previous node is pointing to the new node and the new node is pointing to the previous node
    {
        currentloc->next->prev = newNode;
    }

    currentloc->next = newNode;

    return location = newNode;
    
}

//print data function
template<class T>
void LinkedList<T>::printData()
{
    Node<T>* currentloc = head; //initialize current location to the head of the linked list

    while (currentloc != nullptr) //iterate through the linked list and print out the data value
    {
        currentloc->printData();
        currentloc = currentloc->next;
    }
}


//print function
template<class T>
void LinkedList<T>::print()
{
    Node<T>* currentloc = head; //initialize current location to the head of the linked list

    while(currentloc !=nullptr) //iterate through the linked list and print out the address of the current pointer and everything around it
    {
        currentloc->print();
        currentloc = currentloc->next;
    }
}
#endif /* LinkedList_h */