#ifndef SIMULATION_H
#define SIMULATION_H

#include "player.h"
#include "ball.h"
#include "map.h"

void simulation_read_error(char *file_name); //Error mode read
void simulation_decodeLine(std::string line);

#endif
