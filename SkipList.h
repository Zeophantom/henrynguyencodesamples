//
//  SkipList.h
//  Skip_List
//
//  Copyright Â© Tali Moreshet. All rights reserved.
//
//
//  This is an implementation of a Skip List class, consisting of Linked Lists, which are made up of Nodes.
//  All classes are templated, such that their types may be provided at creation.
//  Nodes contain data (which doubles as key), and pointers to all directions.

#ifndef SkipList_h
#define SkipList_h

#include <iostream>
#include <cstdlib>
#include <stdlib.h>

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
    Node<T>* tail;
    LinkedList<T> *up; 
    LinkedList<T> *down;                            
};

template <class T>
class SkipList {
public:
    SkipList(T minVal, T maxVal);                   // constructor: accepts -infinity, +infinity values,
                                                    //  creates skip list with top-level only
    ~SkipList();                                    // destructor
    Node<T>* search(T data);                        // search for data, return node <= data (existing node, or location
                                                    //  where new node should be inserted in the bottom-most list)
    Node<T>* insert(T data);                            // insert node with data, return pointer if inserted, NULL if error
    void printData();                               // prints skip list data
    void print();                                   // prints skip list with all nodes pointers
    LinkedList<T> *topList;                         // pointer to the top-most list
    LinkedList<T> *botList;                         // pointer to bottom list
    // Node<T>* tail;                       
    int randSeed = 330;                             // to be used as seed for the getRand() function
    LinkedList<T> *listptr;
    
};

//returns 0 or 1 with a 50% chance 
//When it returns 1, insert the node to next level of the skiplist
int getRand(){
    return rand()%2;
}

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
    tail = new Node<T>(maxVal);

    head->next = tail; //make sure the nodes are pointing to each other both ways
    tail->prev = head;
}


//deconstructor
template<class T>
LinkedList<T>::~LinkedList()
{
    Node<T>* temp; //initialize a new node 
    Node<T>* current = head;
    while(current->next != nullptr) //iterate through linked list until head hits nullptr
    {
        temp = current->next; // set out new temp node to the head
        delete current; //delete the current node'
        current = temp;
    }
    
}

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

    if (currentloc->next->data == data)
    {
        return NULL;
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

/****** Skip List Implementation ******/

   /*** TO BE COMPLETED ***/
template <class T>
SkipList<T>::SkipList(T minVal, T maxVal)
{

    topList = new LinkedList<T>(minVal, maxVal);
    Node<T>* tail = new Node<T>(maxVal);

    topList->head->next = tail;
    
    botList = new LinkedList<T>(minVal, maxVal);
    Node<T>* tail2 = new Node<T>(maxVal);

    botList->head->next = tail2;

    topList->head->down = botList->head;
    botList->head->up = topList->head;

    tail->down = tail2;
    tail2->up = tail;

    topList->down = botList;
    botList->up = topList;

    srand(this->randSeed);
}

template <class T>
SkipList<T>::~SkipList()
{
    LinkedList<T>* currList = topList;
    LinkedList<T>* temp;

    while (currList != nullptr)
    {
        temp = currList->down;
        delete currList;
        currList = temp;
    }
}

template <class T>
Node<T>* SkipList<T>::search(T data)
{
    Node<T>* current = topList->head;

    while (current->down != nullptr)
    {
        if (data < current->next->data)
        {
            current = current->down;
        }
        else if (data > current->next->data)
        {
            current = current->next;
        }
        else
        {
            current = current->down;
        }
    }

    while (data >= current->next->data)
    {
        current = current->next;
    }

    if (data >= current->data)
    {
        return current;
    }
    return current;
}


template <class T>
Node<T>* SkipList<T>::insert(T data)
{
    Node<T>* current = this->search(data);
    LinkedList<T>* currList = botList;
    
    if (current->data == data)
    {
        return NULL;
    }

    else
    {
        Node<T>* newNode = new Node<T>(data);

        currList->insert(current,data);


        while (getRand() == 1)
        {
            if (currList->up == topList)
            {
                LinkedList<T>* newlevel = new LinkedList<T>(this->topList->head->data, this->topList->head->next->data);

                newlevel->head->up = topList->head;
                newlevel->head->next->up = topList->head->next;

                topList->head->down = newlevel->head;
                topList->head->next->down = newlevel->head->next;

                newlevel->head->down = currList->head;
                newlevel->head->next->down = currList->tail;

                currList->tail->up = newlevel->head->next;
                currList->head->next->up = newlevel->head->next;
                
                newlevel->up = topList;
                newlevel->down = currList;
                topList->down = newlevel;
                currList->up = newlevel;
            }        
            
            currList = currList->up;
            current = currList->head;

            newNode = currList->search(current, data);
            currList->insert(newNode, data);

            }
        return newNode;
    }
}

template <class T>
void SkipList<T>::printData()
{
    LinkedList<T>* currList = topList;

    while (currList != nullptr)
    {
        currList->printData();
        cout << endl;
        currList = currList->down;
    }
    
        
}

template <class T>
void SkipList<T>::print()
{
    LinkedList<T>* LL = topList;
    

    while(LL != nullptr)
    {
        LL->print();
        LL = LL->down;
    }

}

#endif /* SkipList_h */