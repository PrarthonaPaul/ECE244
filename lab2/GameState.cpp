//
//  GameState.cpp
//  TicTacToe
//
//  Created by Tarek Abdelrahman on 2019-06-07.
//  Modified by Tarek Abdelrahman on 2020-09-17.
//  Copyright © 2019-2020 Tarek Abdelrahman. All rights reserved.
//
//  Permission is hereby granted to use this code in ECE244 at
//  the University of Toronto. It is prohibited to distribute
//  this code, either publicly or to third parties.
//

#include "globals.h"
#include "GameState.h"
#include <iostream>
using namespace std; 

// ECE244 Student: add you code below

GameState:: GameState(){
    selectedRow = 0; 
    selectedColumn = 0; 
    moveValid = true; 
    gameOver = false; 
    winCode = 0; 
    turn = true; 
    for(int i; i < boardSize; i++){
        for(int j; j < boardSize; j++){
            gameBoard[i][j] = Empty; 
        }
    }
}

// Return the selected row (in the range 0..boardSize-1)
int GameState:: get_selectedRow(){
    if(selectedRow >= 0 && selectedRow < 3) 
        return selectedRow; 
    return 0; 
}

// Return the selected column (in the range 0..boardSize-1)
int GameState:: get_selectedColumn(){
    if(selectedColumn >= 0 && selectedColumn < 3) 
        return selectedColumn; 
    return 0; 
}  

// Set the selected row to value in the range (in the range 0..boardSize-1)
// An out of range value is ignored and the function just returns
void GameState:: set_selectedRow(int value){
    selectedRow = value; 
}     

// Set the selected column in the range (in the range 0..boardSize-1)
// An out of range value is ignored and the function just returns
void GameState:: set_selectedColumn(int value){
    selectedColumn = value; 
}  

// Get the moveValid value
bool GameState:: get_moveValid(){
    return moveValid; 
}

// Set the moveValid variable to value
void GameState:: set_moveValid(bool value){
    moveValid = value; 
}

// Get the gameOver value
bool GameState:: get_gameOver(){
    int i = 0; 
    int count = 0; 
    if(winCode != 0)
        gameOver = true; 
    else {
        while(!gameOver && i < 3){
            for(int j = 0; j< 3; j++){
                if(gameBoard[i][j] != Empty)
                    count++; 
            }
            i++; 
        }
        if(count == 9)
            gameOver = true; 
    }
    return gameOver; 
}

// Set the gameOver variable to value
void GameState:: set_gameOver(bool value){
    gameOver = value; 
}

//assesses the board and determines the winCode 
int GameState:: get_winCode(){
    if(gameBoard[0][0] == gameBoard[0][1] && gameBoard[0][0] == gameBoard[0][2] && gameBoard[0][0] != Empty)
        winCode = 1; 
    else if(gameBoard[1][0] == gameBoard[1][1] && gameBoard[1][0] == gameBoard[1][2] && gameBoard[1][0] != Empty)
        winCode = 2; 
    else if(gameBoard[2][0] == gameBoard[2][1] && gameBoard[2][0] == gameBoard[2][2] && gameBoard[2][0] != Empty)
        winCode = 3; 
    else if(gameBoard[0][0] == gameBoard[1][0] && gameBoard[0][0] == gameBoard[2][0] && gameBoard[0][0] != Empty)
        winCode = 4; 
    else if(gameBoard[0][1] == gameBoard[1][1] && gameBoard[0][1] == gameBoard[2][1] && gameBoard[0][1] != Empty)
        winCode = 5; 
    else if(gameBoard[0][2] == gameBoard[1][2] && gameBoard[0][2] == gameBoard[2][2] && gameBoard[0][2] != Empty)
        winCode = 6; 
    else if(gameBoard[0][0] == gameBoard[1][1] && gameBoard[0][0] == gameBoard[2][2] && gameBoard[0][0] != Empty)
        winCode = 7; 
    else if(gameBoard[0][2] == gameBoard[1][1] && gameBoard[0][2] == gameBoard[2][0] && gameBoard[2][0] != Empty)
        winCode = 8; 
    else 
        winCode = 0; 
    
    return winCode; 
}

void GameState:: set_winCode(int value){
    winCode = value; 
}

bool GameState:: get_turn(){
//    if (moveValid)
//        turn = !turn; 
    return turn; 
}
    
void GameState:: set_turn(bool value){
    turn = value; 
}

// void GameState:: set_gameBoard(int row, int col, int value){
//     if (moveValid)
//         gameBoard[row][col] = value;
// }

// Get the game board value at the board location at row and col
// This method checks that row, col and value are in range/valid
// and if not it returns Empty
int GameState:: get_gameBoard(int row, int col){
    if (gameBoard[row][col] == Empty || gameBoard[row][col] == X || gameBoard[row][col] == O) {
        return gameBoard[row][col]; 
    }
    else 
        return Empty; 

}

// Set the game board value at the board location at row and col to value
// This method checks that row, col and value are in range/valid and if not it
// just returns
void GameState:: set_gameBoard(int row, int col, int value){
    gameBoard[row][col] = value; 

}
