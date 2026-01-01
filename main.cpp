#include <iostream>
#include <string.h>
#include <stdlib.h>

#define DEFAULT_FACES 6
#define DEFAULT_DICE 2
#define DEFAULT_ROLLS 100

void print_help()
{
    std::cout << "\nPlease add command arguments + values.\n"
                    << "Available arguments:\n"
                    << "'--faces <value>' (values: [6, 8, 10, 12, 20]) <- Number of faces each dice will have. (6 faces by default)\n"
                    << "'--dice <value>' (values: [1,...,MAX_INT]) <- One can roll so many dice... (2 dice by default)\n"
                    << "'--rolls <value>' (values: [1,...,MAX_INT]) <- Number of rolls for each dice.\n"
                    << "'--game <mode>' (modes: ['stats', 'prob', 'sum', 'craps', 'yahtzee']) <- Represents the Game Mode. ('stats' by default)\n"
                    << "\n";
}

void print_error(const char *err)
{
    std::cout << "\nError with reading the command. ***" << err << "***\n"
    << "Please make sure to add arguments + values like this: '--argument <value/mode>'.\n";
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

const char* gameVec[5] = {"stats", "prob", "sum", "craps", "yahtzee"};

const char* get_game(const char* str) //*str will be argv[i+1], if nothing works, *game = '\0'
{
    if(!str || *(str) == '\0') return NULL;
    for(int i = 0; i < sizeof(gameVec)/sizeof(gameVec[0]); i++)
    {
        if(strcmp(str, gameVec[i]) == 0) return gameVec[i];
    }
    return NULL;
}

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
        if(is_number(argv[i])) continue;
        if((strcmp(argv[i], "--faces") == 0) && (i+1) <= argc)
        {
            if(!is_number(argv[i+1])) 
            {
                print_error(strcat(argv[i],strcat(argv[i+1], " <- there should be a value")));
                return 0;
            }
            faces = atoi(argv[i+1]);
        }
        else if((strcmp(argv[i], "--dice") == 0) && (i+1) <= argc)
        {
            if(!is_number(argv[i+1])) 
            {
                print_error(strcat(argv[i],strcat(argv[i+1], " <- this should be a value")));
                return 0;
            }
            dice = atoi(argv[i+1]);
        }
        else if((strcmp(argv[i], "--rolls") == 0) && (i+1) <= argc)
        {
            if(!is_number(argv[i+1])) 
            {
                print_error(strcat(argv[i],strcat(argv[i+1], " <- this should be a value")));
                return 0;
            }
            rolls = atoi(argv[i+1]);
        }
        else if((strcmp(argv[i], "--game") == 0) && (i+1) <= argc)
        {
            // const char* mode = get_game(argv[i+1]);
            // if(*mode != '\0')
            // {
            //     std::cout << "MODE != '\0'";
            //     strcpy(game, get_game(argv[i+1]));
            // }
            // else 
            // {
            //     std::cout << "MODE = '\0'";
            //     print_error(strcat(argv[i], strcat(argv[i+1], " <- not a game mode")));
            // }
        }
        else
        {
            print_error(strcat(argv[i], " <- wrong/unrecognized command"));
            return 0;
        }
    }

    std::cout << "Faces: " << faces << '\n'
            << "Dice: " << dice << '\n'
            << "Rolls: " << rolls << '\n'
            << "Game: " << game << '\n';

    return 0;
}

//Unblock-File .\main.exe
//Ai bagat si main.exe in primul commit, sa te asiguri ca e sters
