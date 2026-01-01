#pragma once
#include <math.h>
#include <time.h>
#include <stdint.h> //for our large seed

uint32_t get_XORshift_seed();
void update_XORshift_seed(uint32_t* seed);
void get_sum(unsigned int rolls, unsigned int dice, uint32_t* seed);