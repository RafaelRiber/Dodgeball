#include <iostream>
#include "simulation.h"

using namespace std;

void read(char *file_name);

int main(int argc, char *argv[]) {

  static bool errorMode = false;

  if (argc > 1){
    if (argv[1] == string("Error")){
      errorMode = true;
      read(argv[2]);
    }
    else read(argv[1]);
  };

  return 0;
}

void read(char *file_name){
  cout << "FILE READ NOT YET IMPLEMENTED" << endl;
}
