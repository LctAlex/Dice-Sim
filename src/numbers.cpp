#include "numbers.hpp"

void update_XORshift_seed(uint32_t* seed)
{
    uint32_t x = *seed;
    x ^= x << 13;
    x ^= x >> 17;
    x ^= x << 5;
    *seed = x;
}

unsigned int get_random_number(unsigned int min, unsigned int max) //requires an already-set srand(seed)
{
    return min + (rand() % max);
}

float get_total_average(unsigned int sum, unsigned int rolls, unsigned int dice)
{
    return (float)sum / (rolls * dice);
}

float get_theoretical_average(unsigned int faces)
{
    unsigned int faceSum = 0;
    for(int i = 1; i <= faces; i++) faceSum += i;
    return (1 / (float)faces) * faceSum;
}

unsigned int get_sum(unsigned int rolls, unsigned int dice, unsigned int faces)
{
    unsigned int sum = 0;
    uint32_t seed = time(NULL);
    uint32_t* seedPtr = &seed;
    srand(seed);
    for(int i = 0; i < rolls; i++)
    {
        for(int j = 0 ; j < dice; j++)
        {
            update_XORshift_seed(seedPtr);
            srand(seed);
            sum += get_random_number(1, faces);
        }
    }
    return sum;
}