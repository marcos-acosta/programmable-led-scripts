#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <stdlib.h>
#include <FastLED.h>

#ifndef NUM_LEDS_PRIV
  #define NUM_LEDS_PRIV 300
#endif

#ifndef sgn
  #define sgn(x) ((x>0)?(1):(-1))
#endif

class Player {
 private:
  CRGB color_;
  uint16_t pos_;
  uint16_t scaled_pos_;
  int16_t vel_;
  int8_t acc_;

  uint16_t minPos_;
  uint16_t maxPos_;
  uint16_t maxVel_;
  uint8_t maxAcc_;

  uint8_t sf_;

  /**
   * @brief Validate the position of the player
   */
  void checkPos();
  
  void (*inc_callback)(Player&); // callback for increment

 public:
  // constructors
  Player() = delete;

  Player(
    CRGB color,
    uint8_t sf,
    uint16_t position,
    int16_t vel,
    int8_t acc,
    uint16_t maxVel,
    uint8_t maxAcc
  );

  Player(
    CRGB color,
    uint16_t position,
    int16_t vel,
    int8_t acc,
    uint16_t maxVel,
    uint8_t maxAcc
  );

  Player(
    CRGB color,
    uint16_t position,
    int16_t vel,
    int8_t acc,
    uint16_t minPos,
    uint16_t maxPos,
    uint16_t maxVel,
    uint8_t maxAcc
  );

  Player(
    CRGB color,
    uint8_t sf,
    uint16_t position,
    int16_t vel,
    int8_t acc,
    uint16_t minPos,
    uint16_t maxPos,
    uint16_t maxVel,
    uint8_t maxAcc
  );

  Player(
    CRGB color,
    uint8_t sf,
    uint16_t position,
    int16_t vel,
    int8_t acc,
    uint16_t minPos,
    uint16_t maxPos,
    uint16_t maxVel,
    uint8_t maxAcc,
    void (*callback)(Player&)
  );

  ~Player() = default;

  /**
   * @brief Gets the color of the player
   * 
   * @return CRGB The color of the player
   */
  inline CRGB getColor() const { return color_; }

  /**
   * @brief Get the raw position of the player
   * 
   * @return uint16_t The raw position of the player
   */
  inline uint16_t getRawPos() { return pos_; }

  /**
   * @brief Get the (scaled) position of the player
   * 
   * @return uint16_t The (scaled) position of the player
   */
  inline uint16_t getPos() { return scaled_pos_; }

  /**
   * @brief Gets the velocity of the player
   * 
   * @return int8_t The velocity of the player
   */
  inline int16_t getVel() { return vel_; }

  /**
   * @brief Gets the acceleration of the player
   * 
   * @return int8_t The acceleration of the player
   */
  inline int8_t getAccel() { return acc_; }

  /**
   * @brief Get the minimum position
   * 
   * @param minPos The minimum position
   */
  inline uint16_t getMinPos() { return minPos_; }

  /**
   * @brief Get the maximum position
   * 
   * @param minPos The maximum position
   */
  inline uint16_t getMaxPos() { return maxPos_; }

  /**
   * @brief Gets the max velocity of the player
   * 
   * @return int8_t The max velocity of the player
   */
  inline uint16_t getMaxVel() { return maxVel_; }

  /**
   * @brief Gets the max acceleration of the player
   * 
   * @return int8_t The max acceleration of the player
   */
  inline uint8_t getMaxAcc() { return maxAcc_; }

  /**
   * @brief Sets the raw position for the player
   * 
   * @param vel The new raw position
   */
  inline void setRawPos(uint16_t pos) { pos_ = pos; scaled_pos_ = pos_ / sf_; checkPos(); }

  /**
   * @brief Sets the (scaled) position for the player
   * 
   * @param vel The new (scaled) position
   */
  inline void setPos(uint16_t pos) { setRawPos(pos * sf_); }

  /**
   * @brief Sets the (scaled) velocity for the player
   * 
   * @param vel The new (scaled) velocity
   */
  inline void setVel(int16_t vel) { vel_ = sgn(vel) * min(maxVel_, abs(vel)); }

  /**
   * @brief Sets the acceleration for the player
   * 
   * @param vel The new acceleration
   */
  inline void setAccel(int8_t acc) { acc_ = sgn(acc) * min(maxAcc_, abs(acc)); }

  /**
   * @brief Set the minimum position
   * 
   * @param minPos The new minimum position
   */
  inline void setMinPos(uint16_t minPos) { minPos_ = minPos; }

  /**
   * @brief Set the maximum position
   * 
   * @param minPos The new maximum position
   */
  inline void setMaxPos(uint16_t maxPos) { maxPos_ = maxPos; }

  /**
   * @brief Sets the increment callback
   * 
   * @param vel The new acceleration
   */
  inline void setCallback(void (*callback)(Player&)) {
    inc_callback = callback;
  }

  /**
   * @brief Increments the player's position
   * 
   * @return Player& A reference to the player
   */
  Player& operator++();
};

#endif