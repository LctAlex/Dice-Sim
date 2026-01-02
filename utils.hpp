#pragma once
#include <iostream>
#include <string.h>
#include <string>

void print_help();
void print_error(const char *err, bool stop);
bool is_number(const char* str);
const char* get_game(const char* str);
int find_gamemode(const char* game);