#include "PololuMC33926.hpp"

namespace {
constexpr unsigned currentMultiplier = 9u;
}

PololuMC33926::PololuMC33926(PololuMC33926::Pinout const& pinout) {
  initialize(pinout);
}

void PololuMC33926::initialize(PololuMC33926::Pinout const& pinout) {
  if (initialized()) return;

  pinMode(pinout.PWM, OUTPUT);
  pinMode(pinout.DIR, OUTPUT);
  pinMode(pinout.FB, INPUT);
  pinMode(pinout.D2, OUTPUT);
  pinMode(pinout.SF, INPUT);

  digitalWrite(pinout.D2, HIGH);
  speed(0);

  setPins(pinout);
  m_initialized = true;
}

bool PololuMC33926::initialize() {
  if (!pinsSet()) return false;
  if (initialized()) return true;
  initialize(m_pinout);
  return true;
}

void PololuMC33926::setPins(PololuMC33926::Pinout const& pinout) {
  m_pinout = pinout;
  m_pinsSet = true;
}

void PololuMC33926::speed(int speed) {
  if (!initialized()) return;
  bool reversed{false};

  if (speed < 0) {
    speed *= -1;
    reversed = true;
  }

  if (speed > maxSpeed) speed = maxSpeed;

  /*
  Serial.print("[[[DEBUG MESSAGE]]]");
  Serial.print("Speed: ");
  Serial.print(speed);
  Serial.print(", reversed state: ");
  Serial.println(reversed);
  */

  // magic numbers here, unavoidable in any reasonable way, leave as-is.
  analogWrite(m_pinout.PWM, speed * 51 / 80);
  digitalWrite(m_pinout.DIR, reversed);

  m_speed = (reversed ? -speed : speed);
}

int PololuMC33926::speed() const { return m_speed; }

bool PololuMC33926::initialized() const { return m_initialized; }

bool PololuMC33926::pinsSet() const { return m_pinsSet; }

unsigned PololuMC33926::current() const {
  if (!initialized()) return 0u;
  return analogRead(m_pinout.FB) * currentMultiplier;
}

bool PololuMC33926::error() const {
  if (!initialized()) return true;

  return !static_cast<bool>(digitalRead(m_pinout.SF));
}
