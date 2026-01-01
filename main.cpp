#include <iostream>
#include <string>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>

#include "numbers.hpp"

#define DEFAULT_FACES 6
#define DEFAULT_DICE 2
#define DEFAULT_ROLLS 100
const char* gameVec[5] = {"stats", "prob", "sum", "craps", "yahtzee"};

void print_help()
{
    std::cout << "\nPlease add command arguments + values.\n"
                    << "Available arguments:\n"
                    << "'--faces <value>' (values: [6, 8, 10, 12, 20]) <- Number of faces each dice will have. (6 faces by default)\n"
                    << "'--dice <value>' (values: [1,...,MAX_INT]) <- Number of dice to roll (2 dice by default)\n"
                    << "'--rolls <value>' (values: [1,...,MAX_INT]) <- Number of rolls for each dice.\n"
                    << "'--game <mode>' (modes: ['stats', 'prob' <TAKES VALUE>, 'sum', 'craps', 'yahtzee']) <- Represents the Game Mode. ('stats' by default)\n"
                    << "Command example: ./program --dice 20 --faces 12 --game prob 7\n"
                    << "\n";
}

void print_error(const char *err, bool stop)
{
    std::cout << "\nError with reading the command. ***" << err << "***\n";
    if(stop) std::cout << "Please make sure to add arguments + values like this: '--argument <value/mode>'.\n\n";
}
        
bool is_number(const char* str)
{
    if(!str || *(str) == '\0') return false;
    for(int i = 0; *(str+i) != '\0'; i++)
    {
        if(!isdigit(*(str+i))) return false;
    }
    return true;
}

const char* get_game(const char* str)
{
    if(!str || *(str) == '\0') return NULL;
    for(int i = 0; i < sizeof(gameVec)/sizeof(gameVec[0]); i++)
    {
        if(strcmp(str, gameVec[i]) == 0) return gameVec[i];
    }
    return NULL;
}

int find_gamemode(const char* game)
{
    for(int i = 0; i < sizeof(gameVec)/sizeof(gameVec[0]); i++)
    {
        if(strcmp(gameVec[i], game) == 0) return i;
    }
    print_error("Turns out the game mode wasn't registered", false);
    return 0;
}

void print_stats(){};
void print_prob(){};
void print_sum(unsigned int sum){};


int main(int argc, char* argv[])
{
    unsigned int faces = DEFAULT_FACES;
    unsigned int dice = DEFAULT_DICE;
    unsigned int rolls = DEFAULT_ROLLS;
    char game[] = "stats";

    if(argc == 1)
    {
        print_help();
        return 0;
    }

    for(int i = 1; i < argc; i++)
    {
        if((strcmp(argv[i], "--faces") == 0))
        {
            if(((i+1) >= argc) || (!is_number(argv[i+1]))) 
            {
                print_error("No valid value given to --faces", false);
            }
            else
            {
                faces = atoi(argv[i+1]);
                i++;
            }
        }
        else if((strcmp(argv[i], "--dice") == 0))
        {
            if(((i+1) >= argc) || (!is_number(argv[i+1])))
            {
                print_error("No valid value given to --dice", false);
            }
            else
            {
                dice = atoi(argv[i+1]);
                i++;
            }
        }
        else if((strcmp(argv[i], "--rolls") == 0))
        {
            if(((i+1) >= argc) || (!is_number(argv[i+1])))
            {
                print_error("No valid value given to --rolls", false);
            }
            else
            {
                rolls = atoi(argv[i+1]);
                i++;
            }
        }
        else if((strcmp(argv[i], "--game") == 0))
        {
            const char* mode = "stats";
            if((i+1) >= argc)
            {
                print_error("No valid mode given to --game", false);
                continue;
            } 
            else mode = get_game(argv[i+1]);

            if(mode == NULL)
            {
                print_error("No valid mode given to --game", false);
            }
            else
            {
                strcpy(game, mode);
                i++;
            }
        }
        else
        {
            print_error((std::string(argv[i]) + " <- Wrong/unrecognized command").c_str(), true);
            return 0;
        }
    }

    std::cout << "Faces: " << faces << '\n'
            << "Dice: " << dice << '\n'
            << "Rolls: " << rolls << '\n'
            << "Game: " << game << '\n'
            << "\n\nRolling dice...\n\n";
    
    //Now we'll use a switch for the game-mode. To use a switch, we'll find the index of our game inside gameVec and we'll use the switch based on that index
    int index = find_gamemode(game);
    std::cout << "Game " << index << " is active...\n";
    switch(index)
    {
        case 0:
        {
            std::cout << "Shouldn't see this";
            break;
        }
        case 1:
        {
            std::cout << "Neither this";
            break;
        }
        case 2:
        {
            int sum = 0;
            uint32_t seed = get_XORshift_seed();
            uint32_t* seedPtr = &seed;
            for(int i = 0; i < rolls; i++)
            {
                for(int j = 0; j < dice; j++)
                {
                    update_XORshift_seed(seedPtr);
                    srand(seed);
                    std::cout << seed << std::endl;
                    std::cout << "random number off this: " << rand() << std::endl;
                }
            }
            break;
        }
    }
       
    return 0;
}

//Unblock-File .\main.exe