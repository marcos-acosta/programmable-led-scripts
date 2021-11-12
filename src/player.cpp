#include "player.hpp"

#include <stdlib.h>

#define DEFAULT_SF 10

Player::Player(
  CRGB color,
  uint16_t position,
  int16_t velocity,
  int8_t accel,
  uint16_t maxVel,
  uint8_t maxAcc
):  color_{color},
    scaled_pos_{position},
    vel_{velocity},
    acc_{accel},
    minPos_{0},
    maxPos_{NUM_LEDS_PRIV},
    maxVel_{maxVel},
    maxAcc_{maxAcc},
    sf_{DEFAULT_SF} {
  
  pos_ = scaled_pos_ * (uint16_t) sf_;
  inc_callback = nullptr;
}

Player::Player(
  CRGB color,
  uint8_t sf,
  uint16_t position,
  int16_t velocity,
  int8_t accel,
  uint16_t maxVel,
  uint8_t maxAcc
):  color_{color},
    scaled_pos_{position},
    vel_{velocity},
    acc_{accel},
    minPos_{0},
    maxPos_{NUM_LEDS_PRIV},
    maxVel_{maxVel},
    maxAcc_{maxAcc},
    sf_{sf} {
  
  pos_ = scaled_pos_ * (uint16_t) sf_;
  inc_callback = nullptr;
}

Player::Player(
  CRGB color,
  uint16_t position,
  int16_t velocity,
  int8_t accel,
  uint16_t minPos,
  uint16_t maxPos,
  uint16_t maxVel,
  uint8_t maxAcc
):  color_{color},
    scaled_pos_{position},
    vel_{velocity},
    acc_{accel},
    minPos_{minPos},
    maxPos_{maxPos},
    maxVel_{maxVel},
    maxAcc_{maxAcc},
    sf_{DEFAULT_SF} {
  
  pos_ = scaled_pos_ * sf_;
  inc_callback = nullptr;
}

Player::Player(
  CRGB color,
  uint8_t sf,
  uint16_t position,
  int16_t velocity,
  int8_t accel,
  uint16_t minPos,
  uint16_t maxPos,
  uint16_t maxVel,
  uint8_t maxAcc
):  color_{color},
    scaled_pos_{position},
    vel_{velocity},
    acc_{accel},
    minPos_{minPos},
    maxPos_{maxPos},
    maxVel_{maxVel},
    maxAcc_{maxAcc},
    sf_{sf} {
  
  pos_ = scaled_pos_ * sf_;
  inc_callback = nullptr;
}

Player::Player(
  CRGB color,
  uint8_t sf,
  uint16_t position,
  int16_t velocity,
  int8_t accel,
  uint16_t minPos,
  uint16_t maxPos,
  uint16_t maxVel,
  uint8_t maxAcc,
  void (*callback)(Player&)
):  color_{color},
    pos_{position},
    vel_{velocity},
    acc_{accel},
    minPos_{minPos},
    maxPos_{maxPos},
    maxVel_{maxVel},
    maxAcc_{maxAcc},
    sf_{sf},
    inc_callback{callback} {
  
  pos_ = scaled_pos_ * sf_;
}

void Player::checkPos() {
  // make sure we don't go below the lower bound
  scaled_pos_ = max(minPos_, scaled_pos_);

  // make sure we don't go above the upper bound
  scaled_pos_ = min(maxPos_, scaled_pos_);

  if (scaled_pos_ == minPos_) {
    setVel(abs(vel_));
  }

  if (scaled_pos_ == maxPos_) {
    setVel(-abs(vel_));
  }
}

Player& Player::operator++() {
  // updating position and velocity
  pos_ += vel_;
  vel_ += acc_;
  
  scaled_pos_ = pos_ / sf_;

  // adding max caps if necessary
  if (abs(vel_) > maxVel_)
    vel_ = sgn(vel_) * maxVel_;

  if (abs(acc_) > maxAcc_)
    acc_ = sgn(acc_) * maxAcc_;

  checkPos();

  if (inc_callback)
    inc_callback(*this);

  return *this;
}
