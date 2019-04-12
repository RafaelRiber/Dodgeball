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

#define MODE_OR_FILE_NAME_IF_GUI_MODE     1
#define FILE_NAME_OR_NOTHING_IF_GUI_MODE  2

int main(int argc, char *argv[]) {

  int mode(NOFILE);

  //simulation.read("C:/Users/Valentin/Documents/GitHub/Dodgeball/E02.txt"); exit(0); //debug

  if (argc > 1){
    if (strcmp(argv[MODE_OR_FILE_NAME_IF_GUI_MODE], "Error") == 0){
      mode = ERROR;
      Simulation simulation;
      simulation.read_error(argv[FILE_NAME_OR_NOTHING_IF_GUI_MODE]);
    }else if(strcmp(argv[MODE_OR_FILE_NAME_IF_GUI_MODE], "Step") == 0){
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
