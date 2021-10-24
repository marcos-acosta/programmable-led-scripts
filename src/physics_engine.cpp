#include "physics_engine.hpp"

#include <FastLED.h>
#include <stdlib.h>

#define ACCEL_CONST 10000

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

  updateState();
  updateAccel();

  // update leds
  (*leds_)[player1_.getPos()] += player1_.getColor();
  (*leds_)[player2_.getPos()] += player2_.getColor();
}

void PhysicsEngine::updateAccel() {
  int16_t sgn_dist = ((int16_t) player1_.getPos()) - ((int16_t) player2_.getPos());
  int16_t dist = abs(sgn_dist);
  int8_t sgn1 = sgn(-sgn_dist);
  int8_t sgn2 = sgn(sgn_dist);

  if (dist == 0) dist = 1;

  player1_.setAccel(sgn1 * ACCEL_CONST / dist / dist);
  player2_.setAccel(sgn2 * ACCEL_CONST / dist / dist);

  // Serial.println(dist);
  // Serial.println(ACCEL_CONST / dist / dist);
  // Serial.println(player1_.getPos());
  // Serial.println(player1_.getVel());
  // Serial.println(player1_.getAccel());
  // Serial.println(player2_.getAccel());
  // Serial.println();
}

void PhysicsEngine::updateState() {
  if (doesCollide()) {
    int8_t sign = rand() % 2 ? 1 : -1;

    uint8_t vel1, vel2;
    do {
      vel1 = (player1_.getMaxVel() / 2) + rand() % (player1_.getMaxVel() / 2);
    } while (!vel1);
    
    do {
      vel2 = (player2_.getMaxVel() / 2) + rand() % (player2_.getMaxVel() / 2);
    } while (!vel2);

    player1_.setVel(sign * vel1);
    player2_.setVel(-sign * vel2);

    // Serial.println(sign * vel1);
    // Serial.println(-sign * vel2);
    // Serial.println();
  }
}

PhysicsEngine& PhysicsEngine::operator++() {
  evolve();
  return *this;
}
