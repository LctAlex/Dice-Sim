#pragma once
#include <iostream>
#include <stdlib.h>
#include <limits>

#include "numbers.hpp"

void ignore_nl();

//Upper: 0 -> Aces; 1 -> Twos; 2 -> Threes; 3 -> Fours; 4 -> Fives; 5 -> Sixes
//Lower: 0 -> 3OaK; 1 -> 4OaK; 2 -> Full House; 3 -> Seq. of 4; 4 -> Seq. of 5; 5 -> YAHTZEE; 6 -> Chance
bool* new_list_vec(int size);//this vector keeps count of all used/unused scores of the upper/lower scores
void update_list_vec(bool* vec, int index);
void print_available_list(bool* vec, bool isUpper);
bool is_list_available(bool* vec, int index);
unsigned int* new_yahtz_vec(unsigned int faces, unsigned int dice);
void update_yahtz_vec(unsigned int* vec, int index, unsigned int faces);
void print_yahtz_vec(unsigned int* vec, unsigned int dice, unsigned int turn); //'turn' ~= 'rolls'
unsigned int get_sum_of(unsigned int* vec, unsigned int value, unsigned int dice);
