#ifndef SIMULATION_H
#define SIMULATION_H

#include "player.h"
#include "ball.h"
#include "map.h"

void simulation_read(char *file_name);
void simulation_decodeLine(std::string line);

#endif
