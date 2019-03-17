#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "simulation.h"
#include "error.h"
#include "player.h"
#include "ball.h"
#include "map.h"

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

void Simulation::decodeLine(std::string line){
  std::istringstream data(line);

	enum Read_State {NBCELL,NBPLAYERS,PLAYERPOS,NBOBST,OBSTPOS,NBBALLS,BALLS,END};

	static int state(NBCELL);
	static int i(0), j(0), k(0);
  static double nbCell(0), nbPlayers(0), nbObst(0), nbBalls(0);
  double row(0), column(0), x(0), y(0), nbt(0), counter(0), angle(0);
  static Map m;

	switch(state){
	case NBCELL: {
		if(!(data >> nbCell));
		else i = 0;
		state = NBPLAYERS;
    m.setSize(nbCell);
	  break;
  }

	case NBPLAYERS: {
    if(!(data >> nbPlayers));
    else i = 0;
    state = PLAYERPOS;
    break;
  }

	case PLAYERPOS: {
    if(!(data >> x >> y  >> nbt >> counter));
		else ++i;
    if(i == nbPlayers) state = NBOBST;
    Player p(x, y, nbt, counter);
    p.add();
	  break;
  }

  case NBOBST: {
    if(!(data >> nbObst));
    else i = 0;
    state = OBSTPOS;
    break;
  }

  case OBSTPOS: {
    if(!(data >> row >> column));
  	else ++j;
    if(j == nbObst) state = NBBALLS;
    m.setObstacle(row, column);
    break;
  }

  case NBBALLS: {
    if(!(data >> nbBalls));
    else k = 0;
    state = BALLS;
    break;
  }

  case BALLS: {
    if(!(data >> x >> y >> angle));
  	else ++k;
    if(k == nbBalls) state = END;
    Ball b(x, y, angle);
    b.add();
    break;
  }

	case END:
    break;
	}
}
