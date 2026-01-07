#include <iostream>
#include <string>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>

#include "numbers.hpp"
#include "utils.hpp"
#include "games.hpp"

#define DEFAULT_FACES 6
#define DEFAULT_DICE 2
#define DEFAULT_ROLLS 100

int main(int argc, char* argv[])
{
    unsigned int faces = DEFAULT_FACES;
    unsigned int dice = DEFAULT_DICE;
    unsigned int rolls = DEFAULT_ROLLS;
    char game[] = "stats";
    
    uint32_t seed = 0;
    unsigned int probSum = 0;

    if(argc == 1)
    {
        print_help();
        return 0;
    }

    for(int i = 1; i < argc; i++)
    {
        if (strcmp(argv[i], "--.") == 0) //will go with defaults (for what hasn't changed)
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
        else if ((strcmp(argv[i], "--seed") == 0))
        {
            if(((i+1) >= argc) || (!is_number(argv[i+1]))) print_error("No valid <value> given to '--seed'", false);
            else
            {
                seed = atol(argv[i+1]);
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

    if(strcmp(game, "craps") == 0)
    {}
    if(strcmp(game, "yahtzee") == 0)
    {
        dice = 5;
        faces = 6;
        rolls = 13;
    }

    if(!seed)
    {
        seed = time(NULL);
        uint32_t *seedPtr = &seed;
        update_XORshift_seed(seedPtr); //for randomizing the seed
        srand(seed);
    }

    //const char* gameVec[5] = {"stats", "prob", "sum", "craps", "yahtzee"};
    int index = find_gamemode(game);
    if (index > 2) std::cout << "\nAny modifications to '--faces', '--dice' or '--rolls' will be overwritten-\n"
                            << "because of the '" << game << "' Game Mode.\n";
    print_info(faces, dice, rolls, game, probSum, seed);

    switch(index)
    {
        case 0:
        {
            unsigned int* resultVec = get_stats_vec(faces, dice, rolls);
            std::cout << "Frequencies: \n";
            for(int i = 0; i < faces; i++)
            {
                std::cout << i+1 << ": " 
                        << *(resultVec + i) 
                        << " (" << ((float)*(resultVec + i) / (dice * rolls)) * 100.f << "%)\n";
            }
            unsigned int totalSum = get_vec_sum(resultVec, faces);
            float mean = get_mean(totalSum, dice, rolls);
            float stdDev = get_standard_deviation(resultVec, mean, faces, dice, rolls);
            std::cout << "\nMean: " << mean
                    << " (Theoretical: " << get_theoretical_mean(faces) << ")\n"
                    << "Standard deviation: " << stdDev << '\n';
            free(resultVec);
            break;
        }
        case 1:
        {
            unsigned int successes = get_successes_prob(probSum, faces, dice, rolls);
            float finalExp = ((float)successes/rolls)*100;
            float theory = get_theoretical_prob(faces, dice, probSum) * 100;
            float diff = finalExp - theory;
            std::cout << "Probability of sum " << probSum << " with " << dice << " dice out of " << rolls << " rolls:\n"
                    << "Experimental: " << finalExp << "% (" << successes << " out of " << rolls << ")\n"
                    << "Theoretical: " << theory << "%\n"
                    << "Difference: " << diff << "%\n";
            break;
        }
        case 2:
        {
            unsigned int sum = get_sum(faces, dice, rolls);
            std::cout << "Total SUM: "<< sum << '\n';
            break;
        }
        case 3:
        {
            std::cout << "Craps\n";
            break;
        }
        case 4: //YAHTZEE
        {
            std::cout << "Yahtzee:\n";
            bool* upperList = new_list_vec(6);
            bool* lowerList = new_list_vec(7);
            unsigned int upperScore = 0;
            unsigned int lowerScore = 0;
            unsigned int* yahtzVec;
            int opt = 0;
            int rerolls = 2;
            bool roll = true;
            bool YAHTZEE = false;
            while(rolls > 0)
            {
                if(roll)
                {
                    yahtzVec = new_yahtz_vec(faces, dice);
                    roll = false;
                    rerolls = 2;
                } 
                print_yahtz_vec(yahtzVec, dice, rolls);
                std::cout << "\nChoose: \n"
                        << "0. Skip (if no option available)\n"
                        << "1. Upper section (Aces, Twos...)\n"
                        << "2. Lower section (N of a Kind, Full House...)\n"
                        << ((rerolls)? ("3. Reroll a dice\n") : ("\0"))
                        << ">_: ";
                std::cin >> opt;
                ignore_nl();
                switch(opt)
                {
                    case 0:
                    {
                        std::cout << "Skipping...\n";
                        roll = true;
                        break;
                    }
                    case 1:
                    {
                        int choice;
                        print_yahtz_vec(yahtzVec, dice, rolls);
                        print_available_list(upperList, true);
                        std::cin >> choice;
                        ignore_nl();
                        std::cout << std::endl;
                        if(!choice) break;
                        else if((choice < 1) || (choice > 6)) std::cout << "\nError with reading input, please try again\n";
                        else
                        {
                            if(is_list_available(upperList, choice-1))
                            {
                                update_list_vec(upperList, choice-1);
                                unsigned int sum = get_sum_of(yahtzVec, choice, dice);
                                std::cout << "GAINED SCORE: +" << sum << std::endl;
                                upperScore += sum;
                                if(upperScore >= 63)
                                {
                                    std::cout << "BONUS (> 63): +35\n";
                                    upperScore += 35;
                                }
                                std::cout << "\nTotal UPPER score: " << upperScore << std::endl;
                                roll = true;
                            }
                            else std::cout << "\nThat option is no longer available!\nTry again\n";
                        }
                        break;
                    }
                    case 2:
                    {
                        int choice;
                        print_yahtz_vec(yahtzVec, dice, rolls);
                        print_available_list(lowerList, false);
                        std::cin >> choice;
                        ignore_nl();
                        std::cout << std::endl;
                        if(!choice) break;
                        else if((choice < 1) || (choice > 7)) std::cout << "\nError with reading input, please try again\n";
                        else
                        {
                            if(is_list_available(lowerList, choice-1))
                            {
                                //3oak, 4oak, full house, sm seq, lg seq, Yahtzee, chance
                                switch(choice)
                                {
                                    case 1:
                                    {
                                        insertion_sort(yahtzVec, dice);
                                        if(check_reps(yahtzVec, dice, 3))
                                        {
                                            std::cout << "Found 3 of a Kind!\n";
                                            unsigned int sum = get_yahtz_vec_sum(yahtzVec, dice);
                                            std::cout << "GAINED SCORE: +" << sum << '\n';
                                            lowerScore += sum;
                                            roll = true;
                                        }
                                        else std::cout << "Didn't find any 3 of a Kind!\nTry again";
                                        break;
                                    }
                                    case 2:
                                    {
                                        insertion_sort(yahtzVec, dice);
                                        if(check_reps(yahtzVec, dice, 4))
                                        {
                                            std::cout << "Found 4 of a Kind!\n";
                                            unsigned int sum = get_yahtz_vec_sum(yahtzVec, dice);
                                            std::cout << "GAINED SCORE: +" << sum << '\n';
                                            lowerScore += sum;
                                            roll = true;
                                        }
                                        else std::cout << "Didn't find any 4 of a Kind!\nTry again";
                                        break;
                                    }
                                    case 3:
                                    {
                                        insertion_sort(yahtzVec, dice);
                                        if(check_fh(yahtzVec))
                                        {
                                            std::cout << "Found a Full House!\n";
                                            std::cout << "GAINED SCORE: +25\n";
                                            lowerScore += 25;
                                            roll = true;
                                        }
                                        else std::cout << "Didn't find a Full House!\nTry again";
                                        break;
                                    }
                                    case 4:
                                    {
                                        insertion_sort(yahtzVec, dice);
                                        if(check_seq(yahtzVec, dice, 4))
                                        {
                                            std::cout<< "Small sequence of 4 found!\n"
                                                    << "GAINED SCORE: +30\n";
                                            lowerScore += 30;
                                            roll = true;
                                        }
                                        else std::cout << "Didn't find any small sequence of 4!\nTry again";
                                        break;
                                    }
                                    case 5:
                                    {
                                        insertion_sort(yahtzVec, dice);
                                        if(check_seq(yahtzVec, dice, 5))
                                        {
                                            std::cout<< "Large sequence of 5 found!\n"
                                                    << "GAINED SCORE: +40\n";
                                            lowerScore += 40;
                                            roll = true;
                                        }
                                        else std::cout << "Didn't find any large sequence of 5!\nTry again";
                                        break;
                                    }
                                    case 6:
                                    {
                                        insertion_sort(yahtzVec, dice);
                                        if(check_reps(yahtzVec, dice, 5))
                                        {
                                            if(!YAHTZEE)
                                            {
                                                std::cout << "YAHTZEE!!!\n"
                                                        << "GAINED SCORE: +50\n";
                                                lowerScore += 50;
                                                YAHTZEE = true;
                                            }
                                            else
                                            {
                                                std::cout << "YAHTZEE!!!\n"
                                                        << "GAINED SCORE (BONUS YAHTZEE): +100\n";
                                                lowerScore += 100;
                                            }
                                            roll = true;
                                        }
                                        else std::cout << "Didn't find any YAHTZEE!\nTry again";
                                        break;
                                    }
                                    case 7:
                                    {
                                        unsigned int sum = get_yahtz_vec_sum(yahtzVec, dice);
                                        std::cout << "Adding all dice...\n"
                                                << "GAINED SCORE: +" << sum << '\n';
                                        lowerScore += sum;
                                        roll = true;
                                        break;
                                    }
                                }
                                if(roll) //'if it's gonna roll' => successfully scored
                                {
                                    if(choice != 6) update_list_vec(lowerList, choice-1); //YAHTZEE will always be an option
                                    std::cout << "\nTotal LOWER score: " << lowerScore << std::endl;
                                }
                            }
                            else std::cout << "\nThat option is no longer available!\nTry again\n";
                        }
                        break;
                    }
                    case 3:
                    {
                        if(!rerolls) std::cout << "\nCan't reroll anymore for this turn!\n";
                        else
                        {
                            int choice;
                            print_yahtz_vec(yahtzVec, dice, rolls);
                            std::cout << "\nChoose which dice to REROLL\n"
                                    << "(0. Go back)\n"
                                    << ">_: ";
                            std::cin >> choice;
                            ignore_nl();
                            if(!choice) break;
                            else if((choice < 1 )||(choice > dice)) std::cout << "\nError with reading input, please try again\n";
                            else
                            {
                                update_yahtz_vec(yahtzVec, choice-1, faces);
                                rerolls--;
                            }
                        }
                        break;
                    }
                    default:
                    {
                        std::cout << "\nThat option is not available!\nTry again.\n"; //roll = false
                        break;
                    }
                }
                if(roll) rolls--;
            }
            free(upperList);
            free(lowerList);

            std::cout<< "Final UPPER score: " << upperScore
                    << "\nFinal LOWER score: " << lowerScore
                    << "\n\nFINAL SCORE: " << upperScore+lowerScore;
        }
    }
       
    return 0;
}

//Unblock-File ./main.exe