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

int main(int argc, char* argv[])
{
    unsigned int faces = DEFAULT_FACES;
    unsigned int dice = DEFAULT_DICE;
    unsigned int rolls = DEFAULT_ROLLS;
    char game[] = "stats";
    
    unsigned int probSum = 0;

    if(argc == 1)
    {
        print_help();
        return 0;
    }

    for(int i = 1; i < argc; i++)
    {
        if (strcmp(argv[i], "--.") == 0) //will go with defaults for what hasn't changed
        {
            break;
        }
        if((strcmp(argv[i], "--faces") == 0))
        {
            if(((i+1) >= argc) || (!is_number(argv[i+1]))) print_error("No valid <value> given to '--faces'", false);
            else
            {
                faces = atoi(argv[i+1]);
                i++;
            }
        }
        else if((strcmp(argv[i], "--dice") == 0))
        {
            if(((i+1) >= argc) || (!is_number(argv[i+1]))) print_error("No valid <value> given to '--dice'", false);
            else
            {
                dice = atoi(argv[i+1]);
                i++;
            }
        }
        else if((strcmp(argv[i], "--rolls") == 0))
        {
            if(((i+1) >= argc) || (!is_number(argv[i+1]))) print_error("No valid <value> given to '--rolls'", false);
            else
            {
                rolls = atoi(argv[i+1]);
                i++;
            }
        }
        else if((strcmp(argv[i], "--game") == 0))
        {
            const char* mode = "stats";
            if((i+1) >= argc) print_error("No valid <mode> given to '--game'", false);
            else mode = get_game(argv[i+1]);
            if(mode == NULL)
            {
                print_error("No valid <mode> given to --game", false); //we won't jump over the following command (thus it'll crash if it's not an arg)
            }
            else
            {
                if(strcmp(mode, "prob") == 0)
                {
                    if(!is_number(argv[i+2]))
                    {
                        print_error("No valid <value> given to '--game prob'", false);
                        continue;
                    }
                    else
                    {
                        if(atoi(argv[i+2]) <= 0)
                        {
                            print_error("In '--game prob <value>', <value> can't be <=0\n\
                                    This command returns the PROBABILITY of the SUM given as <value>\n\
                                    Try setting a <value> between [dice*rolls, faces*dice*rolls (or a high value)]", true); //SPECIAL CASE: string req met, but info are not good
                            return 0;
                        }
                        probSum = atoi(argv[i+2]);
                        i++;
                    }
                }
                strcpy(game, mode);
                i++;
            }
        }
        else if ((strcmp(argv[i], "--help") == 0) || (strcmp(argv[i], "--h") == 0))
        {
            print_help();
            return 0;
        }
        else
        {
            print_error((std::string(argv[i]) + " <- Wrong/Unrecognized command").c_str(), true);
            return 0;
        }
    }

    print_info(faces, dice, rolls, game, probSum);
    int index = find_gamemode(game);
    //const char* gameVec[5] = {"stats", "prob", "sum", "craps", "yahtzee"};
    switch(index)
    {
        case 0:
        {
            unsigned int* resultVec = get_stats_vec(faces, dice, rolls);
            std::cout << "Frequencies: \n";
            for(int i = 0; i < faces; i++)
            {
                std::cout << i+1 << ": " << *(resultVec + i) << " (" << ((float)*(resultVec + i) / (dice * rolls)) * 100.f << "%)\n";
            }
            unsigned int totalSum = get_vec_sum(resultVec, faces);
            float mean = get_mean(totalSum, dice, rolls);
            float stdDev = get_standard_deviation(resultVec, mean, faces, dice, rolls);
            std::cout << "\nMean: " << mean
                    << " (Theoretical: " << get_theoretical_mean(faces) << ")\n"
                    << "Standard deviation: " << stdDev << '\n';
            break;
        }
        case 1:
        {
            std::cout << "Neither this";
            break;
        }
        case 2:
        {
            unsigned int sum = get_sum(faces, dice, rolls);
            std::cout << "Total SUM: "<< sum << '\n';
            break;
        }
    }
       
    return 0;
}

//Unblock-File ./main.exe