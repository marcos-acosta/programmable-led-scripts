#include "player.hpp"

#include <stdlib.h>
#define sgn(x) x > 0 ? 1 : -1

Player::Player(
  CRGB color,
  uint16_t position,
  int8_t velocity,
  int8_t accel,
  uint8_t maxVel,
  uint8_t maxAcc
):  color_{color},
    pos_{position},
    vel_{velocity},
    acc_{accel},
    maxVel_{maxVel},
    maxAcc_{maxAcc} {
  inc_callback = nullptr;
}

Player::Player(
  CRGB color,
  uint16_t position,
  int8_t velocity,
  int8_t accel,
  uint8_t maxVel,
  uint8_t maxAcc,
  void (*callback)(Player&)
):  color_{color},
    pos_{position},
    vel_{velocity},
    acc_{accel},
    maxVel_{maxVel},
    maxAcc_{maxAcc},
    inc_callback{callback} {
  // nothing to initialize
}

Player& Player::operator++() {
  // updating position and velocity
  pos_ += vel_;
  vel_ += acc_;

  // adding max caps if necessary
  if (abs(vel_) > maxVel_)
    vel_ = sgn(vel_) * maxVel_;

  if (abs(acc_) > maxAcc_)
    acc_ = sgn(acc_) * maxAcc_;

  if (inc_callback)
    inc_callback(*this);

  return *this;
}
