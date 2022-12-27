//
//  ShapeList.cpp
//  Lab4
//
//  Created by Tarek Abdelrahman on 2020-10-25.
//  Copyright © 2020 Tarek Abdelrahman.
//
//  Permission is hereby granted to use this code in ECE244 at
//  the University of Toronto. It is prohibited to distribute
//  this code, either publicly or to third parties.

//  ECE244 Student:
//  Write the implementation (and only the implementation) of the ShapeList class below
#include "ShapeList.h"

ShapeList::ShapeList(){                        // sets head to nullptr
    head = nullptr; 
}
ShapeList::~ShapeList(){                       // deletes all list nodes starting with head plus associated Shapes
    ShapeNode *tptr; 
    //headptr = head; 
    while(head != nullptr){
        tptr = head; 
        head = head->getNext(); 
        delete tptr; 
        tptr = nullptr; 
    } 
}
ShapeNode* ShapeList::getHead() const{         // returns the head pointer
    return head; 
}
void ShapeList::setHead(ShapeNode* ptr){       // sets the head pointer to ptr
    head = ptr; 
}
ShapeNode* ShapeList::find(string name) const{ // finds a shape node with the specified shape name returns a pointer to the node if found, otherwise returns nullptr if the node is not found
    ShapeNode *currShape; 
    
    if(head == nullptr)
        return head; 
    currShape = head; 

    while (currShape->getNext() != nullptr){
        if(currShape->getShape()->getName() == name){
            return currShape;
            //break;
        }
        currShape = currShape->getNext(); 
    }
    if(currShape->getShape()->getName() == name)
        return currShape;
    return nullptr;                                 
}

void ShapeList::insert(ShapeNode* s){
    ShapeNode *next; 
    next = head; 
    if(next == nullptr){
        head = s; 
        head->setNext(nullptr); 
    }
    else{
        while(next->getNext() != nullptr){
            next = next->getNext(); 
        }
        next->setNext(s); 
        next->getNext()->setNext(nullptr); 
        
    }
    
}          // inserts the node pointed to by s at the end of the list; s should never be nullptr
ShapeNode* ShapeList::remove(string name){
    ShapeNode *node = head; 
    ShapeNode *pptr = head; 
    if(head == nullptr)
        return head; 
    if(node->getShape()->getName() == name){
        head = head->getNext(); 
        return node; 
    }
    while(node != nullptr){
//        Shape *ptr = node->getShape(); 
        if(node->getShape()->getName() == name){
            break; 
        }
        pptr = node; 
        if(node != nullptr)
            node = node->getNext(); 
    }
    if(node == nullptr)
        return nullptr; 
    if(node == head){
        head = head->getNext(); 
        return node; 
    }
    pptr->setNext(node->getNext()); 
    node->setNext(nullptr); 
    return node; 
}     // removes the node with the shape called name returns a pointer to the removed node or nullptr is a node with name does not exist 

void ShapeList::print() const{
    ShapeNode *tptr = head; 
    if(tptr == nullptr)
        return; 
    else{
        while(tptr->getNext() != nullptr){
            tptr->print(); 
            tptr = tptr->getNext(); 
        }
        tptr->print(); 
    }
}                 // prints the list

