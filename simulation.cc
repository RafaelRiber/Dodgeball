// EPFL - Programmation Orientée Projet (en C++) - COM-112(a)
// Projet Dodgeball
// Auteurs: Rafael RIBER - SCIPER: 296142
//          Valentin RIAT - SCIPER: 289121

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "error.h"
#include "define.h"

#include "simulation.h"
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
    setSimParameters(nbCell);
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
    add_player(p);
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
    add_obstacle(row, column, j, m);
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
    add_ball(b, k, m.getMap());
    break;
  }

	case END:
    break;
	}
}

void Simulation::setSimParameters(int n){
  nbCell = n;
  playerRadius = COEF_RAYON_JOUEUR * (SIDE / n);
  ballRadius   = COEF_RAYON_BALLE  * (SIDE / n);
  readMargin = (COEF_MARGE_JEU/MARGIN_DIVIDER) * (SIDE/nbCell);
}

void Simulation::add_player(Player p){

  playerBoundsCheck(p, DIM_MAX, DIM_MAX);

  playerPlayerCheck(p);

  players.push_back(p);
}

double Simulation::getPlayerRadius(){
  return playerRadius;
}

double Simulation::getBallRadius(){
  return ballRadius;
}

void Simulation::add_ball(Ball b, int indice,
                          const std::vector<std::vector<int>> &map){

  ballBoundsCheck(b, DIM_MAX, DIM_MAX);

  ballBallCheck(b);

  playerBallCheck(b);

  ballObstacleCheck(b.getBallCoordinates(), indice, map);

  balls.push_back(b);
}

void Simulation::printPlayerSize(){
  std::cout << players.size() << std::endl;
}

void Simulation::printBallSize(){
  std::cout << balls.size() << std::endl;
}

void Simulation::playerBoundsCheck(Player p, double boundaryX, double boundaryY){
  if ((p.getPlayerCoordinates().inBoundary(boundaryX,boundaryY) == false)){
    std::cout << PLAYER_OUT(players.size() + 1) << std::endl;
    exit(0);
  }
}

void Simulation::playerPlayerCheck(Player p){
  for (int i = 0; i < players.size(); ++i){
    Segment d(p.getPlayerCoordinates(), players[i].getPlayerCoordinates());
    if (d.getLength() < (2 * getPlayerRadius()) + readMargin){
      std::cout << PLAYER_COLLISION(i + 1, players.size() + 1) << std::endl;
      exit(0);
    }
  }
}

void Simulation::ballBoundsCheck(Ball b, double boundaryX, double boundaryY){
  if ((b.getBallCoordinates().inBoundary(boundaryX,boundaryY) == false)){
    std::cout << BALL_OUT(balls.size() + 1) << std::endl;
    exit(0);
  }
}

void Simulation::ballBallCheck(Ball b){
  for (int i = 0; i < balls.size(); ++i){
    Segment d(b.getBallCoordinates(), balls[i].getBallCoordinates());
    if (d.getLength() < (2 * getPlayerRadius()) + readMargin){
      std::cout << BALL_COLLISION(i + 1, balls.size() + 1) << std::endl;
      exit(0);
    }
  }
}

void Simulation::playerBallCheck(Ball b){
  for (int i = 0; i < players.size(); ++i){
    Point ballCoords(b.getBallCoordinates());
    Point playerCoords(players[i].getPlayerCoordinates());

    Segment d(ballCoords, playerCoords);

    double minDist = playerRadius + ballRadius + readMargin;

    if(d.getLength() < minDist){
      std::cout << PLAYER_BALL_COLLISION(i + 1, balls.size() + 1) << std::endl;
      exit(0);
    }
  }
}

void Simulation::ballObstacleCheck(Point ball, int indice,
                                   const std::vector<std::vector<int>> &map){
  Cell ballCell(ball, nbCell, SIDE);
  int x(0),y(0);
  ballCell.getCoordinates(x,y);
  double totalMargin = ballRadius + readMargin;

  for(int i(x-1);i<=x+1;i++){
    for(int j(y-1);j<=y+1;j++){
      if(i >= 0 && i < nbCell && j >= 0 && j < nbCell){
        if (map[j][i] > 0 && pointOsbstacleCollistion(ball, j, i, totalMargin)){
          std::cout<<COLL_BALL_OBSTACLE(indice)<<std::endl;
          exit(0);
        }
      }
    }
  }
}

void Simulation::add_obstacle(unsigned int row, unsigned int column,
                              unsigned int indice, Map &m){
  double totalMargin = playerRadius + readMargin;

  for(size_t i(0); i < players.size(); i++){
    if(pointOsbstacleCollistion(players[i].getPlayerCoordinates(), row, column,
                                                                   totalMargin)){
         std::cout<<COLL_OBST_PLAYER( indice, i+1)<<std::endl;
         exit(0);
       }
  }
  m.setObstacle(row, column);
}

bool Simulation::pointOsbstacleCollistion(Point point, int obstRow, int obstColumn,
                                          double totalMargin){
    Point upperLeftCorner (Cell(obstColumn  , obstRow  ), nbCell, SIDE);
    Point upperRightCorner(Cell(obstColumn+1, obstRow  ), nbCell, SIDE);
    Point lowerLeftCorner (Cell(obstColumn  , obstRow+1), nbCell, SIDE);
    Point lowerRightCorner(Cell(obstColumn+1, obstRow+1), nbCell, SIDE);

    Vector up    (0, totalMargin);
    Vector right (totalMargin, 0);

    Rectangle rectangleH (upperLeftCorner  - right, upperRightCorner + right,
                          lowerRightCorner + right, lowerLeftCorner  - right );
    Rectangle rectangleV (upperLeftCorner  + up,    upperRightCorner + up ,
                          lowerRightCorner - up,    lowerLeftCorner  - up);
    Circle upperLeftCircle (upperLeftCorner , totalMargin);
    Circle upperRightCircle(upperRightCorner, totalMargin);
    Circle lowerRightCircle(lowerRightCorner , totalMargin);
    Circle lowerLeftCircle(lowerLeftCorner , totalMargin);


    if(rectangleH.isInRectangle(point)
       || rectangleV.isInRectangle(point)
       || upperRightCircle.isInCircle(point)
       || lowerRightCircle.isInCircle(point)
       || upperLeftCircle.isInCircle(point)
       || lowerLeftCircle.isInCircle(point)){

        return true;
    }else{
        return false;
    }
}
