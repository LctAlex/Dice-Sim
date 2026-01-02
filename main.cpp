#include <iostream>
#include <string>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>

#include "numbers.hpp"
#include "utils.hpp"

#define DEFAULT_FACES 6
#define DEFAULT_DICE 2
#define DEFAULT_ROLLS 100

void print_stats(){};
void print_prob(){};
void print_sum(unsigned int sum){};


int main(int argc, char* argv[])
{
    int probability = 0;

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
                continue;
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
                continue;
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
                continue;
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
                continue;
            }
            else
            {
                if(strcmp(mode, "prob") == 0)
                {
                    if(!is_number(argv[i+2]))
                    {
                        print_error("No valid value given to '--game prob'", false);
                        continue;
                    }
                    else
                    {
                        probability = atoi(argv[i+2]);
                        i++;
                    }
                }
                strcpy(game, mode);
                std::cout << "Probability: " << probability << std::endl;
                i++;
            }
        }
        else
        {
            print_error((std::string(argv[i]) + " <- Wrong/Unrecognized command").c_str(), true);
            return 0;
        }
    }

    std::cout << "Faces: " << faces << '\n'
            << "Dice: " << dice << '\n'
            << "Rolls: " << rolls << '\n'
            << "Game: " << game << '\n'
            << "\n\nRolling dice...\n\n";

    int index = find_gamemode(game);
    //std::cout << "Game " << index << " is active...\n";
    switch(index)
    {
        case 0:
        {
            std::cout << "Should see this";
            break;
        }
        case 1:
        {
            std::cout << "Neither this";
            break;
        }
        case 2:
        {
            unsigned int sum = get_sum(dice, rolls, faces);
            std::cout << "Total sum: "<< sum << std::endl
                    << "Total average: " << (float)sum /(dice*rolls) << std::endl;
            break;
        }
    }
       
    return 0;
}

//Unblock-File .\main.exe