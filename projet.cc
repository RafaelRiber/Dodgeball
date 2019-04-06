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

int main(int argc, char *argv[]) {

  enum ModeList{ERROR,STEP,NORMAL,NOFILE};

  int mode(NOFILE);

  //simulation.read("C:/Users/Valentin/Documents/GitHub/Dodgeball/E02.txt"); exit(0); //debug

  if (argc > 1){
    if (strcmp(argv[1], "Error") == 0){
      mode = ERROR;
      Simulation simulation;
      simulation.read_error(argv[2]);
    }else if(strcmp(argv[1], "Step") == 0){
      mode = STEP;
      Simulation simulation;
      std::cout<<"Step mode not yet implemented"<<std::endl;
    }else{
      mode = NORMAL;
      gui_start(argv[1], argc, argv);
    }

  }else{
    mode = NOFILE;
    gui_start_nofile(argc, argv);
  }
  return 0;
}
