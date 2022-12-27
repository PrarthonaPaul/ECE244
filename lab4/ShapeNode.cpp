
#include "Shape.h"
#include "ShapeNode.h"
//
//  ShapeNode.cpp
//  Lab4
//
//  Created by Tarek Abdelrahman on 2020-10-25.
//  Copyright © 2020 Tarek Abdelrahman.
//
//  Permission is hereby granted to use this code in ECE244 at
//  the University of Toronto. It is prohibited to distribute
//  this code, either publicly or to third parties.

//  ECE244 Student:
//  Write the implementation (and only the implementation) of the ShapeNode class below
ShapeNode::ShapeNode(){                   // sets myShape and next to nullptr
    myShape = nullptr; 
    next = nullptr; 
}
ShapeNode::~ShapeNode(){                  // deletes the shape pointed to by myShape
    delete myShape; 
    myShape = nullptr; 
}
Shape* ShapeNode::getShape() const{       // returns myShape
    return myShape; 
}
void ShapeNode::setShape(Shape* ptr){     // sets myShape to ptr
//    delete myShape; 
    myShape = ptr; 
}
ShapeNode* ShapeNode::getNext() const{    // returns next
    return next; 
}
void ShapeNode::setNext(ShapeNode* ptr){  // sets next to ptr
    next = ptr; 
}
void ShapeNode::print() const{          //example: my_circle: ellipse 50 65 20 20 ; 
    myShape->draw(); 
}  

