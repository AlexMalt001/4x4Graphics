#ifndef serialProcess_h
#define serialProcess_h

class serialProcess {
  public:
    void sendVars(int th, int st);
};

class dataProcess {
  public:
  int processVars(int input, int upper, int lower, int deadzone, int upperPWM, int lowerPWM);
};

#endif
