#ifndef serialProcess_h
#define serialProcess_h

namespace serialProcess {
    void sendVars(int th, int st);
}

namespace dataProcess {
  int processVars(int input, int upper, int lower, int deadzone, int upperPWM, int lowerPWM);
}

#endif
