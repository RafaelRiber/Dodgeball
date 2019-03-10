#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "simulation.h"
#include "error.h"

void simulation_read_error(char *file_name){
  string line;
  ifstream file(file_name);
  if(!file.fail()){
      while(getline(file >> ws,line))
      {
        // On ignore les lignes qui commencent par un commentaire
        if(line[0]=='#')  continue;

        simulation_decodeLine(line);
      }
      std::cout << FILE_READING_SUCCESS << std::endl;
    }
}

void simulation_decodeLine(string line)
{
  std::cout << "LINE DECODE NOT IMPLEMENTED" << std::endl;
}
