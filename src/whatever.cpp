int0 = findFunctionIntersection(f1, f2, fd1, fd2, 1);
allIntersections.at(0).at(0) = int0;
allIntersections.at(0).at(1) =
    functionCombined(f1, f2, int0, 1);

if(isPinger(int0){
  pingerLocation.at(xCoord) = int0;
  if(isnan(f1(int0, 1))){
    pingerLocation.at(yCoord) = f1(int0, 1);
  }
  else{
    pingerLocation.at(yCoord) = f1(int0, -1);
  }
  return;
}

printf("%.18f, %.18f\n", int0,
       allIntersections.at(0).at(1));


int1 = findFunctionIntersection(f1, f3, fd1, fd3, 1);

allIntersections.at(1).at(0) = int1;
allIntersections.at(1).at(1) =
    functionCombined(f1, f3, int1, 1);

if(isPinger(int1){
  pingerLocation.at(xCoord) = int1;
  if(isnan(f1(int1, 1))){
    pingerLocation.at(yCoord) = f1(int1, 1);
  }
  else{
    pingerLocation.at(yCoord) = f1(int1, -1);
  }
  return;
}

printf("%.18f, %.18f\n", int1,
       allIntersections.at(1).at(1));

int2 = findFunctionIntersection(f1, f4, fd1, fd4, 1);
allIntersections.at(2).at(0) = int2;
allIntersections.at(2).at(1) =
    functionCombined(f1, f4, int2, 1);

if(isPinger(int2){
  pingerLocation.at(xCoord) = int2;
  if(isnan(f1(int2, 1))){
    pingerLocation.at(yCoord) = f1(int2, 1);
  }
  else{
    pingerLocation.at(yCoord) = f1(int2, -1);
  }
  return;
}

printf("%.18f, %.18f\n", int2,
       allIntersections.at(2).at(1));

int3 = findFunctionIntersection(f2, f4, fd2, fd4, 1);
allIntersections.at(3).at(0) = int3;
allIntersections.at(3).at(1) =
   functionCombined(f1, f4, int3, 1);

if(isPinger(int3){
 pingerLocation.at(xCoord) = int3;
 if(isnan(f1(int3, 1))){
   pingerLocation.at(yCoord) = f1(int3, 1);
 }
 else{
   pingerLocation.at(yCoord) = f1(int3, -1);
 }
 return;
}

printf("%.18f, %.18f\n", int3,
allIntersections.at(3).at(1));

int4 = findFunctionIntersection(f3, f4, fd3, fd4, 1);
allIntersections.at(4).at(0) = int4;
allIntersections.at(4).at(1) =
   functionCombined(f3, f4, int4, 1);

if(isPinger(int4){
 pingerLocation.at(xCoord) = int4;
 if(isnan(f1(int4, 1))){
   pingerLocation.at(yCoord) = f1(int4, 1);
 }
 else{
   pingerLocation.at(yCoord) = f1(int4, -1);
 }
 return;
}

printf("%.18f, %.18f\n", int4,
      allIntersections.at(4).at(1));
