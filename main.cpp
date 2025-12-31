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
                    << "'--faces' (values: [6, 8, 10, 12, 20]) <- Number of faces each dice will have. (6 faces by default)\n"
                    << "'--dice' (values: [1,...,10000]) <- One can roll so many dice... (2 dice by default)\n"
                    << "'--rolls' (values: any) <- Number of rolls for each dice.\n"
                    << "'--game' (modes: ['stats', 'prob', 'sum', 'craps', 'yahtzee']) <- Represents the Game Mode. ('stats' by default)\n"
                    << "\n";
}

void print_error(const char *err)
{
    std::cout << "\nError with reading the command: ***" << err << "***\n"
            <<"Please make sure to add arguments+values like this: '--argument <value>'.\n";
}

//Honorable mention:
// bool is_number(const char string[])
// {
//     int stringSize = 0;
//     while(string[stringSize] != '\0') ++stringSize;

//     for(int i = 0; i < stringSize; i++)
//     {
//         if(!isdigit(string[i])) return false;
//     }
//     return true;
// }

bool is_number(const char* str)
{
    if(!str || *(str) == '\0') return false;
    for(int i = 0; *(str+i) != '\0'; i++)
    {
        if(!isdigit(*(str+i))) return false;
    }
    return true;
}

enum gameMode {stats, prob, sum, craps, yahtzee};

int main(int argc, char* argv[])
{
    unsigned int faces = DEFAULT_FACES;
    unsigned int dice = DEFAULT_DICE;
    unsigned int rolls = DEFAULT_ROLLS;
    gameMode game = stats;

    if(argc == 1)
    {
        print_help();
        return 0;
    }

    for(int i = 1; i < argc; i+=2)
    {
        //we need to check for '--game' command tho, it doesn't take ints as values
        char* temp = NULL;
        strcpy(temp, argv[i]);
        if(!is_number(argv[i+1]) && (!strcmp(temp, "--game")))
        {
            print_error(argv[i+1]);
            return 0;
        }

        if((strcmp(argv[i], "--faces") == 0) && (i+1) <= argc)
        {
            faces = atoi(argv[i+1]);
        }
        else if((strcmp(argv[i], "--dice") == 0) && (i+1) <= argc)
        {
            dice = atoi(argv[i+1]);
        }
        else if((strcmp(argv[i], "--rolls") == 0) && (i+1) <= argc)
        {
            rolls = atoi(argv[i+1]);
        }
        else if((strcmp(argv[i], "--game") == 0) && (i+1) <= argc)
        {
            //I'd use a switch so hard but IDK how
            if(strcmp(argv[i+1], "stats") == 0) game = stats;
            else if(strcmp(argv[i+1], "prob") == 0) game = prob;
            else if(strcmp(argv[i+1], "sum") == 0) game = sum;
            else if(strcmp(argv[i+1], "craps") == 0) game = craps;
            else if(strcmp(argv[i+1], "yahtzee") == 0) game = yahtzee;
            else 
            {
                print_error(argv[i+1]);
                return 0;
            }
        }
        else
        {
            print_error(strcat(strcat(argv[i], " "), argv[i+1]));
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