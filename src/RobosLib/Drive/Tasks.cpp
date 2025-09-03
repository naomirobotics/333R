
#include "RobosLib/Util.hpp"
#include "main.h"

using namespace robos;

void DriveTrain::DriveLoop(){

    while (true){

        if(Calibrated){

            switch (DriveState){

                case AUTO:

                    AutoTask();

                break;

                case OP:

                break;

                case DISABLED:

                break;

            }

        }    

        pros::delay(10);

    }

}

void DriveTrain::AutoTask(){

    switch (AutonState) {

        case MOVE:

            MoveTask();

        break;

        case TURNTO:

            TurnToTask();

        break;

        case ARC:

            ArcTask();

        break;
    
    }

}

void DriveTrain::MoveTask(){

    float LateralError = LateralTarget - getEncoders()/TickPerInch;

    float HeadingError = robos::angleError(AngularTarget, Gyro->getHeading());

    DistanceTraveled = getEncoders()/TickPerInch;

    float LateralOut = Lateral.Compute(LateralError);

    float HeadingOut = Heading.Compute(HeadingError);

    

        LateralOut = robos::Clamp(-LateralMaxSpeed, LateralMaxSpeed, LateralOut);

    // if(StoredParameters.ExitEarly){

    //     if(robos::sign(LateralOut) == 1){

    //         if(LateralOut < StoredParameters.MinSpeed){

    //             LateralOut = StoredParameters.MinSpeed;

    //         }

    //     }else{

    //         if(LateralOut > -StoredParameters.MinSpeed){

    //             LateralOut = -StoredParameters.MinSpeed;

    //         }

    //     }

    // }

       

    PrivateVoltage(LateralOut + HeadingOut, LateralOut - HeadingOut);

    LateralExit.Iterate(LateralError);

    Master.print(2, 1, "%f", LateralError);

}

void DriveTrain::TurnToTask(){

    float AngularError = robos::angleError(AngularTarget, Gyro->getHeading());

    float AngularOut = Angular.Compute(AngularError);

    DistanceTraveled = robos::angleError(Gyro->getHeading(), StartTheta);

    AngularOut = robos::Clamp(-AngularMaxSpeed, AngularMaxSpeed, AngularOut);

    // if(StoredParameters.ExitEarly){

    //     if(robos::sign(AngularOut) == 1){

    //         if(AngularOut < StoredParameters.MinSpeed){

    //             AngularOut = StoredParameters.MinSpeed;

    //         }

    //     }else{

    //         if(AngularOut > -StoredParameters.MinSpeed){

    //             AngularOut = -StoredParameters.MinSpeed;

    //         }

    //     }

    // }

    PrivateVoltage(AngularOut, -AngularOut);

    AngualrExit.Iterate(AngularError);

    Master.print(2, 1, "%f", AngularError);

}

void DriveTrain::ArcTask(){

    const float radius = fabs(LateralTarget / (ThetaArc *M_PI/180));

    float LateralError = LateralTarget - getEncoders()/TickPerInch;

    DistanceTraveled = getEncoders()/TickPerInch;

    const float ArcTheta = ((getEncoders()/TickPerInch) / radius) * 180 / M_PI;

    float AngularError = robos::angleError(((sign(ThetaArc))* ArcTheta) + AngularTarget, Gyro->getHeading());

    float AngularOut = Angular.Compute(AngularError);

    float LateralOut = Lateral.Compute(LateralError);

    AngularOut = robos::Clamp(-AngularMaxSpeed, AngularMaxSpeed, AngularOut);

    LateralOut = robos::Clamp(-LateralMaxSpeed, LateralMaxSpeed, LateralOut);

    // if(StoredParameters.ExitEarly){

    //     if(robos::sign(LateralOut) == 1){

    //         if(LateralOut < StoredParameters.MinSpeed){

    //             LateralOut = StoredParameters.MinSpeed;

    //         }

    //     }else{

    //         if(LateralOut > -StoredParameters.MinSpeed){

    //             LateralOut = -StoredParameters.MinSpeed;

    //         }

    //     }

    // }

    PrivateVoltage(LateralOut + AngularOut, LateralOut - AngularOut);

    LateralExit.Iterate(LateralError);

}