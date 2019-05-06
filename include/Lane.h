#ifndef LANE_H
#define LANE_H

#pragma once
#include "Node.h"
#include <string>
using namespace std;


class Lane {
    private: 
        int size;
        Node * list;
    public:
        // constructors
        Lane();

        // accessors
        int getSize( void );
        Node * getList( void );
        string toString( void );
        void print( void );

        // mutators
        void addItem( int item );
        void append( int item);
        void numericInsert( int item);
        void removeFromFront(int item);
        void removeFromEnd(int item);
        int getNextInLane(int item);
        void remove(int item);
        void insertAfter(int before, int after);
        int getCarBehind( int item );
};


#endif
