#include "physics_engine.hpp"

#include <FastLED.h>
#include <stdlib.h>

static bool checkCollision(Player& player1, Player& player2) {
  uint16_t& pos1a = player1.getPos();
  uint16_t& pos2a = player2.getPos();

  uint16_t pos1b = player1.getPos() + player1.getVel();
  uint16_t pos2b = player2.getPos() + player2.getVel();

  return (abs(pos1a - pos2a) > abs(pos1b - pos2b) && abs(pos1b - pos2b) < 5);
}

void PhysicsEngine::checkPos(Player& player) {
  uint16_t pos = player.getPos();
  int8_t& vel = player.getVel();
  int8_t& acc = player.getAccel();

  // make sure we don't go below the lower bound
  pos = max(lBound_, pos);

  // make sure we don't go above the upper bound
  pos = min(uBound_, pos);

  if (pos == lBound_) {
    vel = abs(vel);
    acc = abs(acc);
  }

  if (pos == uBound_) {
    vel = -abs(vel);
    acc = -abs(acc);
  }
}

PhysicsEngine::PhysicsEngine(
  CRGBArray<NUM_LEDS_PRIV> *leds,
  Player& player1,
  Player& player2,
  uint16_t lBound,
  uint16_t uBound
):  leds_{leds},
    player1_{player1},
    player2_{player2},
    lBound_{lBound},
    uBound_{uBound} {
  // nothing to instantiate
}

void PhysicsEngine::evolve() {
  ++player1_;
  ++player2_;

  checkState();

  // update leds
  (*leds_)[player1_.getPos()] += player1_.getColor();
  (*leds_)[player2_.getPos()] += player2_.getColor();
}

void PhysicsEngine::checkState() {
  // check positions
  checkPos(player1_);
  checkPos(player2_);

  if (checkCollision(player1_, player2_) && rand() % 2) {
    int8_t sign = rand() % 2 ? 1 : -1;

    uint8_t vel1, vel2;
    do {
      vel1 = rand() % player1_.getMaxVel();
    } while (!vel1);
    
    do {
      vel2 = rand() % player2_.getMaxVel();
    } while (!vel2);

    uint8_t acc1 = rand() % 3 - 1;
    uint8_t acc2 = rand() % 3 - 1;

    player1_.setVel(sign * vel1);
    player1_.setAccel(-sign * acc1);

    player2_.setVel(-sign * vel2);
    player2_.setAccel(sign * acc2);
  }
}

PhysicsEngine& PhysicsEngine::operator++() {
  evolve();
  return *this;
}
