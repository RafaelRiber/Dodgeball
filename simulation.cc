// EPFL - Programmation Orientée Projet (en C++) - COM-112(a)
// Projet Dodgeball
// Auteurs: Rafael RIBER  - SCIPER: 296142
//          Valentin RIAT - SCIPER: 289121

#include "simulation.h"



//----------------------------GETTERS--------------------------------------



Map Simulation::getMap(){
  return m;
}

int Simulation::getNbCell(){
  return nbCell;
}

int Simulation::getNbBalls(){
  return balls.size();
}

std::vector<Player> Simulation::getPlayers(){
  return players;
}

std::vector<Ball> Simulation::getBalls(){
  return balls;
}



//----------------------------READINGS------------------------------------



void Simulation::read_error(char *file_name){
  if(openFile(file_name)) std::cout << FILE_READING_SUCCESS << std::endl;
  exit(0);
}

void Simulation::read_step(char *input_file, char *output_file){
  if(openFile(input_file)){
    simulate_one_step();
    saveToFile(output_file);
  }else{
    exit(0);
  }
}

void Simulation::read(char *file_name){
  if(openFile(file_name)) successfulRead = true;
  else reset();
}

bool Simulation::openFile(std::string fileName){
  std::string line;
  std::ifstream file(fileName);

  if(file.fail()){
    std::cout<<"Failed to open file"<<std::endl;
    return READING_FAIL;
  }else{
    while(getline(file >> std::ws,line)) {
      if(line[0]=='#')  continue;
      if(!decodeLine(line)) return READING_FAIL;
    }
    return READING_SUCCESS;
  }
}

bool Simulation::decodeLine(std::string line){
  std::istringstream data(line);
  static bool end_of_read(false), failed_to_read(false);
	static int i(0), j(0), k(0), state(NBCELL);
  static double nbCell(0), nbPlayers(0), nbObst(0), nbBalls(0);
  double row(0), column(0), x(0), y(0), nbt(0), counter(0), angle(0);
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
      if(nbPlayers == 0) state = NBOBST;
      else state = PLAYERPOS;
      break;
    }
    case PLAYERPOS: {
      if(!(data >> x >> y >> nbt >> counter));
      else ++i;
      if(i == nbPlayers) state = NBOBST;
      Player p(x, y, nbt, counter);
      if(! add_player(p)) {
        end_of_read    = true;
        failed_to_read = true;
      }
      break;
    }
    case NBOBST: {
      if(!(data >> nbObst));
      else i = 0;
      if(nbObst == 0) state = NBBALLS;
      else state = OBSTPOS;
      break;
    }
    case OBSTPOS: {
      if(!(data >> row >> column));
      else ++j;
      if(j == nbObst) state = NBBALLS;
      if(! add_obstacle(row, column, j, m) ){
        end_of_read    = true;
        failed_to_read = true;
      }
      break;
    }
    case NBBALLS: {
      if(!(data >> nbBalls));
      else k = 0;
      if(nbBalls == 0) end_of_read = true;
      else state = BALLS;
      break;
    }
    case BALLS: {
      if(!(data >> x >> y >> angle));
      else ++k;
      if(k == nbBalls) end_of_read = true;
      Ball b(x, y, angle);
      if(! add_ball(b, k, m.getMap()) ){
        end_of_read    = true;
        failed_to_read = true;
      }
      break;
    }
  }
  if(end_of_read){
    i = 0; j = 0; k = 0;
    nbCell = 0; nbPlayers = 0; nbObst = 0; nbBalls = 0;
    state = NBCELL;
    end_of_read = false;
    if(failed_to_read){
      failed_to_read = false;
      return READING_FAIL;
    }
    refresh_floyd();
  }
  return READING_SUCCESS;
}

void Simulation::setSimParameters(int n){
  nbCell = n;
  playerRadius =  COEF_RAYON_JOUEUR * (SIDE / n);
  ballRadius   =  COEF_RAYON_BALLE  * (SIDE / n);
  readMargin   = (COEF_MARGE_JEU/MARGIN_DIVIDER) * (SIDE/nbCell);
  gameMargin   =  COEF_MARGE_JEU * (SIDE/nbCell);
  playerSpeed  =  COEF_VITESSE_JOUEUR * (SIDE/nbCell);
  ballSpeed    =  COEF_VITESSE_BALLE * (SIDE/nbCell);
}

bool Simulation::add_player(Player p){

  if(! playerBoundsCheck(p, DIM_MAX, DIM_MAX) ) return READING_FAIL;

  if(! playerPlayerCheck(p) ) return READING_FAIL;

  players.push_back(p);

  return READING_SUCCESS;
}

double Simulation::getPlayerRadius(){
  return playerRadius;
}

double Simulation::getBallRadius(){
  return ballRadius;
}

bool Simulation::add_ball(Ball b, int indice,
                          const std::vector<std::vector<int>> &map){

  if(! ballBoundsCheck(b, DIM_MAX, DIM_MAX) ) return READING_FAIL;

  if(! ballBallCheck(b) ) return READING_FAIL;

  if(! playerBallCheck(b) ) return READING_FAIL;

  if (! ballObstacleCheck(b.getBallCoordinates(), indice, map) ) return READING_FAIL;
  balls.push_back(b);

  return READING_SUCCESS;
}

void Simulation::printPlayerSize(){
  std::cout << players.size() << std::endl;
}

void Simulation::printBallSize(){
  std::cout << balls.size() << std::endl;
}

bool Simulation::playerBoundsCheck(Player p, double boundaryX, double boundaryY){
  if ((p.getPlayerCoordinates().inBoundary(boundaryX,boundaryY) == false)){
    std::cout << PLAYER_OUT(players.size() + 1) << std::endl;
    return READING_FAIL;
  }
  return READING_SUCCESS;
}

bool Simulation::playerPlayerCheck(Player p){
  for (size_t i = 0; i < players.size(); ++i){
    Segment d(p.getPlayerCoordinates(), players[i].getPlayerCoordinates());
    if (d.getLength() < (2 * playerRadius) + readMargin){
      std::cout << PLAYER_COLLISION(i + 1, players.size() + 1) << std::endl;
      return READING_FAIL;
    }
  }
  return READING_SUCCESS;
}


bool Simulation::ballBoundsCheck(Ball b, double boundaryX, double boundaryY){
  if ((b.getBallCoordinates().inBoundary(boundaryX,boundaryY) == false)){
    std::cout << BALL_OUT(balls.size() + 1) << std::endl;
    return READING_FAIL;
  }
  return READING_SUCCESS;
}

bool Simulation::ballBallCheck(Ball b){
  for (size_t i = 0; i < balls.size(); ++i){
    Segment d(b.getBallCoordinates(), balls[i].getBallCoordinates());
    if (d.getLength() < (2 * ballRadius) + readMargin){
      std::cout << BALL_COLLISION(i + 1, balls.size() + 1) << std::endl;
      return READING_FAIL;
    }
  }
  return READING_SUCCESS;
}

bool Simulation::playerBallCheck(Ball b){
  for (size_t i = 0; i < players.size(); ++i){
    Point ballCoords(b.getBallCoordinates());
    Point playerCoords(players[i].getPlayerCoordinates());

    Segment d(ballCoords, playerCoords);

    double minDist = playerRadius + ballRadius + readMargin;

    if(d.getLength() < minDist){
      std::cout << PLAYER_BALL_COLLISION(i + 1, balls.size() + 1) << std::endl;
      return READING_FAIL;
    }
  }
  return READING_SUCCESS;
}

bool Simulation::ballObstacleCheck(Point ball, int indice,
                                   const std::vector<std::vector<int>> &map){
  Cell ballCell(ball, nbCell, SIDE);
  int x(0),y(0);
  ballCell.getCoordinates(x,y);
  double totalMargin = ballRadius + readMargin;

  for(int i(x-1);i<=x+1;i++){
    for(int j(y-1);j<=y+1;j++){
      if(i >= 0 && i < nbCell && j >= 0 && j < nbCell){
        if (map[j][i] > 0 && pointObstacleCollision(ball, j, i, totalMargin)){
          std::cout<<COLL_BALL_OBSTACLE(indice)<<std::endl;
          return READING_FAIL;
        }
      }
    }
  }
  return READING_SUCCESS;
}

bool Simulation::add_obstacle(unsigned int row, unsigned int column,
                              unsigned int indice, Map &m){
  double totalMargin = playerRadius + readMargin;

  for(size_t i(0); i < players.size(); i++){
    if(pointObstacleCollision(players[i].getPlayerCoordinates(), row, column,
                                                                   totalMargin)){
         std::cout<<COLL_OBST_PLAYER( indice, i+1)<<std::endl;
         return READING_FAIL;
       }
  }
  if(! m.setObstacle(row, column) ) return READING_FAIL;
  return READING_SUCCESS;
}

bool Simulation::pointObstacleCollision(Point point, int obstRow, int obstColumn,
                                          double totalMargin){
    Point upperLeftCorner (Cell(obstRow  , obstColumn  ), nbCell, SIDE);
    Point upperRightCorner(Cell(obstRow+1, obstColumn  ), nbCell, SIDE);
    Point lowerLeftCorner (Cell(obstRow  , obstColumn+1), nbCell, SIDE);
    Point lowerRightCorner(Cell(obstRow+1, obstColumn+1), nbCell, SIDE);

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


    if(   rectangleH.isInRectangle(point)
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

bool Simulation::pointObstacleCollision(Point point, Cell obst, double totalMargin){
  int row(0), column(0);
  obst.getCoordinates(row,column);
  if(pointObstacleCollision(point, row, column, totalMargin)) return true;
  else return false;
}



//----------------------------OTHER FUNCTIONS-----------------------------------



void Simulation::reset(){
  players = std::vector<Player> ();
  balls   = std::vector<Ball>  ();
  m.reset();
}

void Simulation::start(){
  running = true;
  std::cout << "Simulation Started" << std::endl; //DEBUG
}
void Simulation::stop(){
  running = false;
  std::cout << "Simulation Stopped" << std::endl; //DEBUG
}

void Simulation::over(){
  stop();
  gameOver = true;
}

bool Simulation::isOver(){
  if (gameOver) return true;
  else return false;
}

bool Simulation::isRunning(){
  if (running) return true;
  else return false;
}

bool Simulation::isReadSuccessful(){
  if (successfulRead) return true;
  else return false;
}

void Simulation::saveToFile(char *file_name){
  std::ofstream outputFile;
  outputFile.open(file_name);
  outputFile << "# nbCell\n";
  outputFile << nbCell;
  outputFile << "\n# number of players\n";
  outputFile << players.size() << "\n";
  outputFile << "\n# position of players\n";
  for(size_t i(0); i < players.size(); i++){
    double x,y;
    players[i].getPlayerCoordinates().getCoordinates(x, y);
    outputFile << x << " " << y << " "<< players[i].getNbt();
    outputFile << " " << players[i].getCount() << "\n";
  }
  int nbObst(this->getMap().getNbObst());
  outputFile << "\n# number of obstacles\n";
  outputFile << nbObst;
  outputFile << "\n# position of obstacles\n";
  for (size_t i = 0; i < this->getMap().getMap().size(); ++i)
  {
    for (size_t j = 0; j < this->getMap().getMap()[i].size(); ++j)
    {
      if (getMap().getMap()[i][j] == 1) outputFile << i << " " << j << "\n";
    }
  }
  outputFile << "\n# number of balls\n";
  outputFile << getNbBalls() << "\n";
  for(size_t i(0); i < balls.size(); i++){
    double x,y;
    balls[i].getBallCoordinates().getCoordinates(x, y);
    outputFile << x << " " << y << " "<< balls[i].getAngle() << "\n";
  }
  outputFile.close();
}



//----------------------------SIMULATION--------------------------------------


void Simulation::simulate_one_step(){
  //refresh_floyd();
  //dumpFloyd();
/* test cell to indice
  std::cout<<"cell to indice :"<<m.cellToIndice(Cell (1,0))<<std::endl;
  int x,y;
  m.indiceToCell(0).getCoordinates(x,y);
  std::cout<<"indice to cell : "<<x<<" "<<y<<std::endl;
*/
  find_targets();

  move_players();

  fire_balls();
  move_balls();

  ball_player_collisions();
  ball_obstacle_collisions();
  ball_ball_collisions();
  ballOutOfBoundsDeaths();

  incrementCount();
  purge_game();

  std::cout<<"Simulation : one step has been simulated"<<std::endl; //DEBUG
  }

void Simulation::find_targets(){
  double previousDistance = MAX_TARGET_DISTANCE;
  for (size_t i(0); i < players.size(); i++){
    Point currentPlayer = players[i].getPlayerCoordinates();
    previousDistance = MAX_TARGET_DISTANCE;
    for (size_t j(0); j < players.size(); j++){
      if (i != j){
        Point potentialTarget = players[j].getPlayerCoordinates();
        Segment distance(currentPlayer, potentialTarget);
        double currentDistance = distance.getLength();
        if(currentDistance < previousDistance){
          players[i].setTarget(players[j]);
          previousDistance = currentDistance;
        }
      }
      if(players[i].getTarget() == nullptr){
        continue;
      }
    }
  }
}

void Simulation::move_players(){
  set_players_direction();

  for(size_t i(0); i < players.size(); i++){
    Point playerCoord = players[i].getPlayerCoordinates();
    Point targetCoord = players[i].getTargetCoordinates();
    if(Circle(playerCoord+players[i].getNextMove(),
              playerRadius).circleCollision(Circle(targetCoord,playerRadius))){
      Vector next_move(playerCoord, targetCoord);
      next_move.setNorm(next_move.getNorm()-2*playerRadius);
      players[i].setNextMove(next_move);
    }else{
      players[i].make_next_move();
    }
  }
}

void Simulation::set_players_direction(){
  bool lineOfSight(false);
  for(size_t i(0); i<players.size(); i++){
    if(players[i].getTarget() != nullptr){

      lineOfSight = has_direct_line_of_sight(players[i], *(players[i].getTarget()) );                   //CULPRIT
      players[i].setHasLineOfSight(lineOfSight);
      if(lineOfSight){
        Vector direction(players[i].getPlayerCoordinates(),
                         players[i].getTargetCoordinates());
        direction.setNorm(playerSpeed * DELTA_T);
        players[i].setNextMove(direction);
      }else{
        Vector direction = floyd_next_move(players[i]);
        players[i].setNextMove(direction);
      }
    }
  }
}

bool Simulation::has_direct_line_of_sight( Point start, Point end){
  double dl = playerRadius/DELTA_L_DIVIDER;
  double total_margin = playerRadius + gameMargin + dl;

  Point test_point(start);

  Vector direction (test_point, end);
  double distance = direction.getNorm();
  direction.setNorm(dl);

  int test_point_row(0), test_point_col(0);
  for(size_t k(0); k < (distance/dl)-1; k++){
    test_point = test_point+direction;
    Cell(test_point, nbCell, SIDE).getCoordinates(test_point_row, test_point_col);
    for(int i(test_point_row-1); i <= test_point_row+1; i++){
      if (i < 0 || i >= nbCell) continue;
      for(int j(test_point_col-1); j <= test_point_col+1; j++){
        if (j < 0 || j >= nbCell) continue;
        if(m.getMap()[i][j]){
          if(pointObstacleCollision(test_point, i, j, total_margin) ){
            return false;
          }
        }
      }
    }
  }
  return true;
}
bool Simulation::has_direct_line_of_sight(Player &player, Player &target){
  return has_direct_line_of_sight(player.getPlayerCoordinates(),
                                  target.getPlayerCoordinates());
}

Vector Simulation::floyd_next_move(Player player){
  Cell player_cell = Cell(player.getPlayerCoordinates(), nbCell, SIDE);
  Cell target_cell = Cell(player.getTargetCoordinates(), nbCell, SIDE);

  int playerX(0), playerY(0), targetX(0), targetY(0);
  player_cell.getCoordinates(playerX, playerY);
  target_cell.getCoordinates(targetX, targetY);
  int indice_target = m.getCellToIndice()[targetX][targetY];
  int indice_player;
  double current_distance;

  Cell next_cell = CELL_ERROR;
  Point center_next_cell(-SIDE, -SIDE);
  double min_distance(nbCell*nbCell);
  for(int i(playerX-1);i <= playerX+1; i++){
    for(int j(playerY-1); j <= playerY+1; j++){

      if(i >= 0 && j >= 0 && i < nbCell && j < nbCell){
        indice_player = m.getCellToIndice()[i][j];
        if(indice_player != -1){
          current_distance = floyd_distances[indice_player][indice_target];
          if(current_distance < min_distance){
            center_next_cell = Cell(i,j).getCenterCell(nbCell, SIDE);
            if(has_direct_line_of_sight(player.getPlayerCoordinates(),
                                        center_next_cell)){
              min_distance = current_distance;
              next_cell = Cell(i,j);
            }
          }
        }
      }
    }
  }
  center_next_cell = next_cell.getCenterCell(nbCell, SIDE);
  Vector direction(player.getPlayerCoordinates(), center_next_cell);
  direction.setNorm(playerSpeed*DELTA_T);
  return direction;
}

void Simulation::refresh_floyd(){
  int nbSpot = nbCell * nbCell - m.getNbObst();
  floyd_distances.resize(nbSpot, std::vector<double>(nbSpot, nbCell*nbCell));
  m.setCellToIndice();
  m.setIndiceToCell();
  Cell start(CELL_ERROR), goal(CELL_ERROR);
  for(int i(0); i<nbSpot; i++){
    floyd_distances[i][i] = 0;
    for(int j(0); j<nbSpot; j++){
      start = m.getIndiceToCell()[i];
      goal  = m.getIndiceToCell()[j];
      if( start.isAdjacentTo(goal) ){
        floyd_distances[i][j] = 1;
      }else if( start.isDiagonalyAdjacentTo(goal) ){
        //floyd_distances[i][j] = sqrt(2);
      }
    }
  }
  double new_distance(0);
  for(int k(0); k < nbSpot; k++){
    for(int i(0); i < nbSpot; i++){
      for(int j(0); j < nbSpot; j++){
        new_distance = floyd_distances[i][k] + floyd_distances[k][j];
        if(new_distance < floyd_distances[i][j]){
          floyd_distances[i][j] = new_distance;
        }
      }
    }
  }
}

void Simulation::fire_balls(){
  for(size_t i(0); i < players.size(); i++){
    Point playerCoord = players[i].getPlayerCoordinates();
    if((players[i].getCount() == MAX_COUNT) && players[i].getHasLineOfSight()){
      Vector target_direction(playerCoord, players[i].getTargetCoordinates());
      target_direction.setNorm(playerRadius+ballRadius+gameMargin + BALL_THROW_MARGIN);
      balls.push_back(Ball(playerCoord+target_direction, target_direction.getAngle()));
      players[i].resetCount();
    }
  }
}

void Simulation::incrementCount(){
  for(size_t i(0); i<players.size(); i++){
    players[i].incrementPlayerCount();
  }
}
void Simulation::move_balls(){
  for(size_t i(0); i<balls.size(); i++){
    double alpha = balls[i].getAngle();
    double dirNorm = ballSpeed * DELTA_T;
    Vector direction(cos(alpha), sin(alpha));
    direction.setNorm(dirNorm);

    Point newPos = balls[i].getBallCoordinates() + direction;
    balls[i].setCoords(newPos);
  }
}
void Simulation::ball_ball_collisions(){
  for (size_t i = 0; i < balls.size(); ++i){
    for (size_t j = 0; j < balls.size(); ++j){
      if(i != j){
        Segment d(balls[i].getBallCoordinates(), balls[j].getBallCoordinates());

        if (d.getLength() <= (2 * ballRadius) + gameMargin){
          balls[i].setDeath(true);
          balls[j].setDeath(true);
        }
      }
    }
  }
}
void Simulation::ball_player_collisions(){
  for (size_t i = 0; i < players.size(); ++i){
    for (size_t j = 0; j < balls.size(); ++j){
      if(i != j){
        Segment d(players[i].getPlayerCoordinates(), balls[j].getBallCoordinates());

        if (d.getLength() < (playerRadius + ballRadius + gameMargin)){
          balls[j].setDeath(true);
          players[i].got_hit();
          if(players[i].getNbt() <= MIN_LEFT_TOUCH) players[i].setDeath(true);
        }
      }
    }
  }
}

void Simulation::ball_obstacle_collisions(){
  for(size_t k(0); k<balls.size(); k++){
    Cell ballCell(balls[k].getBallCoordinates(), nbCell, SIDE);
    int x(0),y(0);
    ballCell.getCoordinates(x,y);
    double totalMargin = ballRadius + gameMargin;
    for(int i(x-1);i<=x+1;i++){
      for(int j(y-1);j<=y+1;j++){
        if(i >= 0 && i < nbCell && j >= 0 && j < nbCell){
          if (m.getMap()[i][j] > 0 && pointObstacleCollision(balls[k].getBallCoordinates(), i, j, totalMargin)){
            balls[k].setDeath(true);
            m.removeObstacle(i, j);

            //*
            //*
            //*
            //*
            ///REFRESH ICI ???????????????????????
            //*
            //*
            //*
            //*
            //*
          }
        }
      }
    }
  }
}

void Simulation::ballOutOfBoundsDeaths(){
  for (size_t i = 0; i < balls.size(); ++i){
    if ((balls[i].getBallCoordinates().inBoundary(DIM_MAX,-DIM_MAX))){
      balls[i].setDeath(true);
    }
  }
}

void Simulation::playerOutOfBoundsDeaths(){
  for (size_t i = 0; i < players.size(); ++i){
    if ((players[i].getPlayerCoordinates().inBoundary(DIM_MAX,-DIM_MAX))){
      players[i].setDeath(true);
    }
  }
}

void Simulation::purge_game(){
  purgeBalls();
  purgePlayers();

  if ((players.size() == 1 && players[0].getCount() == MAX_COUNT) or players.empty()){
    over();
  }
}

void Simulation::purgeBalls(){
  for (size_t i = 0; i < balls.size(); ++i){
    if (balls[i].getDeath()){
      balls[i] = balls.back();;
      balls.pop_back();
      std::cout << "ball " << i << " has been purged" << std::endl; //DEBUG
    }
  }
}

void Simulation::purgePlayers(){
  for (size_t i = 0; i < players.size(); ++i){
    if (players[i].getDeath()){
      players[i] = players.back();;
      players.pop_back();
      std::cout << "a player has been purged" << std::endl; //DEBUG
    }
  }
}

void Simulation::reset_targets(){}

//----------------------------DEBUG FUNCTIONS--------------------------------------



void Simulation::dump(){

  std::cout<<std::endl<<" * dumping *"<<std::endl;
  for(size_t i(0); i<players.size(); i++){
    std::cout<<"player "<<(i+1)<<" : ";
    players[i].getPlayerCoordinates().dump();
    std::cout<<"NBT: " << players[i].getNbt()<<std::endl;
  }
  std::cout<<std::endl;
  for(size_t i(0); i<balls.size(); i++){
    std::cout<<"ball "<<(i+1)<< " : ";
    balls[i].getBallCoordinates().dump();
    std::cout<< "Will die ? " << balls[i].getDeath() <<std::endl;
  }
  std::cout<<std::endl;
  std::cout<<"map size :"<<m.getMap().size()<<std::endl;
  m.dump();
  std::cout<<std::endl;
}

void Simulation::dumpPlayer(){
  std::cout<<std::endl<<"--- Player status ---"<<std::endl;
  for(size_t i(0); i < players.size(); i++){
    std::cout<<"i"<<i<<": ";
    players[i].dump();
  }
  std::cout<<"  -----"<<std::endl;
}

void Simulation::dumpFloyd(){
  int nbSpot = nbCell*nbCell-m.getNbObst();
  std::cout<<std::endl<<"--- Floyd status ---"<<std::endl;
  for(int i(0); i < nbSpot; i++){
    std::cout<<std::endl<<"|";
    for(int j(0); j < nbSpot; j++){
      std::cout<<std::setprecision(4)<<std::setw(4)<<floyd_distances[i][j]<<"|";
    }
  }
  std::cout<<std::endl;
  std::cout<<" -----"<<std::endl;
}
