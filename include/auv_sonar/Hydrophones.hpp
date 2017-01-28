#ifndef HYDROPHONES_H;
#define HYDROPHONES_H;

class Hydrophones{

public:
  Hydrophones();
  ~hydrophones();

  std::string getTag(){
          return std::string("[Hydrophones]");
  }

  four of those weird arrays for xcorr;

  array sample();
  int record(double duration, int samplesPerSecond); //some weird array type

private:

  int firstBit;
  int currentBit = 0;
  int sampleCount = 0;
  bool continueChecking = true;
}

#endif
