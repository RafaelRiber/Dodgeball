#include <iostream>
#include "simulation.h"
#include "error.h"

using namespace std;

void read(char *file_name);
void decodeLine(string line);

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
  string line;
  ifstream file(file_name);
  if(!file.fail()){
      while(getline(file >> ws,line))
      {
        // On ignore les lignes qui commencent par un commentaire
        if(line[0]=='#')  continue;

        decodeLine(line);
      }
      cout << "fin de la lecture" << endl;
    }
    else erreur(LECTURE_OUVERTURE);
}

void decodeLine(string line)
{
  cout << "LINE DECODE NOT IMPLEMENTED" << endl;
}
