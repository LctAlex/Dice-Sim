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
    return min + rand() % (max - min + 1);
}

unsigned int* init_empty_vec(unsigned int size) //I should generalize this one
{
    unsigned int* finalVec = (unsigned int*)malloc(size * sizeof(unsigned int)); 
    for(int i = 0; i < size; i++)
    {
        *(finalVec + i) = 0;
    }
    return finalVec;
}

unsigned int* get_stats_vec(unsigned int faces, unsigned int dice, unsigned int rolls) //Gives a vector (size of faces), with each face (index+1) holding a value representing the number of it's appearence
{
    unsigned int* resultVec = init_empty_vec(faces);
    for(int i = 0; i < dice * rolls; i++)
    {
        unsigned int index = get_random_number(0, faces-1);
        *(resultVec + index) += 1;
    }
    return resultVec;
}//*same logic used for yahtzee*

unsigned int get_faces_vec_sum(unsigned int* statsVec, unsigned int faces)
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

unsigned int get_successes_prob(unsigned int probSum, unsigned int faces, unsigned int dice, unsigned int rolls)
{
    unsigned int tempSum = 0;
    unsigned int successes = 0;
    for(int i = 0; i < rolls; i++)
    {
        for(int j = 0; j < dice; j++)
        {
            tempSum += get_random_number(1, faces);
        }
        if(probSum == tempSum) successes++;
        tempSum = 0;
    }
    return successes;
}

long long binom(int n, int k)
{
    long long res = 1;
    for (int i = 1; i <= k; i++)
    res = res * (n - k + i) / i;
    return res;
}

float get_theoretical_prob(unsigned int faces, unsigned int dice, unsigned int probSum)
{
    long long sum = 0;
    int maxIndex = (probSum - dice) / faces;
    for(int i = 0; i <= maxIndex; i++)
    sum += ((i%2 == 0)? 1:-1) * binom(dice, i) * binom(probSum-faces*i-1, dice-1);

    return (1.f/pow(faces, dice) * sum);
}

unsigned int get_sum(unsigned int rolls, unsigned int dice, unsigned int faces)
{
    unsigned int sum = 0;
    for(int i = 0; i < dice * rolls; i++)
    {
        sum += get_random_number(1, faces);
    }
    return sum;
}