#pragma once

#include <chrono>

class pid{
public:
    pid(double kP, double kI, double kD, double max=100, double min=-100):
        _kP(kP), _kD(kD), _kI(kI), _lastError(0), _integral(0) {
        _lastTime = clock();
    }

    void setPoint(double val) {
        _setPoint = val;
    }

    double control(double sensedOut) {
        auto dt = float(clock()-_lastTime)/CLOCKS_PER_SEC;
        _lastTime = clock();
        auto error = _setPoint - sensedOut;
        _integral += error*dt;    
        auto derivative = (error-_lastError)/dt;
        auto ctrlSignal = _kP*error + _kI*_integral + _kD*derivative; 
        if (ctrlSignal > _maxCtrl) ctrlSignal = _maxCtrl;
        else if (ctrlSignal < _minCtrl) ctrlSignal = _minCtrl;
        _lastError = error;
        return ctrlSignal;
    }

    ~pid() {}

private:
    double _kP, _kD, _kI;
    double _maxCtrl, _minCtrl;
    double _lastError;
    double _integral;
    double _setPoint;
    clock_t _lastTime;
};

