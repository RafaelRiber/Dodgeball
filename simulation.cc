#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "simulation.h"
#include "error.h"

void Simulation::read_error(char *file_name){
  std::string line;
  std::ifstream file(file_name);
  if(!file.fail()){
      while(getline(file >> std::ws,line))
      {
        // On ignore les lignes qui commencent par un commentaire
        if(line[0]=='#')  continue;

        Simulation::decodeLine(line);
      }
      std::cout << FILE_READING_SUCCESS << std::endl;
    }
}

void Simulation::read(char *file_name){
  std::cout << "read in non-error mode not yet implemented" << std::endl;
}

void Simulation::decodeLine(std::string line)
{
  std::cout << "LINE DECODE NOT IMPLEMENTED" << std::endl;
}
