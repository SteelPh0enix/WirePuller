#ifndef UIDATA_HPP
#define UIDATA_HPP
#include <QHash>

namespace UIData {
enum class Axis { None = 0, X, Wheel, Breaker };

struct AxisInputData {
  bool leftEndstopState;
  bool rightEndstopState;
  int distanceTicks;
};

struct AxisOutputData {
  enum class Mode { None, SetPower, SetPosition } mode;
  int power;
  double distanceCm;
  int ticksPerCm;
  bool destinationAchieved;
};
}  // namespace UIData

#endif  // UIDATA_HPP
