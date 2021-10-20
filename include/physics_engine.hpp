#ifndef PHYSICS_ENGINE_HPP
#define PHYSICS_ENGINE_HPP

#include <stdlib.h>
#include <FastLED.h>
#include "player.hpp"

#define NUM_LEDS_PRIV 300

class PhysicsEngine {

 public:
  CRGBArray<NUM_LEDS_PRIV> *leds_;
  Player player1_;
  Player player2_;
  uint16_t lBound_, uBound_;

  // constructors and destructors
  PhysicsEngine(CRGBArray<NUM_LEDS_PRIV> *leds, Player& player1, Player& player2, uint16_t lBound, uint16_t uBound);
  ~PhysicsEngine() = default;

  /**
   * @brief Evolves the physics engine by 1 iteration
   */
  void evolve();

  /**
   * @brief Checks the state of the engine and updates variables as needed
   */
  void checkState();

  /**
   * @brief Alias for evolve
   * 
   * @return PhysicsEngine& A reference to this physics engine
   */
  PhysicsEngine& operator++();

 private:
  /**
   * @brief Checks the position of a player enforces the restrictions
   * 
   * @param player The player to check the position of
   */
  void checkPos(Player& player);
};

#endif