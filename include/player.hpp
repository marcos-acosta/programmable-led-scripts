#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <stdlib.h>
#include <FastLED.h>

class Player {
 private:
  CRGB color_;
  uint16_t pos_;
  int8_t vel_;
  int8_t acc_;

  uint8_t maxVel_;
  uint8_t maxAcc_;
  
  void (*inc_callback)(Player&); // callback for increment

 public:
  // constructors and destructor
  Player() = delete;

  Player(
    CRGB color,
    uint16_t position,
    int8_t vel,
    int8_t acc,
    uint8_t maxVel,
    uint8_t maxAcc
  );

  Player(
    CRGB color,
    uint16_t position,
    int8_t vel,
    int8_t acc,
    uint8_t maxVel,
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
   * @brief Get the position of the player
   * 
   * @return uint16_t The position of the player
   */
  inline uint16_t& getPos() { return pos_; }

  /**
   * @brief Gets the velocity of the player
   * 
   * @return int8_t The velocity of the player
   */
  inline int8_t& getVel() { return vel_; }

  /**
   * @brief Gets the acceleration of the player
   * 
   * @return int8_t The acceleration of the player
   */
  inline int8_t& getAccel() { return acc_; }

  /**
   * @brief Gets the max velocity of the player
   * 
   * @return int8_t The max velocity of the player
   */
  inline uint8_t getMaxVel() { return maxVel_; }

  /**
   * @brief Gets the max acceleration of the player
   * 
   * @return int8_t The max acceleration of the player
   */
  inline uint8_t getMaxAcc() { return maxAcc_; }

  /**
   * @brief Sets the velocity for the player
   * 
   * @param vel The new velocity
   */
  inline void setVel(int8_t vel) { vel_ = vel; }

  /**
   * @brief Sets the acceleration for the player
   * 
   * @param vel The new acceleration
   */
  inline void setAccel(int8_t acc) { acc_ = acc; }

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