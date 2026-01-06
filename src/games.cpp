#include "games.hpp"

void ignore_nl()
{
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

bool* new_list_vec(int size) //note: a great game developer would store all states of the vector in a single byte (1 bool)...but I'm not that guy
{
    bool* vec = (bool*)malloc(size*sizeof(bool));
    for(int i = 0; i < size; i++) *(vec+i) = true;
    return vec;
}

void update_list_vec(bool* vec, int index)
{
    *(vec+index) = false;
}

void print_available_list(bool* vec, bool isUpper)
{
    int size = (isUpper) ? 6 : 7;
    std::cout << "\nChoose how to score:\n"
            << "(0. Go back)\n";
    for(int i = 0; i < size; i++)
    {
        if(is_list_available(vec, i))
        {
            std::string str = "Add ";
            switch(i+1)
            {
                case 1: str += "Aces"; break;
                case 2: str += "Twos"; break;
                case 3: str += "Threes"; break;
                case 4: str += "Fours"; break;
                case 5: str += "Fives"; break;
                case 6: str += "Sixes"; break;
            }
            std::cout << i+1 << ". " + str + '\n';
        }
    }
    std::cout << ">_: ";
}

bool is_list_available(bool* vec, int index)
{
    return *(vec + index);
}

unsigned int* new_yahtz_vec(unsigned int faces, unsigned int dice)
{
    unsigned int* valVec = (unsigned int*)malloc(dice*sizeof(unsigned int));
    for(int i = 0; i < dice; i++)
    {
        *(valVec+i) = get_random_number(1, 6);
    }
    return valVec;
}

void update_yahtz_vec(unsigned int* vec, int index, unsigned int faces)
{
    *(vec+index) = get_random_number(1, faces);
}

void print_yahtz_vec(unsigned int* vec, unsigned dice, unsigned int turn)
{
    std::cout <<"\nTurn " << 14 - turn << " (out of 13): ";
    for(int i = 0; i < dice; i++)
    {
        std::cout << *(vec+i) << ' ';
    }
    std::cout << std::endl;
}

unsigned int get_sum_of(unsigned int* vec, unsigned int value, unsigned int dice)
{
    unsigned int sum = 0;
    for(int i = 0; i < dice; i++)
    {
        if(*(vec+i) == value) sum += value;
    }
    return sum;
}