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

  static bool errorMode = false;

  Simulation simulation;

  if (argc > 1){
    if (strcmp(argv[1], "Error") == 0){
      errorMode = true;
    }
    if (errorMode == true){
      simulation.read_error(argv[2]);
    }
    else {
      std::cout << "Only error mode is implemented at this time" << std::endl;
    }
  }
  return 0;
}
