#include "RobosLib/Drive/DriveTrain.hpp"
#include "main.h"
#include "pros/misc.h"
#include "pros/rtos.hpp"



using namespace robos;


    DriveTrain::DriveTrain(pros::MotorGroup* RightMotors, pros::MotorGroup* LeftMotors, Inertial* Gyro, float Wheeldiameter, float RPM):
    RightMotors(RightMotors),

    LeftMotors(LeftMotors),
    Gyro(Gyro),

    DriveTask([this]{this->DriveLoop();}),

    Lateral(10,0.03,100,5),

    Angular(4.1,0.025,40,15),

    Heading(4,0.01,40,20),

    LateralExit(0.75, 80),

    AngualrExit(3, 80),
    
    Master(pros::E_CONTROLLER_MASTER),

    StoredParameters(0,false)


    {

        TickPerInch = ((50.0 * (3600.0 / RPM)))/(Wheeldiameter * M_PI);

    }

//IMPORTANT NOTE:

//I switched around the voltage so that the left motors receive what is supposed to be the right motor voltage & vice versa
//I did this because otherwise, the X axis joystick is inverted. 

void DriveTrain::PrivateVoltage(int Right, int Left){
    LeftMotors->move_voltage(Right * 12000/127);
    //RightMotors->move_voltage(Right * 12000/127);

    RightMotors->move_voltage(Left * 12000/127);
    //LeftMotors->move_voltage(Left * 12000/127);

}

void DriveTrain::ResetEncoders(){

    RightMotors->tare_position();

    LeftMotors->tare_position();

}

void DriveTrain::SetHeading(float theta){

    Gyro->SetRotation(theta);

}

void DriveTrain::Calibrate(){

    pros::delay(3000);

    Calibrated = true;

}

void DriveTrain::Op(bool Curves){

    DriveState = OP;

    double Yaw = Master.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X);

    double Throttle = Master.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);

    PrivateVoltage(Throttle + Yaw, Throttle - Yaw);

}

float DriveTrain::getEncoders(){return (RightMotors->get_position() + LeftMotors->get_position())/2;}