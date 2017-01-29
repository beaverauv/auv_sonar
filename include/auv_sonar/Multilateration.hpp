#ifndef MULTILATERATION_H
#define MULTILATERATION_H

#include <array>
#include <functional>
#include <math.h>
#include <ros/ros.h>

typedef std::function<double(double, int)> Equation;
typedef std::function<double(Equation, Equation, double, int)> CombinedEquation;
typedef std::array<std::array<double, 2>, 10> Intersections;

class Multilateration {
public:

  Multilateration();
  ~Multilateration();

  double findFunctionIntersection(Equation f1, Equation f2, Equation fd1,
                                  Equation fd2, int sign);
  void findAllIntersections(); //finds all intersections and stores them in the
                               //Intersections type allIntersections array
  void printAllIntersections() {} //prints all the found intersection values
  auto sq(auto a) { return a * a; } //squares value a

  void findPinger(); //A vriation of findAllIntersections which checks if each
                     //point is the pinger, and breaks when it is done
  bool checkForPinger(int arrayPosition, double intersection);
                        //Checks a given interception to see if it is the pinger
  bool isPinger(); //checks if a given xCoordinate represents the xCoordinate of the pinger
  Intersections allIntersections;
  std::array<double, 2> = pingerLocation;

  double xCurrent;
  double xInitial = 10;
  double xChange = 0;
  double NewtonRaphsonXThresh = .0000000000001;
  int iteratorNewton;
  int maxIterations = 10000;
  int arrayCounter = 0;

  int xCoord = 0; //for array purposes
  int yCoord = 1; //Same

  double int0; //to more easily store the x intercept values
  double int1;
  double int2;
  double int3;
  double int4;

private:
  float mountingDistance = 1; // The distance between each hydrophone in mm


  double a = 0.115784275175;

  double b = 0.935821596706;

  double c = 0.0886131503014;

  double d = 0.855231827134;

  Equation f1 = [&](double x, int sign) {
    return xDist + (sign * sqrt((sq(xDist) - a) - ((sq(x) / a) - 1)));
  };

  Equation f2 = [&](double x, int sign) {
    return sign * sqrt(b * (1 + sq(x + xDist) / (sq(xDist) - b)));
  };

  Equation f3 = [&](double x, int sign) {
    return -1 * xDist + (sign * sqrt((sq(xDist) - c) * ((sq(x) / c) - 1)));
  };

  Equation f4 = [&](double x, int sign) {
    return sign * sqrt(d * (1 + sq(x - xDist) / (sq(xDist) - d)));
  };

  Equation fd1 = [&](double x, int sign) {
    return (sign * x * (sq(xDist) - b)  /  ( b* sqrt( (sq(x)/b - 1)* (sq(xDist) - b) ) );

  };

  Equation fd2 = [&](double x, int sign) {
    return sign * (  (b*(x+xDist))  /  ( (sq(xDist) - b) * sqrt( b * ( sq((x+xDist)) / (sq(xDist)-b) ) +1 )) );
  };

  Equation fd3 = [&](double x, int sign) {
    return (sign * x * (sq(xDist) - c)  /  ( c* sqrt( (sq(x)/c - 1)* (sq(xDist) - c) ) );
  };

  Equation fd4 = [&](double x, int sign) {
    return sign * (  (d*(x+xDist)) /  ( (sq(xDist) - d) * sqrt( d * ( sq((x+xDist)) / (sq(xDist)-d) ) +1 )) );
  };

  CombinedEquation functionCombined = [](Equation Eq1, Equation Eq2, double x,
                                         int sign) {
    return Eq1(x, sign) - Eq2(x, sign);
  };
};

#endif
