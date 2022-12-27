//
//  Triangle.h
//  Lab5
//
//  Created by Tarek Abdelrahman on 2020-11-25.
//  Copyright © 2020 Tarek Abdelrahman.
//
//  Permission is hereby granted to use this code in ECE244 at
//  the University of Toronto. It is prohibited to distribute
//  this code, either publicly or to third parties.

#ifndef Triangle_h
#define Triangle_h

#include <iostream>
#include <string>
using namespace std;

#include "Shape.h"
#include "Circle.h"

// This class implements the triangle Shape objects.
// ECE244 Student: Write the definition of the class here.

class Triangle : Shape {
private: 
    float x1; 
    float x2; 
    float x3; 
    float y1; 
    float y2;
    float y3;

public: 
    //constructor
    Triangle(string n, float xcent, float ycent, float a, float b, float c, float d, float e, float f); 
    virtual ~Triangle(); 
    
    float getX1() const; 
    
    float getX2() const; 
    
    float getX3() const; 
    
    float getY1() const; 
    
    float getY2() const; 
    
    float getY3() const; 
    
    void setX1(float x); 
    
    void setX2(float x); 
    
    void setX3(float x); 
    
    void setY1(float y); 
    
    void setY2(float y); 
    
    void setY3(float y);
    
    virtual void draw() const; 
    
    virtual float computeArea() const;  // Draws the rectangle; for the assignment it
                                   // prints the information of the circle
    
    virtual Shape* clone() const;  // Clones the object

}; 

#endif /* Triangle_h */


