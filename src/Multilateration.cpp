#include <auv_sonar/Multilateration.hpp>
#include <limits>

Multilateration::Multilateration() {}

Multilateration::~Multilateration() {}

double Multilateration::findFunctionIntersection(Equation f1, Equation f2,
                                                 Equation fd1, Equation fd2,
                                                 int sign) {
  xCurrent = xInitial;
  xChange = 1;
  int numberOfIterations = 0;
  while (fabs(xChange) > NewtonRaphsonXThresh) {
    xChange = functionCombined(f1, f2, xCurrent, sign) /
              functionCombined(fd1, fd2, xCurrent, sign);
    xCurrent -= xChange;
    // printf("xChange: %f\n", xChange);
    // printf("xCurrent: %f\n", xCurrent);
    numberOfIterations++;
    if (numberOfIterations > maxIterations) {
      // printf("PANIC\n");
      return std::numeric_limits<double>::quiet_NaN();
    }
  }

  return xCurrent;

}

void Multilateration::findAllIntersections() {
  allIntersections.at(0).at(0) = findFunctionIntersection(f1, f2, fd1, fd2, 1);
  allIntersections.at(0).at(1) =
      functionCombined(f1, f2, allIntersections.at(0).at(0), 1);
  printf("%.5f, %.5f\n", allIntersections.at(0).at(0),
         allIntersections.at(0).at(1));

  allIntersections.at(1).at(0) = findFunctionIntersection(f1, f3, fd1, fd3, 1);
  allIntersections.at(1).at(1) =
      functionCombined(f1, f3, allIntersections.at(1).at(0), 1);
  printf("%.5f, %.5f\n", allIntersections.at(1).at(1),
         allIntersections.at(1).at(1));

  allIntersections.at(2).at(0) = findFunctionIntersection(f1, f4, fd1, fd4, 1);
  allIntersections.at(2).at(1) =
      functionCombined(f1, f4, allIntersections.at(2).at(0), 1);
  printf("%.5f, %.5f\n", allIntersections.at(2).at(0),
         allIntersections.at(2).at(1));

  allIntersections.at(3).at(0) = findFunctionIntersection(f2, f4, fd2, fd4, 1);
  allIntersections.at(3).at(1) =
      functionCombined(f2, f4, allIntersections.at(3).at(0), 1);
  printf("%.5f, %.5f\n", allIntersections.at(3).at(0),
         allIntersections.at(3).at(1));

  allIntersections.at(4).at(0) = findFunctionIntersection(f3, f4, fd3, fd4, 1);
  allIntersections.at(4).at(1) =
      functionCombined(f3, f4, allIntersections.at(4).at(0), 1);
  printf("%.5f, %.5f\n", allIntersections.at(4).at(0),
         allIntersections.at(4).at(1));
}

void Multilateration::findPinger() {

  xint0 = findFunctionIntersection(f1, f2, fd1, fd2, 1);
  printf("Found function intersection for 1 and 2 at %f\n", xint0);
  if (isPinger(xint0)) {
    printf("Intersection %.5f, %.5f\n", pingerLocation.at(0),
           pingerLocation.at(1));
    return;
  } else {
    printf("Pinger not found\n");
  }
  xint1 = findFunctionIntersection(f1, f3, fd1, fd3, 1);
  printf("Found function intersection for 1 and 3 at %f\n", xint1);
  if (isPinger(xint1)) {
    printf("Intersection %.5f, %.5f\n", pingerLocation.at(0),
           pingerLocation.at(1));
    printf("Pinger Located13\n");
    return;
  } else {
    printf("Pinger not found\n");
  }
  xint2 = findFunctionIntersection(f1, f4, fd1, fd4, 1);
  printf("Found function intersection for 1 and 4 at %f\n", xint2);
  if (isPinger(xint2)) {
    printf("Intersection %.5f, %.5f\n", pingerLocation.at(0),
           pingerLocation.at(1));
    printf("Pinger Located14\n");
    return;
  } else {
    printf("Pinger not found\n");
  }
  xint3 = findFunctionIntersection(f2, f4, fd2, fd4, 1);
  printf("Found function intersection for 2 and 4 at %f\n", xint3);
  if (isPinger(xint3)) {
    printf("Intersection %.5f, %.5f\n", pingerLocation.at(0),
             pingerLocation.at(1));
    printf("Pinger Located24\n");
    return;
  } else {
    printf("Pinger not found\n");
  }
  xint4 = findFunctionIntersection(f3, f4, fd3, fd4, 1);
  printf("Found function intersection for 3 and 4 at %f\n", xint4);
  if (isPinger(xint4)) {
    printf("Intersection %.5f, %.5f\n", pingerLocation.at(0),
           pingerLocation.at(1));
    printf("Pinger Located34\n");
    return;
  } else {
    printf("Pinger not found\n");
  }
}

bool Multilateration::isPinger(double intersectionXCoordinate) {
  int sign;
  if isnan(intersectionXCoordinate)
    return false;
  double onetwo = fabs(functionCombined(f1, f2, intersectionXCoordinate, 1));
  double twothree = fabs(functionCombined(f2, f3, intersectionXCoordinate, 1));
  double onefour = fabs(functionCombined(f1, f4, intersectionXCoordinate, 1));
  double threefour = fabs(functionCombined(f3, f4, intersectionXCoordinate, 1));

  bool onetwotwothree = ((onetwo - twothree) <= 0.1);
  bool twothreeonefour = ((twothree - onefour) <= 0.1);
  bool onefourthreefour = ((onefour - threefour) <= 0.1);

  if(fabs(f1(intersectionXCoordinate, 1)) - fabs(f2(intersectionXCoordinate, 1)) == 0){
    sign = 1;
  }
  else{
    sign = -1;
  }
  printf("sign %d", sign);

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
