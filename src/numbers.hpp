#pragma once
#include <math.h>
#include <time.h>
#include <stdint.h> //for our large seed

void update_XORshift_seed(uint32_t* seed);
unsigned int get_random_number(unsigned int min, unsigned int max);
unsigned int* init_empty_vec(unsigned int faces);
//void sort()
//stats:
unsigned int* get_stats_vec(unsigned int faces, unsigned int dice, unsigned int rolls);
unsigned int get_vec_sum(unsigned int* statsVec, unsigned int faces);
float get_mean(unsigned int sum, unsigned int dice, unsigned int rolls);
float get_theoretical_mean(unsigned int faces);
float get_standard_deviation(unsigned int* statsVec, float mean, unsigned int faces, unsigned int dice, unsigned int rolls);
//sum:
unsigned int get_sum(unsigned int faces, unsigned int dice, unsigned int rolls); //simple, but I can get it with --game stats too