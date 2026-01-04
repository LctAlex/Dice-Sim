#include "numbers.hpp"

void update_XORshift_seed(uint32_t* seed) //I don't really need to use a pointer
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

unsigned int* init_empty_vec(unsigned int faces) //I should generalize this one
{
    unsigned int* finalVec = (unsigned int*)malloc(faces * sizeof(unsigned int)); 
    for(int i = 0; i < faces; i++)
    {
        *(finalVec + i) = 0;
    }
    return finalVec;
}

unsigned int* get_stats_vec(unsigned int faces, unsigned int dice, unsigned int rolls) //Gives a vector (size of faces), with each face (index+1) holding a value representing the number of it's appearence
{
    uint32_t seed = time(NULL);
    uint32_t* seedPtr = &seed; 
    update_XORshift_seed(seedPtr);
    srand(seed);
    unsigned int* resultVec = init_empty_vec(faces);
    for(int i = 0; i < rolls; i++)
    {
        for(int j = 0 ; j < dice; j++)
        {
            unsigned int index = get_random_number(0, faces);
            *(resultVec + index) += 1;
        }
    }
    return resultVec;
}

unsigned int get_vec_sum(unsigned int* statsVec, unsigned int faces)
{
    unsigned int sum = 0;
    for(int i = 0; i < faces; i++)
    {
        sum += (i+1) * (*(statsVec + i)); //face * appearence
    }
    return sum;
}

float get_mean(unsigned int sum, unsigned int rolls, unsigned int dice)
{
    return (float)sum / (rolls * dice);
}

float get_theoretical_mean(unsigned int faces)
{
    unsigned int faceSum = 0;
    for(int i = 1; i <= faces; i++) faceSum += i;
    return (1 / (float)faces) * faceSum;
}

float get_standard_deviation(unsigned int* statsVec, float mean, unsigned int faces, unsigned int dice, unsigned int rolls)
{
    float devSum = 0;
    for(int i = 0; i < faces; i++)
    {
        devSum += pow((i+1)-mean, 2) * *(statsVec + i);
    }
    return sqrt(devSum/(dice*rolls));
}

unsigned int get_sum(unsigned int rolls, unsigned int dice, unsigned int faces)
{
    unsigned int sum = 0;
    uint32_t seed = time(NULL);
    uint32_t* seedPtr = &seed;
    update_XORshift_seed(seedPtr);
    srand(seed);
    for(int i = 0; i < rolls; i++)
    {
        for(int j = 0 ; j < dice; j++)
        {
            sum += get_random_number(1, faces);
        }
    }
    return sum;
}