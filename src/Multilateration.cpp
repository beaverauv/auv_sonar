#include <auv_mission_control/Multilateration.hpp>

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
    numberOfIterations++;
    if (numberOfIterations > maxIterations) {
      printf("PANIC\n");
      break;
    }
  }
  return xCurrent;
}

void Multilateration::findAllIntersections() {
  allIntersections.at(0).at(0) = findFunctionIntersection(f1, f2, fd1, fd2, 1);
  allIntersections.at(0).at(1) =
      functionCombined(f1, f2, allIntersections.at(0).at(0), 1);
  printf("%.18f, %.18f\n", allIntersections.at(0).at(0),
         allIntersections.at(0).at(1));

  allIntersections.at(1).at(0) = findFunctionIntersection(f1, f3, fd1, fd3, 1);
  allIntersections.at(1).at(1) =
      functionCombined(f1, f3, allIntersections.at(1).at(0), 1);
  printf("%.18f, %.18f\n", allIntersections.at(1).at(1),
         allIntersections.at(1).at(1));

  allIntersections.at(2).at(0) = findFunctionIntersection(f1, f4, fd1, fd4, 1);
  allIntersections.at(2).at(1) =
      functionCombined(f1, f4, allIntersections.at(2).at(0), 1);
  printf("%.18f, %.18f\n", allIntersections.at(2).at(0),
         allIntersections.at(2).at(1));

  allIntersections.at(3).at(0) = findFunctionIntersection(f2, f4, fd2, fd4, 1);
  allIntersections.at(3).at(1) =
      functionCombined(f2, f4, allIntersections.at(3).at(0), 1);
  printf("%.18f, %.18f\n", allIntersections.at(3).at(0),
         allIntersections.at(3).at(1));

  allIntersections.at(4).at(0) = findFunctionIntersection(f3, f4, fd3, fd4, 1);
  allIntersections.at(4).at(1) =
      functionCombined(f3, f4, allIntersections.at(4).at(0), 1);
  printf("%.18f, %.18f\n", allIntersections.at(4).at(0),
         allIntersections.at(4).at(1));
}

void Multilateration::findPinger(){

  int0 = findFunctionIntersection(f1, f2, fd1, fd2, 1);
  if(isPinger(int0)){
    printf("Pinger Located\n");
    return;
  }
  int1 = findFunctionIntersection(f1, f3, fd1, fd3, 1);
  if(isPinger(int1)){
    printf("Pinger Located\n");
    return;
  }
  xint2 = findFunctionIntersection(f1, f4, fd1, fd3, 1);
  if(isPinger(int2)){
    printf("Pinger Located\n");
    return;
  }
  xint3 = findFunctionIntersection(f2, f4, fd2, fd4, 1);
  if(isPinger(int3)){
    printf("Pinger Located\n");
    return;
  }
  xint4 = findFunctionIntersection(f3, f4, fd3, fd4, 1);
  if(isPinger(int4)){
    printf("Pinger Located\n");
    return;
  }
  else{
    printf("PINGER NOT LOCATED\n");
  }

}

bool Multilateration::isPinger(double intersectionXCoordinate){
  if((functionCombined(f1, f2, intersectionXCoordinate, 1) - (functionCombined(f1, f3, intersectionXCoordinate, 1) <= NewtonRaphsonXThresh) &&
    (functionCombined(f1, f3, intersectionXCoordinate, 1) - (f1, f4, intersectionXCoordinate, 1) <= NewtonRaphsonXThresh) &&
    (functionCombined(f1, f4, intersectionXCoordinate, 1) - (f3, f4, intersectionXCoordinate, 1) <= NewtonRaphsonXThresh)
    ){
      pingerLocation.at(xCoord) = intersection;
      pingerLocation.at(yCoord) = f1(intersection, 1);
      return true;
  }
  else { return false }
}

Multilateration::getSign(){
  if timeLag23 > 0{
    return 1;
  }
  else{
    return -1;
  }
}
