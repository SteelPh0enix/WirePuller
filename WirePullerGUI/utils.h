#ifndef UTILS_H
#define UTILS_H

template<typename T>
inline constexpr T linearApprox(T value, T xMin, T xMax, T yMin, T yMax) {
  return ((yMax - yMin) * (value - xMin) / (xMax - xMin)) + yMin;
}

template<typename T>
constexpr int sign(T val) {
  return (T(0) < val) - (val < T(0));
}

#endif // UTILS_H
