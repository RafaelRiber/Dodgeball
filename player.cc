// EPFL - Programmation Orientée Projet (en C++) - COM-112(a)
// Projet Dodgeball
// Auteurs: Rafael RIBER  - SCIPER: 296142
//          Valentin RIAT - SCIPER: 289121

#include "player.h"

Player::Player(double x_in, double y_in, int nbt_in, int count_in)
: coordinates(x_in, y_in), next_move(0,0){
  nbt = nbt_in;
  count = count_in;
  target = nullptr;
  has_line_of_sight = false;
}

Point Player::getPlayerCoordinates() {
  return coordinates;
}

int Player::getNbt(){
  return nbt;
}

int Player::getCount(){
  return count;
}

Player* Player::getTarget(){
  return target;
}

Point Player::getTargetCoordinates(){
  if(target != nullptr){
    return target->getPlayerCoordinates();
  }
  else{
    Point p(DEFAULT_POINT);
    return p;
  }
}

bool Player::getHasLineOfSight(){
  return has_line_of_sight;
}

Vector Player::getNextMove(){
  return next_move;
}

void Player::setNextMove(Vector v){
  next_move = v;
}

void Player::setTarget(Player &targetIn){
  target = &targetIn;
}

void Player::setHasLineOfSight(bool b){
  has_line_of_sight = b;
}

void Player::make_next_move(){
  coordinates = coordinates + next_move;
}

void Player::got_hit(){
  nbt--;
}

void Player::incrementPlayerCount(){
  if (count != 20) ++count;
}

void Player::resetCount(){
  count = 0;
}

void Player::setDeath(bool willDie_in){
  willDie = willDie_in;
}
bool Player::getDeath(){
  return willDie;
}

void Player::dump(){
  std::cout<<"Player : (";
  coordinates.dump();
  std::cout<<"),nbt : "<<nbt<<", count : "<<count<< ", target : ";
  if(target == nullptr){
    std::cout<<"none";
  }else{
    std::cout<<"(";
    target->getPlayerCoordinates().dump();
    std::cout<<") ";
  }
  std::cout<<", LOS? "<<has_line_of_sight<<std::endl;

}
