//
//  GroupList.cpp
//  Lab4
//
//  Created by Tarek Abdelrahman on 2020-10-25.
//  Copyright © 2020 Tarek Abdelrahman.
//
//  Permission is hereby granted to use this code in ECE244 at
//  the University of Toronto. It is prohibited to distribute
//  this code, either publicly or to third parties.

//  ECE244 Student:
//  Write the implementation (and only the implementation) of the GroupList class below
#include <string>
#include "Shape.h"
#include "GroupNode.h"
#include "GroupList.h"
using namespace std;

GroupList::GroupList(){
    head = nullptr; 
}                      
GroupList::~GroupList(){
    GroupNode * tptr; 
    while(head != nullptr){
        tptr = head; 
        head = head->getNext(); 
        delete tptr; 
        tptr = nullptr; 
    }
}                     
    
GroupNode* GroupList::getHead() const{
    return head; 
}       
void GroupList::setHead(GroupNode* ptr){
    head = ptr; 
}     
void GroupList::insert(GroupNode* s){
    GroupNode * tptr = head; 
    if(tptr == nullptr){
        head = s; 
        s->setNext(nullptr); 
    }
    else{
        while(tptr->getNext() != nullptr){
            tptr = tptr->getNext(); 
        }
        tptr->setNext(s);  
        s->setNext(nullptr); 

    }
}   

GroupNode* GroupList::remove(string name){
    GroupNode * tptr = head;
    GroupNode *pptr = head; 
    if(head == nullptr)
        return head; 
    if(tptr->getName() == name){
        head = head->getNext(); 
        return tptr; 
    }
    
    while(tptr != nullptr){
        if(tptr->getName() == name){
            break; 
        }
        pptr = tptr; 
        if(tptr != nullptr)
            tptr = tptr->getNext();  
    }
    if(tptr == NULL) 
        return NULL;
    if(tptr == head) {
        head = head->getNext();
        return tptr;
    }
    pptr->setNext(tptr->getNext()); 
    tptr->setNext(nullptr); 
    return tptr; 
}
                                      
void GroupList::print() const{
    GroupNode *tptr = head; 
    if(tptr == nullptr)
        return; 
    else{
        while(tptr->getNext() != nullptr){
            tptr->print(); 
            tptr = tptr->getNext(); 
        }
        tptr->print(); 
    }
}


