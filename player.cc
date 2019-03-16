#include <vector>
#include "player.h"

static std::vector<Player> players;

Player::Player(double x_in, double y_in, int nbt_in, int count_in)
: coordinates(x_in, y_in){
  nbt = nbt_in;
  count = count_in;
}
