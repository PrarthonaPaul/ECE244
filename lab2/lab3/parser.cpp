//
//  parser.cpp
//  lab3
//
//  Modified by Tarek Abdelrahman on 2020-10-04.
//  Created by Tarek Abdelrahman on 2018-08-25.
//  Copyright © 2018-2020 Tarek Abdelrahman.
//
//  Permission is hereby granted to use this code in ECE244 at
//  the University of Toronto. It is prohibited to distribute
//  this code, either publicly or to third parties.


#include <iostream>
#include <sstream>
#include <string>
#include <random>

using namespace std;

#include "globals.h"
#include "Shape.h"

// This is the shape array, to be dynamically allocated
Shape** shapesArray;

// The number of shapes in the database, to be incremented 
int shapeCount = 0;

// The value of the argument to the maxShapes command
int max_shapes;
bool commandIsvalild(string); 
bool nameIsValid(string); 
bool typeIsValid(string); 
int nameSearch(string name); 
void create(stringstream &); 
void move(stringstream &); 
void rotate (stringstream &); 
void drawShape(stringstream &); 
void deleteShape(stringstream &); 
int peekCheck (stringstream & lineStream); 

// ECE244 Student: you may want to add the prototype of
// helper functions you write here

int main() {

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
        // The only way this can fail is if the eof is enshapeCountered
        lineStream >> tmp;
        if(commandIsvalild(tmp))
            command = tmp;  
        else{ 
            cout << "Error: invalid command" << endl; 
            command = ""; 
        }
                    
                
        if(command == keyWordsList[1]){ //maxshapes 
            lineStream >>  max_shapes; 
            if(!lineStream.fail()){
                if(shapeCount > 0){
                    for(int i = 0; i < shapeCount; i++ ){
                        if(shapesArray[i] != nullptr){
                            delete shapesArray[i]; 
                            shapesArray = nullptr; 
                        }
                    }
                    shapeCount = 0; 
                }
                shapesArray = new Shape*[ max_shapes]; 
                cout << "New database: max shapes is " <<  max_shapes << endl; 
            }
            else{
                //insert code about what to do 
                lineStream.clear(); 
                lineStream.ignore(1000, '\n'); 
                cout << "Error: invalid argument" << endl; 
            }                
        } 
        else if(command ==  keyWordsList[2]){   //create 
            if(shapeCount <=  max_shapes-1)
                create(lineStream); 
            else
                cout << "Error: shape array is full" << endl;
        }
        else if(command == keyWordsList[3]) {   //move 
                move(lineStream); 
        }
        else if(command == keyWordsList[4]) {   //rotate
            rotate(lineStream); 
        }
        else if(command == keyWordsList[5]){    //draw
            drawShape(lineStream);  
        }
        else if(command == keyWordsList[6]){    //delete
            deleteShape(lineStream); 
        }
        
        // Check for the command and act accordingly
        // ECE244 Student: Insert your code here     
        // Once the command has been processed, prompt for the0
        // next command
        cout << "> ";          // Prompt for input
        
        
        getline(cin, line);
        
    }  // End input loop until EOF.
    
    return 0;
}

//checks the value for the command and matches it with the acceptable set of commands and return s true if there is a match
bool commandIsvalild(string command){

    for(int i = 1; i < 7; i++){
        if(keyWordsList[i] == command)
            return 1;  
    }
    return 0;
}

void create(stringstream & lineStream){
    string name, type, extras; 
    int loc1, loc2, size1, size2, i = 0; 
    
    while(!lineStream.eof() && !lineStream.fail()){
        switch(i){
            case 0:
                lineStream >> name; 
                if(!nameIsValid(name)){
                    cout << "Error: invalid shape name" << endl; 
                    return; 
                }
                break; 
            case 1:
                lineStream >> type; 
                if(!typeIsValid(type)){
                    cout << "Error: invalid shape type" << endl; 
                    return;                                                  
                } 
                else if(nameSearch(name) != -1){
                    cout << "Error: shape " << name << " exists" << endl; 
                    return;
                }
                break; 
            case 2:
                lineStream >> loc1; 
                
                if(lineStream.fail()){
                    if(lineStream.eof()){
                        cout << "Error: too few arguments" << endl; 
                        return; 
                    }
                    else{   
                        lineStream.clear(); 
                        lineStream.ignore(1000, '\n'); 
                        cout << "Error: invalid argument" << endl; 
                        return; 
                    }
                }
                else if(loc1 < 0){
                    cout << "Error: invalid value" << endl; 
                    return; 
                }
                break; 
                
            case 3:
                lineStream >> loc2; 
                if(lineStream.fail()){
                    lineStream.clear(); 
                    lineStream.ignore(1000, '\n'); 
                    cout << "Error: invalid argument" << endl; 
                    return; 
                }
                else if(loc2 < 0){
                    cout << "Error: invalid value" << endl; 
                    return; 
                }
                break; 
                
            case 4:
                lineStream >> size1; 
                  if(lineStream.fail()){
                        lineStream.clear(); 
                        lineStream.ignore(1000, '\n'); 
                        cout << "Error: invalid argument" << endl; 
                        return; 
                    }
                    else if(size1 < 0){
                        cout << "Error: invalid value" << endl; 
                        return; 
                    }
                break; 
            case 5:
                lineStream >> size2; 
                 if(lineStream.fail()){
                    lineStream.clear(); 
                    lineStream.ignore(1000, '\n'); 
                    cout << "Error: invalid argument" << endl; 
                    return; 
                }
                else if(size2 < 0){
                    cout << "Error: invalid value" << endl; 
                    return; 
                }
                if (peekCheck(lineStream) == 1) 
                    return; 
                break; 
            default:
                lineStream >> extras; //puts any extra inputs in here 
                break; 
        }
        i++; 
    }

    if(i < 6){
        cout << "Error: too few arguments" << endl; 
        return; 
    }
    else if(i > 6 && extras != "") {
        cout << "Error: too many arguments" << endl; 
        return; 
    }
    
    if(type == shapeTypesList[0]){
        if(size1 != size2) 
            cout << "Error: invalid value" << endl; 
        else {
            shapesArray[shapeCount] = new Shape(name, type, loc1, size1, loc2, size2); 
            cout << "Created " << shapesArray[shapeCount]->getName() <<": " << shapesArray[shapeCount]->getType() << " " << shapesArray[shapeCount]->getXlocation() << " " << shapesArray[shapeCount]->getYlocation() << " " << shapesArray[shapeCount]->getXsize()<< " " << shapesArray[shapeCount]->getYsize() << endl; 
            shapeCount++; 
        }
    }
    else {
            shapesArray[shapeCount] = new Shape(name, type, loc1, size1, loc2, size2); 
            cout << "Created " << shapesArray[shapeCount]->getName() << ": " << shapesArray[shapeCount]->getType() << " " << shapesArray[shapeCount]->getXlocation() << " " << shapesArray[shapeCount]->getYlocation() << " " << shapesArray[shapeCount]->getXsize()<< " " << shapesArray[shapeCount]->getYsize() << endl; 
            shapeCount++; 
    }
}

int peekCheck (stringstream & lineStream){
    if(lineStream.peek() != ' ' && lineStream.peek() != '\t' && lineStream.peek() != -1){
        cout << "Error: invalid argument" << endl; 
        return 1; 
    }
    return 0; 
}

bool nameIsValid(string name){
    bool flag = true; 
    
    for(int i = 0; i < 7; i++){
        if(keyWordsList[i] == name){
            flag = false; 
            break; 
        }
    }
    
    for(int i = 0; i < 4; i++){
        if(shapesArray[i] != nullptr && shapeTypesList[i] == name){
            flag = false; 
            break; 
        }
    }
    return flag; 
}

int nameSearch(string name){
    for(int i = 0; i < shapeCount; i++){
        if(shapesArray[i] != nullptr && name == shapesArray[i]->getName())
            return i; 
    }
    return -1; 
}

bool typeIsValid(string type){
    for(int i = 0; i < 4; i++){
        if(shapeTypesList[i] == type)
            return 1; 
    }
    return 0;
}

void move(stringstream & lineStream){
    string name, extras; 
    int loc1, loc2, i = 0, token; 
    
    while(!lineStream.eof() && !lineStream.fail()){
        switch(i){
            case 0:
                lineStream >> name; 
                token = nameSearch(name); 
                if( token == -1){
                    if(!nameIsValid(name)){
                    cout << "Error: invalid shape name" << endl; 
                    return; 
                    }
                    else{
                    cout << "Error: shape " << name << " not found" << endl; 
                    return;
                    }
                }
                break; 
            case 1:
                lineStream >> loc1; 
                
                if(lineStream.fail()){
                    if(lineStream.eof()){
                        cout << "Error: too few arguments" << endl; 
                        return; 
                    }
                    else{   
                        lineStream.clear(); 
                        lineStream.ignore(1000, '\n'); 
                        cout << "Error: invalid argument" << endl; 
                        return; 
                    }
                }
                else if(loc1 < 0){
                    cout << "Error: invalid value" << endl; 
                    return; 
                }
                break; 
                
            case 2:
                lineStream >> loc2; 
                if(lineStream.fail()){
                    lineStream.clear(); 
                    lineStream.ignore(1000, '\n'); 
                    cout << "Error: invalid argument" << endl; 
                    return; 
                }
                else if(loc2 < 0){
                    cout << "Error: invalid value" << endl; 
                    return; 
                }
                if (peekCheck(lineStream) == 1) 
                    return; 
                break; 
            default:
                lineStream >> extras; //puts any extra inputs in here 
                break; 
        }
        i++; 
    }

    if(i < 3){
        cout << "Error: too few arguments" << endl; 
        return; 
    }
    else if(i > 3 && extras != "") {
        cout << "Error: too many arguments" << endl; 
        return; 
    }
    shapesArray[token]->setXlocation(loc1); 
    shapesArray[token]->setYlocation(loc2); 
    cout << "Moved " << shapesArray[token]->getName() << " to " << shapesArray[token]->getXlocation() << " " << shapesArray[token]->getYlocation() << endl ; 
}
void rotate (stringstream & lineStream){
    string name, extras; 
    int angle, i = 0, token; 
    
    while(!lineStream.eof() && !lineStream.fail()){
        switch(i){
            case 0:
                lineStream >> name; 
                token = nameSearch(name); 
                if( token == -1 ){
                    if(!nameIsValid(name)){
                    cout << "Error: invalid shape name" << endl; 
                    return; 
                }
                break; 
            case 1:
                lineStream >> angle; 

                if(lineStream.fail()){
                    if(lineStream.eof()){
                        cout << "Error: too few arguments" << endl; 
                        return; 
                    }
                    else{   
                        lineStream.clear(); 
                        lineStream.ignore(1000, '\n'); 
                        cout << "Error: invalid argument" << endl; 
                        return; 
                    }
                }
                else if(angle < 0 || angle > 360){
                    cout << "Error: invalid value" << endl; 
                    return; 
                }
                if (peekCheck(lineStream) == 1) 
                    return; 
                break; 
            default:
                lineStream >> extras; //puts any extra inputs in here 
                break; 
        }
        i++; 
    }
    if( token == -1 && name != keyWordsList[0]){
        cout << "Error: shape " << name << " not found" << endl; 
        return;
        }
    }
    if(i < 2){
        cout << "Error: too few arguments" << endl; 
        return; 
    }
    else if(i > 2 && extras != "") {
        cout << "Error: too many arguments" << endl; 
        return; 
    }
    shapesArray[token]->setRotate(angle); 
    cout << "Rotated " << shapesArray[token]->getName() << " by " << angle << " degrees" << endl ; 
} 
void drawShape(stringstream & lineStream){
    string name, extras; 
    int i = 0, token; 
    
    while(!lineStream.eof() && !lineStream.fail()){
        switch(i){
            case 0:
                lineStream >> name; 
                token = nameSearch(name); 
                if( token == -1 && name != keyWordsList[0]){
                    if(!nameIsValid(name)){
                        cout << "Error: invalid shape name" << endl; 
                        return; 
                    }
                    else{   
                    cout << "Error: shape " << name << " not found" << endl; 
                    return;
                    }
                }
                if (peekCheck(lineStream) == 1) 
                    return; 
                break;  
            default:
                lineStream >> extras; //puts any extra inputs in here 
            break; 
        }
        i++; 
    }

    if(i < 1){
        cout << "Error: too few arguments" << endl; 
        return; 
    }
    else if(i > 1 && extras != "") {
        cout << "Error: too many arguments" << endl; 
        return; 
    }
    
    if(name == keyWordsList[0]){
        cout << "Drew all shapes" << endl;  
        for(int i = 0; i < shapeCount; i++)
            if(shapesArray[i] != nullptr)
                shapesArray[i]->draw(); 
    }
    else{
        cout << "Drew " ; 
        shapesArray[token]->draw(); 
    }
} 

void deleteShape(stringstream & lineStream){
    string name, extras; 
    int i = 0, token; 
    
    while(!lineStream.eof() && !lineStream.fail()){
        switch(i){
            case 0:
                lineStream >> name; 
                cout << name << endl; 
                token = nameSearch(name); 
                if( token == -1 && name != keyWordsList[0]){
                    if(!nameIsValid(name)){
                    cout << "Error: invalid shape name" << endl; 
                    return; 
                    }
                }
                if (peekCheck(lineStream) == 1) 
                    return; 
                cout << peekCheck(lineStream) << endl; 
            break;  
            default:
                lineStream >> extras; //puts any extra inputs in here 
            break; 
        }
        i++; 
        cout << i << endl; 
    }
    if( token == -1 && name != keyWordsList[0] && nameIsValid(name)){
        cout << "Error: shape " << name << " not found" << endl; 
        return;
        }
    }
    if(i < 1){
        cout << "Error: too few arguments" << endl; 
        return; 
    }
    else if(i > 1 && extras != "") {
        cout << "Error: too many arguments" << endl; 
        return; 
    }
    
    if(name == keyWordsList[0]){
        cout << "Deleted: all shapes" << endl;  
        for(int i = 0; i < shapeCount; i++){
            delete shapesArray[i]; 
            shapesArray[i] = nullptr; 
        }
    }
    else{
        cout << "Deleted shape " << shapesArray[token]->getName() << endl ; 
        cout << i << endl; 
        delete shapesArray[token];
        shapesArray[token] = nullptr; 
    }
} 