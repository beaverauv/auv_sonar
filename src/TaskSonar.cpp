#include <auv_mission_control/TaskSonar.h>

TaskSonar::TaskSonar(){
}


TaskSonar::TaskSonar(PidManager* pm, TaskVision* vision) : pm_(pm), vision_(vision){
        AUV_INFO("INIT");
}

TaskSonar::~TaskSonar(){

}


int TaskSonar::execute(){

while(ros::ok && sonarIsActive){ ///add sonarIsActive function

switch sonarState(currentSonarStete){

  case 0:{ //waiting for ping
    if(checkForPing)
      currentSonarStete = 1;
    else
      currentSonarStete = 0;
    break;
  }

  case 1:{ //record samples
    record(channel, time, samplesPerSecond);
  }

  case 3:{ //bandpass filter them all, then cross correlate them

  }

  case 2:{ //fancy maths

  }

  case 4:{ //ros publish

  }

  default:{
    currentSonarStete = 0;
    break;
  }

}


  if(checkForPing()){
    wait 1.5 seconds;
    beginRecording();
  }
  else{

  }

}

}
