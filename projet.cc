// EPFL - Programmation Orientée Projet (en C++) - COM-112(a)
// Projet Dodgeball
// Auteurs: Rafael RIBER  - SCIPER: 296142
//          Valentin RIAT - SCIPER: 289121

#include <iostream>
#include <string>
#include <cstring>
#include "simulation.h"
#include "error.h"
#include "gui.h"
#include "define.h"

int main(int argc, char *argv[]) {
  int mode(NOFILE);
  if (argc > 1){
    if (strcmp(argv[FIRST_ARG], "Error") == 0){
      if (argc < 3){
        std::cout << "Not enough arguments" << std::endl;
        exit(0);
      }
      mode = ERROR;
      Simulation simulation;
      simulation.read_error(argv[SECOND_ARG]);
    }else if(strcmp(argv[FIRST_ARG], "Step") == 0){
      if (argc < 3){
        std::cout << "Not enough arguments" << std::endl;
        exit(0);
      }
      mode = STEP;
      Simulation simulation;
      std::cout<<"Step mode not yet implemented"<<std::endl;
    }else{
      mode = NORMAL;
      gui_start(mode, argv[1]);
    }
  }else{
    mode = NOFILE;
    gui_start_nofile(mode);
  }
  return 0;
}
