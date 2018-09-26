#ifndef POLOLU_MC33926_HPP
#define POLOLU_MC33926_HPP

#include <Arduino.h>
#include <Globals.hpp>

//! Class representing a single channel of PololuMC33926 driver
class PololuMC33926 {
 public:
  //! Maximal speed of motor
  static constexpr int maxSpeed = 400;

  //! Pin connections
  struct Pinout {
    u8 PWM;
    u8 DIR;
    u8 FB;
    u8 D2;
    u8 SF;
  };

  //! Default constructor
  /*!
      Be aware that you will have to initialize the object after
     default-constructing or every bool-returning function will return false
      \see initialize
  */
  PololuMC33926() = default;

  //! Constructor with pinout
  /*!
      \param pinout pin connections of driver to Arduino
      \see Pinout
  */
  PololuMC33926(Pinout const& pinout);

  //! Initializes the object with specified driver pinout
  /*!
      \param pinout pin connections of driver to Arduino
      \see Pinout
  */
  void initialize(Pinout const& pinout);

  //! Initializes the object if pinout was set ealier
  /*!
      \return true if initialized, false if pins were not set
  */
  bool initialize();

  //! Sets pinout of driver
  /*!
      \param pinout pin connections of driver to Arduino
      \see Pinout
  */
  void setPins(Pinout const& pinout);

  //! Sets speed of motor
  /*!
      \param speed speed of motor in range -maxSpeed to maxSpeed
      \see maxSpeed
  */
  void speed(int speed);

  //! Gets speed of motor
  /*!
      \return speed speed of motor in range -maxSpeed to maxSpeed
      \see maxSpeed
  */
  int speed() const;

  //! Checks if object is initialized
  /*!
      \return true if intialized, false if not
      \see initialize
  */
  bool initialized() const;

  //! Checks if pins are set
  /*!
      \return true if pins are set, false if not
      \see setPins
  */
  bool pinsSet() const;

  //! Returns current draw of motor
  /*!
      If object is not initialized, it will always return 0
      \return current draw of motor in miliampers
  */
  uint current() const;

  //! Checks if an error happened
  /*!
      \return true if driver error occurred or object is not initialized
  */
  bool error() const;

  //! Returns pinout
  /*!
      \return driver pinout
      \see setPins
  */
  Pinout pinout() const;

 protected:
  bool m_initialized{false};
  bool m_pinsSet{false};
  Pinout m_pinout{0, 0, 0, 0, 0};
  int m_speed{0};
};

#endif
