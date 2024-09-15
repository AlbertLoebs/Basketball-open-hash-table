#include <iostream>
#include <string>
#include <fstream>
#include <string.h>
#include <vector>
#include <cstdlib>
#include <queue>
#include <cmath>

using namespace std;


#ifndef BBALL_H
#define BBALL_H

struct Player {
    string lastName;
    string firstName;
    string college;
    double height;
    double weight;
    int bday;
};

void printPlayer(const Player *p);

#endif
