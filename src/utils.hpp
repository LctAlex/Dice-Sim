#pragma once
#include <iostream>
#include <string.h>
#include <string>

void print_help();
void print_error(const char *err, bool stop);
bool is_number(const char* str);
void print_info(unsigned int faces, unsigned int dice, unsigned int rolls, char game[], unsigned int probSum);
const char* get_game(const char* str);
int find_gamemode(const char* game);