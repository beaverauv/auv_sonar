#include <auv_sonar/Multilateration.hpp>
#include <limits>

Multilateration::Multilateration() {}

Multilateration::~Multilateration() {}

double Multilateration::findFunctionIntersection(int i1, int i2, int sign) {
  xCurrent = xInitial;
  xChange = 1;
  int numberOfIterations = 0;
  while (fabs(xChange) > NewtonRaphsonXThresh) {
    xChange =
        functionCombined(getFunction(i1), getFunction(i2), xCurrent, sign) /
        functionCombined(getDerivFunction(i1), getDerivFunction(i2), xCurrent,
                         sign);
    // printf("%f", xChange);
    xCurrent -= xChange;
    numberOfIterations++;
    if (numberOfIterations > maxIterations) {
      return std::numeric_limits<double>::quiet_NaN();
    }
  }

  return xCurrent;
}

std::array<double, 2> Multilateration::loadIntersection(int i1, int i2,
                                                        int sign) {
  std::array<double, 2> arr{};
  arr.at(0) = findFunctionIntersection(i1, i2, sign);
  arr.at(1) = getFunction(i1)(arr.at(0), sign);
  printf("%d, %d: %.5f, %.5f, sign: %d\n", i1, i2, arr.at(0), arr.at(1), sign);
  return arr;
}

Equation Multilateration::getFunction(int func) {
  switch (func) {
  case 1:
    return f1;
  case 2:
    return f2;
  case 3:
    return f3;
  case 4:
    return f4;
  }
}

Equation Multilateration::getDerivFunction(int func) {
  switch (func) {
  case 1:
    return fd1;
  case 2:
    return fd2;
  case 3:
    return fd3;
  case 4:
    return fd4;
  }
}

Equation Multilateration::getDerivFunction(Equation eq) {
  if (getAddress(eq) == getAddress(f1))
    return fd1;
  if (getAddress(eq) == getAddress(f2))
    return fd2;
  if (getAddress(eq) == getAddress(f3))
    return fd3;
  if (getAddress(eq) == getAddress(f4))
    return fd4;
}

void Multilateration::findAllIntersections() {
  double lowerBound = -1.5;
  double upperBound = 1.5;

  for (double i = lowerBound; i < upperBound; i += 0.1) {
    xInitial = i;
    // printf("%f\n", i);

    for (int i = 1; i < 5; i++) {
      int q = i + 1;
      if (q == 5)
        q = 1;
      // printf("%d, %d\n", i, q);
      std::vector<double> valuesP, valuesN;
      double tempCeptP = findFunctionIntersection(i, q, 1);
      double tempCeptN = findFunctionIntersection(i, q, -1);

      if (!std::isnan(tempCeptP)) {
        valuesP.push_back(tempCeptP);
        valuesP.push_back(getFunction(i)(tempCeptP, 1));
        // printf("%f, %f\n", tempCeptP, getFunction(i)(tempCeptP, 1));
        Point p(points.size(), valuesP);
        points.push_back(p);
      }

      if (!std::isnan(tempCeptN)) {
        valuesN.push_back(tempCeptN);
        valuesN.push_back(getFunction(i)(tempCeptN, -1));
        // printf("%f, %f\n", tempCeptN, getFunction(i)(tempCeptN, -1));

        Point p(points.size(), valuesN);
        points.push_back(p);
      }
    }
  }
  int total_points = points.size();
  int total_values = 2;
  int max_iterations = 100;

  KMeans kmeans(3, total_points, total_values, max_iterations);

  std::vector<double> pinger = kmeans.run(points);
  std::cout << "PINGER FOUND AT " << pinger.at(0) << ", " << pinger.at(1)
            << std::endl;
}

void Multilateration::checkIntForPinger(int i1, int i2) {
  double xint = findFunctionIntersection(i1, i2, 1);
  printf("Found function intersection for %d and %d at %f\n", i1, i2, xint);
  if (isPinger(xint)) {
    printf("pinger found\n");
    printf("Intersection %.5f, %.5f\n", pingerLocation.at(0),
           pingerLocation.at(1));
    return;
  } else {
    printf("Pinger not found\n");
  }
}

void Multilateration::findPinger() {

  checkIntForPinger(1, 2);

  checkIntForPinger(1, 3);

  checkIntForPinger(1, 4);

  checkIntForPinger(2, 3);

  checkIntForPinger(2, 4);

  checkIntForPinger(3, 4);
}

bool Multilateration::isPinger(double intersectionXCoordinate) {
  int sign;
  if (std::isnan(intersectionXCoordinate))
    return false;
  double onetwo = fabs(functionCombined(f1, f2, intersectionXCoordinate, 1));
  double twothree = fabs(functionCombined(f2, f3, intersectionXCoordinate, 1));
  double onefour = fabs(functionCombined(f1, f4, intersectionXCoordinate, 1));
  double threefour = fabs(functionCombined(f3, f4, intersectionXCoordinate, 1));

  printf("%f, %f, %f, %f\n", onetwo, twothree, onefour, threefour);
  printf("%f - %f = %f\n", onetwo, twothree, onetwo - twothree);
  printf("%f - %f = %f\n", twothree, onefour, twothree - onefour);
  printf("%f - %f = %f\n", onefour, threefour, onefour - threefour);

  bool onetwotwothree = ((onetwo - twothree) <= 0.1);
  bool twothreeonefour = ((twothree - onefour) <= 0.1);
  bool onefourthreefour = ((onefour - threefour) <= 0.1);

  // printf("%.5f - %.5f = %.5f\n", fabs(f1(intersectionXCoordinate, 1)),
  //        fabs(f2(intersectionXCoordinate, 1)),
  //        fabs(f1(intersectionXCoordinate, 1)) -
  //            fabs(f2(intersectionXCoordinate, 1)));
  if (fabs(f1(intersectionXCoordinate, 1)) -
          fabs(f2(intersectionXCoordinate, 1)) ==
      0) {
    sign = 1;
  } else {
    sign = -1;
  }
  printf("sign %d\n", sign);

  if (onetwotwothree && twothreeonefour && onefourthreefour) {
    pingerLocation.at(xCoord) = intersectionXCoordinate;
    pingerLocation.at(yCoord) = f3(intersectionXCoordinate, sign);
    return true;
  } else {
    return false;
  }
}

int Multilateration::getSign() {
  if (timeLag23 > 0) {
    return 1;
  } else {
    return -1;
  }
}
