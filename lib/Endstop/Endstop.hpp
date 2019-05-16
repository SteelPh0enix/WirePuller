#ifndef ENDSTOP_HPP
#define ENDSTOP_HPP
#include <Arduino.h>
#include <Globals.hpp>

//! Class representing an endstop
/*!
    Connection information: GND - Endstop - `feedback` pin (any digital pin)
*/
class Endstop {
 public:
  //! Default constructor
  /*!
      Note: If you default-construct, you have to use initialize() in order to
     use the object or every bool-returning function will return false \see
     initialize
  */
  Endstop() = default;

  //! Initializing constructor
  /*!
      \param feedback pin to which endstop is connected
  */
  Endstop(uint8_t feedback) { initialize(feedback); }

  //! Initializes the object and I/O
  /*!
      \param feedback pin to which endstop is connected
  */
  void initialize(uint8_t feedback) {
    if (initialized()) return;

    setFeedbackPin(feedback);
    pinMode(feedback, INPUT_PULLUP);
    m_initialized = true;
  }

  //! Initializes the object and I/O if `feedback` pin were set ealier
  /*!
      \return true if object has been initialized, false if pins were not set
  */
  bool initialize() {
    if (!pinsSet()) return false;
    if (initialized()) return true;

    initialize(m_feedback);
    return true;
  }

  //! Sets `feedback` pin
  /*!
      \param feedback pin to which endstop is connected
  */
  void setFeedbackPin(uint8_t feedback) {
    m_feedback = feedback;
    m_pinsSet = true;
  }

  //! Checks if pins are set
  /*!
      \return true if pins are set
      \see setFeedbackPin
  */
  bool pinsSet() const { return m_pinsSet; }

  //! Checks if object is initialized
  /*!
      \return true if object is initialized
      \see initialize
  */
  bool initialized() const { return m_initialized; }

  //! Returns endstop state
  /*!
      \return true if endstop is hit, false if not or if object is not
     initialized
  */
  bool state() const {
    if (!initialized()) return false;

    // negation, because of pullup
    return !static_cast<bool>(digitalRead(m_feedback));
  }

 protected:
  bool m_initialized{false};
  bool m_pinsSet{false};
  uint8_t m_feedback{0};
};

#endif
