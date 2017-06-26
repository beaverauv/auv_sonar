#ifndef FINDPING_H
#define FINDPING_H

#include <cstdarg>
#include <ros/ros.h>
#include <stdio.h>

class FindPing {

public:
  FindPing();
  ~FindPing();

  std::string getTag() { return std::string("[Task Find Ping]"); }

  bool check();
  double time();
  double frequency();

private:
  double threshold();
};

#endif
