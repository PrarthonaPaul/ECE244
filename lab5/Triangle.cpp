//
//  Triangle.cpp
//  Lab5
//
//  Created by Tarek Abdelrahman on 2020-11-25.
//  Copyright © 2020 Tarek Abdelrahman.
//
//  Permission is hereby granted to use this code in ECE244 at
//  the University of Toronto. It is prohibited to distribute
//  this code, either publicly or to third parties.

//  ECE244 Student: Write the implementation of the class Rectangle here

#include <iostream>
#include <string>
#include <iomanip>
using namespace std;
#include "Shape.h"
#include "Triangle.h"

Triangle::Triangle(string n, float xcent, float ycent, float a, float b, float c, float d, float e, float f):Shape(n, xcent, ycent) {
    x1 = a; 
    x2 = b; 
    x3 = c; 
    y1 = d; 
    y2 = e; 
    y3 = f; 
}

Triangle::~Triangle() {
    // Nothing to do
}

// Accessor
float Triangle::getX1() const {
    return x1;
}

float Triangle::getX2() const { 
    return x2;
}

float Triangle::getX3() const {
    return x3;
}
float Triangle::getY1() const {
    return y1;
}
float Triangle::getY2() const {
    return y2;
}
float Triangle::getY3() const {
    return y3;
}

// Mutator
void Triangle::setX1(float x) {
    x1 = x;
}

void Triangle::setX2(float x) {
    x2 = x;
}

void Triangle::setX3(float x) {
    x3 = x;
}

void Triangle::setY1(float y) {
    y1 = y;
}

void Triangle::setY2(float y) {
     y2 = y;
}

void Triangle::setY3(float y) {
    y3 = y;
}

void Triangle::draw() const{
    cout << std::fixed;
    cout << std::setprecision(2);
    
    cout << "triangle: " << name << " "
         << x_centre << " " << y_centre
         << " " << x1 << " " << y1 << " "  << x2 << " " << y2 << " "  << x3 << " " << y3 << " " << computeArea()
         << endl;
}
    
float Triangle::computeArea() const {
    float a = x1*(y2-y3); 
    float b = x2*(y3-y1); 
    float c = x3*(y1-y2); 
    float area =  (0.5*(a+b+c)); 
    if(area >= 0)
        return area; 
    return (area * (-1)); 
}  // Draws the rectangle; for the assignment it
   // prints the information of the circle
    
Shape* Triangle:: clone() const{
    return (new Triangle(*this)); 
}  // Clones the object