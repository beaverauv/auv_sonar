#ifndef FINDPING_H
#define FINDPING_H


#include <stdio.h>
#include <cstdarg>
#include <ros/ros.h>

class FindPing{

public:

  FindPing();
  ~FindPing();

  std::string getTag(){
          return std::string("[Task Find Ping]");
  }

  bool check();
  double time();
  double frequency();

private:

  double threshold();

}

#endif
