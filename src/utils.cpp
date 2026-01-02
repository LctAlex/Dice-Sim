#include "utils.hpp"

void print_help()
{
    std::cout << "\nHELP:: Please add command arguments + values.\n"
                    << "Available arguments:\n"
                    << "'--faces <value>' (values: [6, 8, 10, 12, 20]) <- Number of faces each dice will have. (6 faces by default)\n"
                    << "'--dice <value>' (values: [1,...,MAX_INT]) <- Number of dice to roll. (2 dice by default)\n"
                    << "'--rolls <value>' (values: [1,...,MAX_INT]) <- Number of rolls for each dice. (100 rolls by default)\n"
                    << "'--game <mode>' (modes: ['stats', 'prob' <takes VALUE>, 'sum', 'craps', 'yahtzee']) <- Represents the Game Mode. ('stats' by default)\n"
                    << "Command example: ./program --dice 20 --faces 12 --game prob 7\n"
                    << "Use '--h' or '--help' to see this again.\n"
                    << "\n";
}

void print_error(const char *err, bool stop)
{
    std::cout << "\nERROR:: Error with reading the command. *** " << err << " ***\n";
    if(stop) std::cout << "Please make sure to add arguments + values/modes like this: '--argument <value/mode>'.\n\n";
}

void print_info(unsigned int faces, unsigned int dice, unsigned int rolls, char game[], unsigned int probSum)
{
    std::cout << "\nINFO:\n"
            << "=====\n"
            << "Faces: " << faces << '\n'
            << "Dice: " << dice << '\n'
            << "Rolls: " << rolls << '\n'
            << "Game: " << game << '\n'
            << ((probSum) ? (std::string("Probability Sum: ") + std::to_string(probSum) +'\n').c_str() : ("\0")) //surprised this works!
            << "====="
            << "\n\nRolling dice...\n\n";
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
    return 0; //will baiscally set the game to 'stats'
}