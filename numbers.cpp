#include "numbers.hpp"

uint32_t get_XORshift_seed()
{
    uint32_t seed = time(NULL);
    seed ^= seed >> 17;
    seed ^= seed << 21;
    seed ^= seed >> 13;
    return seed;
}
void update_XORshift_seed(uint32_t* seed)
{
    uint32_t x = *seed;
    x ^= x << 13;
    x ^= x >> 17;
    x ^= x << 5;
    *seed = x;
}