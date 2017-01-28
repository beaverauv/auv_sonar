#ifndef TASKSONAR_H
#define TASKSONAR_H

class TaskSonar{

public:
  TaskSonar();
  ~TaskSonar();

  std::string getTag(){
          return std::string("[Sonar Main]");
  }

  int execute();

private:
  int recordTime = 2; //time to record, in seconds
  int samplesPerSecond = 128906; //samples per second (calculated per ti ads1274 datasheet)

};

#endif
