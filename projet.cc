#include <iostream>
#include <string>
#include "simulation.h"
#include "error.h"

int main(int argc, char *argv[]) {

  static bool errorMode = false;

  if (argc > 1){
    if (strncmp(argv[1], "Error", 5) == 0){
      errorMode = true;
    }
    if (errorMode == true){
      simulation_read_error(argv[2]);
    }
    else {
      simulation_read(argv[2]);
    }
    else simulation_read_error(argv[1]);
  };

  return 0;
}
