#pragma once
#include <iostream>
#include <fstream> //for balance $$$
#include <limits> //for ignore_nl();
#include <stdlib.h>
#include <stdarg.h> //for make_vec()

#include "numbers.hpp"

void ignore_nl();
void insertion_sort(unsigned int* vec, unsigned int size);

void yahtzee_loop(unsigned int faces, unsigned int dice, unsigned int rolls);
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
unsigned int get_yahtz_vec_sum(unsigned int* vec, unsigned int dice);
bool check_reps(unsigned int* vec, unsigned int dice, int reps);
bool check_seq(unsigned int* vec, unsigned int dice, int seq);
bool check_fh(unsigned int *vec); //hardcode the length of the vector with 5

void craps_loop(); //hardcoded faces(6) and dice(2)
void print_craps_rules();
unsigned int roll_2dice();
unsigned int* make_vec(int size, ...); //It's costy to keep making a vector every time but it has to be done...
bool is_num_in_vec(unsigned int num, int size, unsigned int* vec);
void print_values(unsigned int* vec, int size, const char* text);

int read_balance(const char* fileName);
void write_balance(const char* fileName, int number);
unsigned int take_from_balance(const char* fileName, unsigned int minus);
void add_to_balance(const char* fileName, unsigned int plus);