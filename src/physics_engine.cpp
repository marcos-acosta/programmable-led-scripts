#include "physics_engine.hpp"

#include <FastLED.h>
#include <stdlib.h>

#define ACCEL_CONST 10000
#define PROB_PASS 80

PhysicsEngine::PhysicsEngine(
  CRGBArray<NUM_LEDS_PRIV>& leds,
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

  player1.setMinPos(lBound);
  player1.setMaxPos(uBound);

  player2.setMinPos(lBound);
  player2.setMaxPos(uBound);
}

bool PhysicsEngine::doesCollide() {
  static int8_t prev_dir;

  int16_t pos1 = (int16_t) player1_.getPos();
  int16_t pos2 = (int16_t) player2_.getPos();

  bool collides = prev_dir != sgn(pos1 - pos2);
  prev_dir = sgn(pos1 - pos2);

  return collides;
}

void PhysicsEngine::evolve() {
  ++player1_;
  ++player2_;

  updateCollision();
  updateAccel();

  // update leds
  leds_[player1_.getPos()] += player1_.getColor();
  leds_[player2_.getPos()] += player2_.getColor();
}

void PhysicsEngine::updateAccel() {
  int16_t sgn_dist = ((int16_t) player1_.getPos()) - ((int16_t) player2_.getPos());
  int16_t dist = abs(sgn_dist);
  int8_t sgn1 = sgn(-sgn_dist);
  int8_t sgn2 = sgn(sgn_dist);

  if (dist == 0) dist = 1;

  player1_.setAccel(sgn1 * ACCEL_CONST / dist / dist);
  player2_.setAccel(sgn2 * ACCEL_CONST / dist / dist);
}

void PhysicsEngine::updateCollision() {
  if (!doesCollide()) return;

  // random struggle time
  delay(rand() % 5 * 10);

  int8_t new_dir = rand() % 100 > PROB_PASS ? 1 : -1;

  uint8_t vel1 = (player1_.getMaxVel() / 2) + rand() % (player1_.getMaxVel() / 2);
  uint8_t vel2 = (player2_.getMaxVel() / 2) + rand() % (player2_.getMaxVel() / 2);

  player1_.setVel(new_dir * sgn(player1_.getVel()) * vel1);
  player2_.setVel(new_dir * sgn(player2_.getVel()) * vel2);
}

PhysicsEngine& PhysicsEngine::operator++() {
  evolve();
  return *this;
}
