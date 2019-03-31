// EPFL - Programmation Orientée Projet (en C++) - COM-112(a)
// Projet Dodgeball
// Auteurs: Rafael RIBER  - SCIPER: 296142
//          Valentin RIAT - SCIPER: 289121

#include <iostream>
#include <string>
#include <cstring>
#include "simulation.h"
#include "error.h"

int main(int argc, char *argv[]) {

  Simulation simulation;


  if (argc > 1){
    if (strcmp(argv[1], "Error") == 0){
      simulation.read_error(argv[2]);
    }else if(strcmp(argv[1], "Step") == 0){
      std::cout<<"Step mode not yet implemented"<<std::endl;
    }else{
      simulation.read(argv[2]);
    }

  }else{
    simulation.read();
  }
  return 0;
}
