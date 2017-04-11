#ifndef MULTILATERATION_H
#define MULTILATERATION_H

#include <array>
#include <auv_sonar/KMeans.hpp>
#include <functional>
#include <math.h>
#include <vector>

typedef std::function<double(double, int)> Equation;
typedef std::function<double(Equation, Equation, double, int)> CombinedEquation;
typedef std::vector<std::array<double, 2>> Intersections;

template <typename T, typename... U>
size_t getAddress(std::function<T(U...)> f) {
  typedef T(fnType)(U...);
  fnType **fnPointer = f.template target<fnType *>();
  return (size_t)*fnPointer;
}

class Multilateration {
public:
  Multilateration();
  ~Multilateration();
  double findFunctionIntersection(int i1, int i2, int sign);
  void findAllIntersections(); // finds all intersections and stores them in the
  // Intersections type allIntersections array
  std::array<double, 2> loadIntersection(int i1, int i2, int sign);
  Equation getFunction(int func);
  Equation getDerivFunction(int func);
  Equation getDerivFunction(Equation eq);

  void printAllIntersections() {}   // prints all the found intersection values
  auto sq(auto a) { return a * a; } // squares value a

  void findPinger(); // A vriation of findAllIntersections which checks if each
  // point is the pinger, and breaks when it is done
  bool checkForPinger(int arrayPosition, double intersection);
  // Checks a given interception to see if it is the pinger
  bool isPinger(double intersectionXCoordinate); // checks if a given
  // xCoordinate represents the
  // xCoordinate
  // of the pinger

  void checkIntForPinger(int i1, int i2);

  Intersections allIntersections;
  std::array<double, 2> pingerLocation;

  double xCurrent;
  double xInitial = 0.0001;
  double xChange = 0;
  double xDist = 1;
  double NewtonRaphsonXThresh = 0.0001;
  int iteratorNewton;
  int maxIterations = 1000;
  int arrayCounter = 0;

  int xCoord = 0; // for array purposes
  int yCoord = 1; // Same

  double xint0; // to more easily store the x intercept values
  double xint1;
  double xint2;
  double xint3;
  double xint4;

  double distDifference12 = 0;
  double distDifference23 = 0;
  double distDifference34 = 0;
  double distDifference41 = 0;

  std::vector<Point> points;

  double timeLag23 = 0;

  int getSign();

private:
  float mountingDistance = 1; // The distance between each hydrophone in mm

  double a = 0.0552538835813;
  // double a = sq(distDifference12/2);
  double b = 0.946647542253;
  // double b = sq(distDifference23/2)
  double c = 0.0564906363378;
  // double c = sq(distDifference34/2)
  double d = 0.941563591867;
  // double d = sq(distDifference14/2)

  Equation f1 = [&](double x, int sign) {
    return xDist + (sign * sqrt((sq(xDist) - a) * (-1 + sq(x) / a)));
  };

  Equation f2 = [&](double x, int sign) {
    return sign * sqrt(b * (1 + sq(x + xDist) / (sq(xDist) - b)));
  };

  Equation f3 = [&](double x, int sign) {
    return (-1 * xDist) + (sign * sqrt((sq(xDist) - c) * ((sq(x) / c) - 1)));
  };

  Equation f4 = [&](double x, int sign) {
    return sign * sqrt(d * (1 + sq(x - xDist) / (sq(xDist) - d)));
  };

  Equation fd1 = [&](double x, int sign) {
    return sign * ((x * (sq(xDist) / a - 1)) /
                   (a * sqrt((sq(x) / a - 1) * (sq(xDist) - a))));

  };

  Equation fd2 = [&](double x, int sign) {
    return sign * (((b * (x + xDist)) /
                    ((sq(xDist) - b) *
                     sqrt(b * (sq((x + xDist)) / (sq(xDist) - b)) + 1))));
  };

  Equation fd3 = [&](double x, int sign) {
    return (sign * x * (sq(xDist) - c) /
            (c * sqrt((sq(x) / c - 1) * (sq(xDist) - c))));
  };

  Equation fd4 = [&](double x, int sign) {
    return sign * ((d * (x + xDist)) /
                   ((sq(xDist) - d) *
                    sqrt(d * (sq((x + xDist)) / (sq(xDist) - d)) + 1)));
  };

  CombinedEquation functionCombined = [](Equation Eq1, Equation Eq2, double x,
                                         int sign) {
    // printf("      %.5f - %.5f = %.5f\n", Eq1(x, sign), Eq2(x, sign),
    //        Eq1(x, sign) - Eq2(x, sign));
    return Eq1(x, sign) - Eq2(x, sign);
  };
};

#endif
