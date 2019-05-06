#include "Lane.h"
#include "Node.h"
#include <iostream>
#include <string>
#include <sstream>
using namespace std;

/// Constructors
Lane::Lane() {
    /// default constructor
    size = 0;
    list = NULL;
}

/// Accessors
int Lane::getSize( void ) {
    /// return number of items in the list
    return size;
}

Node * Lane::getList( void ) {
    /// return pointer to first nod ein the list
    return this->list;
}

void Lane::print( void ) {
    /// print list data to stdout
    cout << "List:";
    Node * ptr = list;
    while( ptr != NULL ) {
        cout << ptr->getData() << " ";
        ptr = ptr->getNext();
    }
    cout << endl;
}

string Lane::toString( void ) {
    /// returns a space separated string with list contents
    stringstream ss;
    Node * ptr = list;
    while( ptr != NULL ) {
        ss << ptr->getData() << " ";
        ptr = ptr->getNext();
    }
    return ss.str();
}

// mutators
void Lane::addItem( int item ) {
    /// add new item to the list in front
    Node * n = new Node;            // create new node
    n->setData( item );             // save the item
    n->setNext( this->list );       // node point to old list
    // cout << "next item data data: " << list->getData();
    this->list = n;                 // list points to new node
    this->size += 1;               // increase list size
    // cout << "item" << item <<  "added";
}

void Lane::append(int val) {
    Node * currentNode, * nextNode;

     // add to empty list, or as the first item
    if (list == NULL) {
        addItem(val);
        return;
    }

    currentNode = list;
    while( currentNode != NULL ) {
        nextNode = currentNode->getNext();
        if(nextNode == NULL) {
            // we have reached the end, add to the end
            Node * n = new Node;
            n->setData( val );
            n->setNext( NULL );
            currentNode->setNext(n);
            return;
        }
    // on to the next node to check
        currentNode = nextNode;
    }
}

void Lane::numericInsert(int val) {
    Node * currentNode, * nextNode;

    // add to empty list, or as the first item
    if (list == NULL) {
        addItem(val);
        return;
    }


    // add to existing list between current and next nodes
    currentNode = list;
    while( currentNode != NULL) {
        nextNode = currentNode->getNext();

        if(nextNode == NULL) {
            // we have reached the end, add to the end
            Node * n = new Node;
            n->setData( val );
            n->setNext( NULL );
            currentNode->setNext(n);
            return;
        }
        // general case, check if we insert before nextNode
        if( val > nextNode->getData()) {
            Node * n = new Node;
            n->setData( val );
            n->setNext( nextNode );
            currentNode->setNext(n);
            return;
        }
        // on to the next node to check
        currentNode = nextNode;
     }
}

void Lane::removeFromFront( int val ){
    if( list == NULL) return;

    Node * currentNode, * nextNode;
     // is the item in front?
    if( list->getData() == val) {
        // cout << "removing " << val << " from list front" << endl;
        nextNode = list->getNext();
        delete list;
        list = nextNode;
        this->size -= 1;
        return;
    }

    // general case, find the string in the next node
    currentNode = list;
    while(currentNode != NULL) {
        nextNode=currentNode->getNext();
        if( nextNode == NULL) {
            cout << "car " << val <<" is not in the list" << endl;
            return; // item is not in the list
        }
        if( nextNode->getData() == val) {
            // hang on to the list after nextNode
            // cout << "removing " << val << " from the list" << endl;
            Node *ptr = nextNode->getNext();
            delete nextNode;
            this->size -= 1;
            // hook the old list to the last list
            currentNode->setNext(ptr);
            return;
        }
        currentNode = nextNode;
    }
}

// void Lane::removeFromEnd(int val){
//     Node * currentNode, * nextNode;
//     currentNode = list;
//     while(currentNode != NULL){
//     nextNode = currentNode->getNext();
//     if (nextNode = NULL){
//         delete currentNode;
//         this->size -= 1;
//     currentNode = nextNode;
//     }
// }
// }

int Lane::getNextInLane(int val){
    Node * currentNode, * nextNode;
    currentNode = list;
    while(currentNode != NULL){
        nextNode = currentNode->getNext();
        if (currentNode->getData() == val){
            if (nextNode != NULL){
                int n = nextNode->getData();
                return n;
            }
            else
                return -1;
        }
        currentNode = nextNode;
    }
}


void Lane::insertAfter(int first, int second){
    Node * currentNode, * nextNode;
    currentNode = list;
    while(currentNode != NULL){
        nextNode = currentNode->getNext();
        if (currentNode->getData() == first){
            Node * n = new Node;
            n->setData( second );
            n->setNext( nextNode );
            currentNode->setNext(n);
            return;
        }
        currentNode = nextNode;
    }
}

int Lane::getCarBehind(int item){
    Node * currentNode, * nextNode;
    if (list->getData() == item){
        //this car is the head, there is no car behind, return -1
        return -1;
    }
    currentNode = list;
    while(currentNode != NULL){
        nextNode = currentNode->getNext();
        if (nextNode->getData() == item){
            //current node has data for car behind, return it
            int i = currentNode->getData();
            return i;
        }
        currentNode = nextNode;
    }
}






