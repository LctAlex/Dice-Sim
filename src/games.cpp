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

void craps_loop()
{
    //I'll just make the main 3 vectors beforehand (to avoid reinitialization);
    unsigned int* mainVec1 = make_vec(2, 7,11);
    unsigned int* mainVec2 = make_vec(3, 2,3,12);
    unsigned int* mainVec3 = make_vec(6, 4,5,6,8,9,10);
    unsigned int* fieldVec = make_vec(7 ,2,3,4,9,10,11,12);

    bool loop = true;
    int opt;
    while(loop)
    {
        std::cout << "\nChoose game:\n"
                << "0. Stop betting\n"
                << "1. Pass Line\n"
                << "2. Don't Pass Bar\n"
                << "3. Field Bet\n"
                << "4. Dealer Bets\n"
                << ">_: ";
        std::cin >> opt;
        ignore_nl();
        switch(opt)
        {
            case 0: 
            {
                std::cout << "\nExiting bets...\n";
                loop = false;
                break;
            }
            case 1:
            {
                bool reroll = true;
                while(reroll)
                {
                    reroll = false;
                    print_values(mainVec1, 2, "\nWinning values: ");
                    print_values(mainVec2, 3, "Losing values: ");
                    unsigned int res = roll_2dice();
                    if(is_num_in_vec(res, 2, mainVec1)) std::cout << "You WIN!";
                    else if(is_num_in_vec(res, 3, mainVec2)) std::cout << "You LOSE!";
                    else
                    {
                        std::cout << "\nYou have to REROLL\n";
                        reroll = true;
                    }

                    std::cin.ignore();//just design
                }
                break;
            }
            case 2:
            {
                bool reroll = true;
                while(reroll)
                {
                    reroll = false;
                    print_values(mainVec2, 3, "\nWinning values: ");
                    print_values(mainVec1, 2, "Losing values: ");
                    unsigned int res = roll_2dice();
                    if(is_num_in_vec(res, 3, mainVec2)) std::cout << "You WIN!";
                    else if(is_num_in_vec(res, 2, mainVec1)) std::cout << "You LOSE!";
                    else
                    {
                        std::cout << "\nYou have to REROLL\n";
                        reroll = true;
                    }

                    std::cin.ignore();
                }
                break;
            }
            case 3:
            {
                std::cout << "You only have ONE roll!\n\n";
                print_values(fieldVec, 7, "\nWinning values: ");
                std::cout << "Losing values: 5 6 7 8\n"; //I am NOT making a whole vector just for this!!!
                unsigned int res = roll_2dice();
                if(is_num_in_vec(res, 7, fieldVec)) std::cout << "You WIN!";
                else std::cout << "You LOSE!";

                std::cin.ignore();
                break;
            }
            case 4:
            {
                int choice;
                std::cout << "\nChoose a bet type:\n"
                        << "0. Go back\n"
                        << "1. Place Bet (Small win)\n"
                        << "2. Lay Bet (Big win)\n"
                        << "3. Special bet\n"
                        << ">_: ";
                std::cin >> choice;
                ignore_nl();
                switch(choice)
                {
                    case 0: break;
                    case 1:
                    {
                        print_values(mainVec3, 6, "\nWinning values: ");
                        std::cout << "Losing value: 7\n";
                        unsigned int res = roll_2dice();
                        if(res == 7) std::cout << "You LOSE!";
                        else std::cout << "You WIN!";

                        std::cin.ignore();
                        break;
                    }
                    case 2:
                    {
                        std::cout << "Winning value: 7\n";
                        print_values(mainVec3, 6, "Losing values: ");
                        unsigned int res = roll_2dice();
                        if(res == 7) std::cout << "You WIN!";
                        else std::cout << "You LOSE!";

                        std::cin.ignore();
                        break;
                    }
                    case 3:
                    {
                        unsigned int num;
                        std::cout << "You only have ONE roll!\n"
                                << "Bet your number: ";
                        std::cin >> num;
                        ignore_nl();
                        if(num < 2 || num > 12)
                        {
                            std::cout << num << " is out of bounds!\n"
                                    << "Try adding a number between 2 and 12\n";
                        }
                        unsigned int res = roll_2dice();
                        if(res == num) std::cout << "YOU WIN!!!";
                        else std::cout << "You LOSE...";
                        
                        std::cin.ignore();
                        break;
                    }
                    default:
                    {
                        std::cout << "Invalid option!\n";
                        break;
                    }
                }
                break;
            }
            default:
            {
                std::cout << "Invalid option!\n";
                break;
            }
        }
    }
    free(mainVec1);
    free(mainVec2);
    free(mainVec3);
    free(fieldVec);
}

void print_craps_rules()
{
    std::cout << "RULES:\n\
============================\n\
-Pass Line:\n\
    -Win: 7 or 11\n\
    -Lose: 2,3 or 12\n\
    -Reroll: 4,5,6,8,9,10\n\
\
-Don't Pass Bar: (opposite of Pass Line)\n\
    -Win: 2,3 or 12\n\
    -Lose 7 or 11\n\
    -Reroll(same as Pass Line)\n\
\
-Field Bet(one roll bet):\n\
    -Win: 2,3,4,9,10,11,12\n\
    -Lose: 5,6,7,8\n\
\
-Dealer Bets:\n\
    -Place Bet:\n\
        -Win: 4,5,6,8,9,10\n\
        -Lose: 7\n\
    -Lay Bet:\n\
        -Win: 7\n\
        -Lose: 4,5,6,8,9,10\n\
============================\n";
}

unsigned int roll_2dice()
{
    unsigned int dice1, dice2;
    std::cout << "\nPress ENTER to roll dice!";
    std::cin.ignore();
    dice1 = get_random_number(1, 6);
    dice2 = get_random_number(1, 6);
    std::cout << "======\nYou ROLLED: " << dice1 << " and " << dice2 << "\n======\n";
    return dice1 + dice2;
}

unsigned int* make_vec(int size, ...)
{
    unsigned int* vec = (unsigned int*)malloc(size * sizeof(unsigned int));
    va_list args;
    va_start(args, size);
    for(int i = 0; i < size; i++)
    {
        *(vec+i) = va_arg(args, unsigned int);
    }
    va_end(args);
    return vec;
}

bool is_num_in_vec(unsigned int num, int size, unsigned int* vec)
{
    for(int i = 0; i < size; i++)
    {
        if(num == *(vec+i)) return true;
    }
    return false;
}

void print_values(unsigned int* vec, int size, const char* text) //Print values with a text first
{
    std::cout << text;
    for(int i = 0; i < size; i++)
    {
        std::cout << *(vec+i) << ' ';
    }
    std::cout << std::endl;
}