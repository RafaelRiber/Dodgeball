// EPFL - Programmation Orientée Projet (en C++) - COM-112(a)
// Projet Dodgeball
// Auteurs: Rafael RIBER  - SCIPER: 296142
//          Valentin RIAT - SCIPER: 289121

#include "player.h"

Player::Player(double x_in, double y_in, int nbt_in, int count_in)
: coordinates(x_in, y_in){
  nbt = nbt_in;
  count = count_in;
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

void Player::setTarget(Player targetIn){
  target = &targetIn;
}

Player* Player::getTarget(){
  return target;
}
