#include <iostream>
#include <chrono>
#include <windows.h>

#include "pid.h"

int main() {
    const clock_t begin_time = clock();
    
    pid myPid = pid(0.2, 0.5, 0.01);//kP, kD, kI
    double sensedOut = 5;
    myPid.setPoint(0);
    double ctrlSignal=0;
    for (int i=0; i<100; i++) {
        std::cout << "sensed out: " << sensedOut << ", ctrlSignal: " << ctrlSignal <<std::endl;
        ctrlSignal = myPid.control(sensedOut);
        sensedOut += ctrlSignal;
        Sleep(100);
    }

    return 0;
}

