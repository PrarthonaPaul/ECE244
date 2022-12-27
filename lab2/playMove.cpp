//
//  playMove.cpp
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
//  ECE244 Student: write your code for playMove in this file

#include "globals.h"
#include "GameState.h"

void playMove(GameState& game_state) {
    int row = game_state.get_selectedRow(); 
    int col = game_state.get_selectedColumn(); 
    int value = game_state.get_gameBoard(row, col); //this is the value that gets sent to the set_gameBoard function to edit the game board
    bool turn, valid, game_Over; 
    int win_code; 
    turn = game_state.get_turn();  
    game_state.set_moveValid(true); 
    
    if(value == Empty ){
//        valid = game_state.get_moveValid();
//        game_state.set_moveValid(valid); 
        if(turn){
            game_state.set_gameBoard(row, col, X); 
            game_state.set_turn(false); 
        }
        else{
            game_state.set_gameBoard(row, col, O); 
            game_state.set_turn(true); 
        }
        
//        int occupancy; 
//        for(int i = 0; i < boardSize; i++){
//            for(int j = 0; j< boardSize; j++){
//                if(game_state.get_gameBoard(i, j) != Empty)
//                    occupancy++; 
//            }
//        }
        win_code = game_state.get_winCode(); 
        game_Over = game_state.get_gameOver(); 
        
//        if(win_code == 0)
//            game_state.set_gameOver(false); 
//        else
//            game_state.set_gameOver(true); 
    }
    else
        game_state.set_moveValid(false); 

}