//
//  GroupNode.cpp
//  Lab4
//
//  Created by Tarek Abdelrahman on 2020-10-25.
//  Copyright © 2020 Tarek Abdelrahman.
//
//  Permission is hereby granted to use this code in ECE244 at
//  the University of Toronto. It is prohibited to distribute
//  this code, either publicly or to third parties.

//  ECE244 Student:

#include "GroupNode.h"
#include "ShapeList.h"
#include <string>

//  Write the implementation (and only the implementation) of the GroupNode class below
GroupNode::GroupNode(string n){
    name = n; 
    myShapeList = new ShapeList(); 
    next = nullptr; 
}

// sets group name to n and makes myShapeList point to a new ShapeList; sets next to nullptr
GroupNode::~GroupNode(){
    //myShapeList->remove(); 
//    ShapeNode *node = myShapeList->getHead(); 
//    ShapeNode *pptr = myShapeList->getHead(); 
//    
//    while(node != nullptr){
//        //Shape *ptr = node->getShape(); 
//        node = node->getNext(); 
//        delete pptr; 
//        pptr = node; 
//        node = node->getNext(); 
//    }
//    node = nullptr; 
//    delete pptr; 
//    pptr = nullptr; 
    if(this == NULL) return;
    delete myShapeList;
    next = nullptr; 
    
}// deletes the myShapeList list
string GroupNode::getName() const{
    return name; 
}                // returns group name
ShapeList* GroupNode::getShapeList() const{
    return myShapeList; 
}       // returns myShapeList
void GroupNode::setShapeList(ShapeList* ptr){
    myShapeList = ptr; 
}     // sets myShapeList to ptr
GroupNode* GroupNode::getNext() const{
    return next; 
}            // returns next
void GroupNode::setNext(GroupNode* ptr){
    next = ptr; 
}          // sets next to ptr
void GroupNode::print() const{
    cout << name << ":" << endl; 
    myShapeList->print(); 
}  


