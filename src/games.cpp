#include "games.hpp"

void ignore_nl()
{
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}
//{8,5,6,3,1,2,9}
void insertion_sort(unsigned int* vec, unsigned int size)
{
    for(int i = 1; i < size; i++)
    {
        int key = *(vec+i);
        int j = i-1;
        while(j >= 0 && *(vec+j) > key)
        {
            *(vec+j+1) = *(vec+j);
            j--;
        }
        *(vec+j+1) = key;
    }

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
        if(isUpper)
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
        else
        {
            if(is_list_available(vec, i))
            {
                std::string str;
                switch(i+1)
                {
                    case 1: str = "3 of a Kind"; break;
                    case 2: str = "4 of a Kind"; break;
                    case 3: str = "Full House"; break;
                    case 4: str = "Small Straight (of 4)"; break;
                    case 5: str = "Large Straight (of 5)"; break;
                    case 6: str = "YAHTZEE"; break;
                    case 7: str = "Chance (add all dice)"; break;
                }
                std::cout << i+1 << ". " + str + '\n';
            }
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
    std::cout <<"==================\nTurn " << 14 - turn << " (out of 13): ";
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

unsigned int get_yahtz_vec_sum(unsigned int* vec, unsigned int dice)
{
    unsigned int sum = 0;
    for(int i = 0; i < dice; i++)
    {
        sum += *(vec+i);
    }
    return sum;
}

bool check_reps(unsigned int* vec, unsigned int dice, int reps) //requires a sorted vector
{
    int repSum = 0;
    for(int i = 1; i < dice; i++)
    {
        if(*(vec+i) == *(vec+i-1)) repSum++;
        else repSum = 0;

        if(repSum == reps - 1) return true; 
    }
    return false;
}

bool check_seq(unsigned int* vec, unsigned int dice, int seq) //requires a sorted vector
{
    int seqSum = 0;
    for(int i = 1; i < dice; i++)
    {
        //if current==previous+1 => seqSum increments
        if(*(vec+i) == *(vec+i-1)+1) seqSum++;
        else if(*(vec+i) == *(vec+i-1)) continue;
        else seqSum = 0;

        if(seqSum == seq-1) return true;
    }
    return false;
}

//How I'll check for a Full House:
//make sure it's not a yahtzee (even tho it would not benefit the player)
//check for reps of 2 AND 3
bool check_fh(unsigned int *vec) //requires a sorted vector
{
    if(check_reps(vec, 5, 5))
    {
        std::cout << "This is a YAHTZEE, not a Full House!\n";
    }
    else if(check_reps(vec, 5, 2) && check_reps(vec, 5, 3)) return true;
    
    return false;
}//surprisingly simple haha!