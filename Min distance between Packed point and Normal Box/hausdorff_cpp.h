#include "structures_cpp.h"
#include <algorithm>
#include <array>
#include <cmath>
#include <iostream>

inline double SquaredDistance(double x0, double y0, double x1, double y1) {
  const double squared = (x0 - x1) * (x0 - x1) + (y0 - y1) * (y0 - y1);
  return squared;
}

inline std::array<double, 8> Hausdorff_CPP(NormalBox_cpp box,
                                           PackedPoint_cpp pack) {
  std::array<double, 8> X;
  std::array<double, 8> Y;
  for (int i = 0; i < 8; i++) {
    X[i] = std::abs(pack.X[i]);
    Y[i] = std::abs(pack.Y[i]);
  }
  std::array<double, 8> result;
  for (int i = 0; i < 8; i++) {
    if (X[i] <= box.Half_Width && Y[i] <= box.Half_Height) {

      result[i] =
          SquaredDistance(X[i], Y[i], -box.Half_Width, -box.Half_Height);
    } else if (X[i] <= box.Half_Width && Y[i] > box.Half_Height) {

      result[i] =
          (SquaredDistance(X[i], Y[i], -box.Half_Width, box.Half_Height));
    } else if (X[i] > box.Half_Width && Y[i] <= box.Half_Height) {

      result[i] =
          (SquaredDistance(X[i], Y[i], box.Half_Width, -box.Half_Height));
    } else {

      const double a1 = SquaredDistance(X[i], Y[i], -box.Half_Width, box.Half_Height);
      const double a2 = SquaredDistance(X[i], Y[i], box.Half_Width, -box.Half_Height);

      result[i] = (std::max(a1, a2));
    }
  }
  return result;
}
