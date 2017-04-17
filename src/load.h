#ifndef load_h
#define load_h

#include "Arduino.h"
#include "screen.h"



namespace load {
    using namespace eraseManager;
    void modeSet();
    void serialSetup();
    static eraseManager::screenObjectArray objectArray;
}
 
namespace pins {
  
    
}

#endif
