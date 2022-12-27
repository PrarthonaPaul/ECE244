//
//  parser.cpp
//  Lab4
//
//  Created by Tarek Abdelrahman on 2020-10-25.
//  Copyright © 2020 Tarek Abdelrahman.
//
//  Permission is hereby granted to use this code in ECE244 at
//  the University of Toronto. It is prohibited to distribute
//  this code, either publicly or to third parties.


#include <iostream>
#include <sstream>
#include <string>

using namespace std;

#include "globals.h"
#include "Shape.h"
#include "ShapeNode.h"
#include "GroupNode.h"
#include "ShapeList.h"
#include "GroupList.h"
bool nameIsValid(string); 
bool nameExists(string, GroupNode*); 
void create(stringstream &, GroupNode*); 
void group(string, GroupNode*); 
void drawShape(); 
void move(stringstream &, GroupNode *); 
void deleteObject(stringstream &, GroupNode *poolGroup); 
bool groupExists(string name, GroupNode * poolGroup);


// This is a pointer to the groups list
// The list itseld must be allocated
GroupList* gList;

// ECE244 Student: you may want to add the prototype of
// helper functions you write here

int main() {
    // Create the groups list
    gList = new GroupList();
    
    // Create the poo group and add it to the group list
    GroupNode* poolGroup = new GroupNode(keyWordsList[5]);
    gList->insert(poolGroup);
    
    string line;
    string command;
    string tmp; 

    cout << "> ";         // Prompt for input
    getline(cin, line);    // Get a line from standard input

    while ( !cin.eof () ) {
        // Put the line in a linestream for parsing
        // Making a new sstream for each line so flags etc. are cleared
        stringstream lineStream (line);
        
        // Read from string stream into the command
        // The only way this can fail is if the eof is encountered
        lineStream >> command;

        // Check for the command and act accordingly
        // ECE244 Student: Insert your code here
        if(command ==  keyWordsList[0]){   //shape
            create(lineStream, poolGroup); 
        }
        else if(command == keyWordsList[1]) {   //group 
            lineStream >> tmp; 
            group(tmp, poolGroup); 
        }
        else if(command == keyWordsList[2]) {   //draw
            move(lineStream, poolGroup); 
        }
        else if(command == keyWordsList[3]){    //move
            deleteObject(lineStream, poolGroup);  
        }
        else if(command == keyWordsList[4]){    //delete
            drawShape(); 
        }
        // Once the command has been processed, prompt for the
        // next command
        cout << "> ";          // Prompt for input
        getline(cin, line);
        
    }  // End input loop until EOF.
    delete gList; 
    return 0;
}

bool nameIsValid(string name){
    bool flag = true; 
    
    for(int i = 0; i < 6 ; i++){
        if(keyWordsList[i] == name){
            flag = false; 
            break; 
        }
    }
    if(flag){
        for(int i = 0; i < 3; i++){
            if(shapeTypesList[i] == name){
                flag = false; 
                break; 
            }
        }
    }
    return flag; 
}

void create(stringstream &lineStream, GroupNode *poolGroup){
    string type; 
    string name;
    Shape *ptr; 
    int locx, locy, sizex, sizey; 
    lineStream >> name; 
    lineStream >> type; 
    lineStream >> locx; 
    lineStream >> locy; 
    lineStream >> sizex; 
    lineStream >> sizey; 
    
    if (!nameIsValid(name)){
        cout << "error: invalid name" << endl; 
        return; 
    }
    else if(nameExists(name, poolGroup) || groupExists(name, poolGroup)){
        cout << "error: name " << name << " exists" << endl; 
        return; 
    }
    else{
        //Shape newShape; //create a shape
        ptr = new Shape(name, type, locx, sizex, locy, sizey); 
        ShapeNode *nodePtr = new ShapeNode; 
        nodePtr->setShape(ptr); //insert shape into shapenode
        if(poolGroup->getShapeList() == nullptr){
            ShapeList *newList = new ShapeList(); //create a new list 
            poolGroup->setShapeList(newList); //make it point to the new list
            poolGroup->setNext(nullptr); 
        }
        else{
            //ShapeList *listptr = poolGroup->getShapeList(); 
            poolGroup->getShapeList()->insert(nodePtr); 
            //poolGroup->setNext(nullptr);  
        }        //insert shapeNode at the end of ShapeList 
    }
    ptr->draw(); 
}

bool nameExists(string name, GroupNode * poolGroup){
    ShapeNode *nodePtr; 
    //GroupNode *tptr = poolGroup; 
    Shape * ptr;  
    bool flag = false; 
    if(poolGroup == nullptr){
        flag = false; 
    }
    else{
        nodePtr = poolGroup->getShapeList()->getHead(); 
        if(nodePtr == nullptr)
            flag = false; 
        else{
            while (nodePtr != nullptr)
            {
                ptr = nodePtr->getShape(); 
                if(ptr->getName() == name){
                    flag = true; 
                    nodePtr = nodePtr->getNext(); 
                }
                else
                    nodePtr = nodePtr->getNext(); 
            }
        }
    }
    return flag; 
}

bool groupExists(string name, GroupNode * poolGroup){
    GroupNode *tptr = poolGroup; 
    while (tptr != nullptr){
        if(name == tptr->getName()){
            return true; 
            tptr = tptr->getNext(); 
        }
        else
            tptr = tptr->getNext(); 
    }
    return false; 
}

void group(string name, GroupNode* poolGroup){
    if (!nameIsValid(name)){
        cout << "error: invalid name" << endl; 
        return; 
    }
    else if(nameExists(name, poolGroup) || groupExists(name, poolGroup)){
        cout << "error: name " << name << " exists" << endl; 
        return; 
    }
    else{
        GroupNode* newGroup = new GroupNode(name);
        gList->insert(newGroup);
        cout << newGroup->getName() << ": group" << endl; 
    }
}

void drawShape(){
    cout << "drawing:" << endl; 
    gList->print(); 
}

void move(stringstream & lineStream, GroupNode * poolGroup){
    GroupNode* tptr, *toPtr, *fromPtr; 
    toPtr = nullptr; 
    ShapeNode *node; 
    string name1, name2; 
    lineStream >> name1; 
    lineStream >> name2; 
    fromPtr = gList->getHead(); 
    while(fromPtr != nullptr){
        if(fromPtr->getShapeList()->find(name1) != nullptr)
            break; 
        fromPtr = fromPtr->getNext(); 
    }
    
    if(nameIsValid(name1)){
        if(nameIsValid(name2)){
            if(nameExists(name1, fromPtr)){
                if(groupExists(name2, poolGroup)){
                    node = fromPtr->getShapeList()->find(name1); 
                    tptr = gList->getHead(); 
                    while(tptr != nullptr){
                        node = tptr->getShapeList()->find(name1); 
                        if(node != nullptr)
                            break; 
                        tptr = tptr->getNext(); 
                    }
                    tptr = gList->getHead(); 

                    while(tptr != nullptr){
                        if(tptr->getName() == name2){
                            toPtr = tptr; 
                            break; 
                        }
                        tptr = tptr->getNext(); 
                    }
                } else{cout << "error: group " << name2 << " not found" << endl;  return;}
            } else{cout << "error: invalid name" << endl;  return;}
        } else{cout << "error: shape " << name1 << " not found" << endl;  return;}
    } else{cout << "error: invalid name" << endl;  return; }
    
    if(node == nullptr)
        cout << "error: shape " << name1 << " not found" << endl;
    else{
        toPtr->getShapeList()->insert(fromPtr->getShapeList()->remove(name1)); 
        cout << "moved " << name1 << " to " << name2 << endl; 
        //delete node; 
    }
}

void deleteObject(stringstream & lineStream, GroupNode *poolGroup){
    string name; 
    GroupNode *temp;  
    GroupNode *tptr = gList->getHead(); 
    ShapeNode *tempPtr, *storePtr; 
    lineStream >> name; 
    if(!nameIsValid(name)) {cout << "error: invalid name" << endl;  return; }
        
    while(tptr != nullptr){
        if(nameExists(name, tptr) || tptr->getName() == name)
            break; 
        tptr = tptr->getNext(); 
    }
    if(tptr == nullptr){
        cout << "error: shape " << name << " not found" << endl;  
        return;
    }
    else{
        if(tptr->getName() == name){
            temp = gList->remove(tptr->getName()); 
            tempPtr = temp->getShapeList()->getHead(); 
            storePtr = poolGroup->getShapeList()->getHead(); 
            while(storePtr != nullptr &&  gList->getHead()->getShapeList()->getHead() != nullptr){ 
                if(storePtr->getNext() == nullptr){
                    storePtr->setNext(tempPtr); 
                    break; 
                }
                storePtr = storePtr->getNext(); 
            }
            if( gList->getHead()->getShapeList()->getHead() == nullptr)
                poolGroup->getShapeList()->setHead(tempPtr); 
            cout << name << " : deleted" << endl; 
        }
        else{
            tptr->getShapeList()->remove(name); 
            cout << name << " : deleted" << endl; 
        }
    }
    
}