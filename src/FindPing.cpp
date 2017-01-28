#include <auv_sonar/FindPing.h>

FindPing::FindPing(){
}

FindPing::~FindPing(){
}

bool FindPing::check(){
  -fft
  -sample to array
  -check max
  -if max > threshold: return true
  -else return false

}

double FindPing::time(){
    return ros::Time::now();
}

double FindPing::frequency(){
  -fft
  -sample to array
  -check max
  -round
  -return rounded value
}
