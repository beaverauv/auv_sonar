#include <auv_mission_control/Hydrophones.h>

Hydrophones::Hydrophones(){
}


Hydrophones::Hydrophones(PidManager* pm, TaskVision* vision) : pm_(pm), vision_(vision){
        AUV_INFO("INIT");
}

Hydrophones::~Hydrophones(){

}

whatever array Hydrophones::sample(){
  Hydrophones::currentBit++;
  -if info isnt available, do nothing
  -if it is and continueChecking = true:


  if(currentBit <= 24){ //the first 24 bits
    -set (currentBit - 1) in bool array for first channel to this bit
    -continueChecking = true
  }
  else if(currentBit > 24 && currentBit <= 48){
    -set (currentBit - 25) in bool array for second channel to this bit
    -continueChecking = true
  }
  else if(currentBit > 48 && currentBit <= 72){
    -set (currentBit - 49) in bool array for thrid channel to this bit
    -continueChecking = true
  }
  else if(currentBit > 72 && currentBit <=96){
    -set (currentBit - 73) in bool array for fourth channel to this bit
    -continueChecking = true
  }
  else{
    -continueChecking = false
    -convert arrays to long ints
    return four long ints as array
  }
}

int Hydrophones::record(double duration, int samplesPerSecond){
  if(sampleCount < duration * samplesPerSecond){
    Hydrophones::sample()[0] = (sampleCount) of first array;
    Hydrophones::sample()[1] = (sampleCount) of second array;
    Hydrophones::sample()[2] = (sampleCount) of third array;
    Hydrophones::sample()[3] = (sampleCount) of fourth array;
  }
  else{
    return 1; //indicates that it's done
  }
}
