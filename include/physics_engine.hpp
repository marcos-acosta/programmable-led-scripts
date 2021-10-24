#ifndef PHYSICS_ENGINE_HPP
#define PHYSICS_ENGINE_HPP

#include <stdlib.h>
#include <FastLED.h>
#include "player.hpp"

#ifndef NUM_LEDS_PRIV
  #define NUM_LEDS_PRIV 300
#endif

#ifndef sgn
  #define sgn(x) ((x>0)?(1):(-1))
#endif

class PhysicsEngine {
 public:
  CRGBArray<NUM_LEDS_PRIV>& leds_;
  Player player1_;
  Player player2_;
  uint16_t lBound_, uBound_;

  // constructors and destructors
  PhysicsEngine(CRGBArray<NUM_LEDS_PRIV>& leds, Player& player1, Player& player2, uint16_t lBound, uint16_t uBound);
  ~PhysicsEngine() = default;

  /**
   * @brief Alias for evolve
   * 
   * @return PhysicsEngine& A reference to this physics engine
   */
  PhysicsEngine& operator++();

 private:
  /**
   * @brief Checks if the current state of the system will collide in the next cycle
   */
  bool doesCollide();

  /**
   * @brief Evolves the physics engine by 1 iteration
   */
  void evolve();

  /**
   * @brief Checks the state of the engine and updates variables if collision occurs
   */
  void updateCollision();

  /**
   * @brief Updates the acceleration of the players based on the state of the system
   */
  void updateAccel();
};

#endif