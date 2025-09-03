#include "main.h"

using namespace robos;

Exit::Exit(double MinError, int SettleTime){

    ErrorRange = MinError;

    this->SettleTime = SettleTime;

}

bool Exit::Iterate(double Error){
    const int curTime = pros::millis();
    if (std::fabs(Error) > ErrorRange) StartTime = -1;
    else if (StartTime == -1) StartTime = curTime;
    else if (curTime >= StartTime + SettleTime) done = true;
    return done;
}

bool Exit::getState(){return done;}

void Exit::Reset(){

    StartTime = -1;

    done = false;

}

Params::Params(int MaxSpeed){

    this->MaxSpeed = MaxSpeed;

    ExitEarly = false;

}

Params::Params(int MaxSpeed, bool Async){

    this->MaxSpeed = MaxSpeed;

    this->Async = Async;

    this->ExitEarly = false;

}

Params::Params(float EarlyExitRange, int MinSpeed, int MaxSpeed){

    Async = false;

    this->EarlyExitRange = EarlyExitRange;

    this->MinSpeed = MinSpeed;

    this->MaxSpeed = MaxSpeed;

    ExitEarly = true;

}