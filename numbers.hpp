#pragma once
#include <math.h>
#include <time.h>
#include <stdint.h> //for our large seed

void update_XORshift_seed(uint32_t* seed);
unsigned int get_random_number(unsigned int min, unsigned int max);

//MAIN functions
unsigned int get_sum(unsigned int rolls, unsigned int dice, unsigned int faces);