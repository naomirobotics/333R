
#include "RobosLib/Exit.hpp"
#include "main.h"
#include "pros/rtos.hpp"


using namespace robos;

void DriveTrain::Wait(){

    Timer time(CurrentTimeOut);

    while ((!LateralExit.done || !AngualrExit.done) && !time.isDone())
    
        pros::delay(10);

    
    
}

void DriveTrain::WaitUntil(float Distance){

    Timer time(CurrentTimeOut);

    while ((!LateralExit.done || !AngualrExit.done) && !time.isDone() && fabs(DistanceTraveled) < Distance)
    
        pros::delay(10);

    CurrentTimeOut = time.getTimeLeft();

}

// void DriveTrain::Move(float Target, int Timeout, int MaxSpeed, bool Async){


//     LateralTarget = Target;

//     ResetEncoders();

//     LateralMaxSpeed = MaxSpeed;

//     LateralExit.Reset();

//     Timer time(Timeout);

//     CurrentTimeOut = Timeout;

//     AutonState = MOVE;

//     DriveState = AUTO;

//     if(!Async){

//         while (!LateralExit.done && !time.isDone()) {

//             pros::delay(10);
        
//         }

//     }

// }

void DriveTrain::Move(float Target, int Timeout, Params ExitParams){

    StoredParameters = ExitParams;

    LateralTarget = Target;

    ResetEncoders();

    LateralMaxSpeed = ExitParams.MaxSpeed;

    LateralExit.Reset();

    Timer time(Timeout);

    CurrentTimeOut = Timeout;

    AutonState = MOVE;

    DriveState = AUTO;

    if(!ExitParams.Async){

        if(!ExitParams.ExitEarly){ 

            while (!LateralExit.done && !time.isDone()) {

                pros::delay(10);
            
            }

        }else{

            while ((DistanceTraveled - LateralTarget) > ExitParams.EarlyExitRange && !time.isDone()) {

                pros::delay(10);
            
            }

        }   

    }

}

void DriveTrain::TurnTo(float Target, int Timeout, int MaxSpeed, bool Async){

    StoredParameters = {MaxSpeed,Async};

    AutonState = TURNTO;

    DriveState = AUTO;

    AngularTarget = Target;

    AngularMaxSpeed = MaxSpeed;

    CurrentTimeOut = Timeout;

    AngualrExit.Reset();

    StartTheta = Gyro->getHeading();

    Timer time(Timeout);

    if(!Async){

        while (!AngualrExit.done && !time.isDone()) {

            pros::delay(10);
        
        }

    }

}

void DriveTrain::Arc(float Distance, float ThetaOffset, int Timeout, Params ExitParams){

    StoredParameters = ExitParams;
    
    AutonState = ARC;

    DriveState = AUTO;

    LateralMaxSpeed = ExitParams.MaxSpeed;

    AngularMaxSpeed = 127;

    LateralExit.Reset();

    ResetEncoders();

    AngularTarget = Gyro->getHeading();

    ThetaArc = ThetaOffset;

    LateralTarget = Distance;

    Timer time(Timeout);

    CurrentTimeOut = Timeout;

    if(!ExitParams.Async){

        

            while (!LateralExit.done && !time.isDone()) {

                pros::delay(10);
            
            }

        

        

    }

}