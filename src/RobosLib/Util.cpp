#include "Util.hpp"
#include "main.h"
#include "pros/imu.hpp"
#include <vector>

using namespace robos;

robos::Inertial::Inertial(std::vector<int> Ports):
IMU1((Ports.size() > 0) ? Ports[0] : 0),
IMU2((Ports.size() > 1) ? Ports[1] : 0),
IMU3((Ports.size() > 2) ? Ports[2] : 0),
IMU4((Ports.size() > 3) ? Ports[3] : 0),
IMU5((Ports.size() > 4) ? Ports[4] : 0)
{
    
    if(Ports.size() > 5) Ports.resize(5);

    NumOfPorts = Ports.size();

}

float robos::Inertial::getHeading(){

    float avgHeading = 0;

    switch (NumOfPorts) {

        case 1:

            avgHeading = IMU1.get_heading();

        break;

        case 2:

            avgHeading = (IMU1.get_rotation() + IMU2.get_rotation())/2;

        break;

        case 3:

            avgHeading = (IMU1.get_rotation() + IMU2.get_rotation() + IMU3.get_rotation())/3;

        break;

        case 4:

            avgHeading = (IMU1.get_rotation() + IMU2.get_rotation() + IMU3.get_rotation() + IMU4.get_rotation())/4;

        break;

        case 5:

            avgHeading = (IMU1.get_rotation() + IMU2.get_rotation() + IMU3.get_rotation() + IMU4.get_rotation() + IMU5.get_rotation())/5;

        break;
    
    }

    return robos::BoundAngle(BoundAngle(avgHeading));

}

void Inertial::SetRotation(float Theta){

    IMU1.set_rotation(Theta);

    IMU2.set_rotation(Theta);

    IMU3.set_rotation(Theta);

    IMU4.set_rotation(Theta);

    IMU5.set_rotation(Theta);

    IMU1.set_heading(BoundAngle(Theta));

}

float robos::BoundAngle(float input){

    return std::fmod(std::fmod(input, 360) + 360,360);

}

int robos::sign(float input){return (input > 0) ? 1:-1;}

float robos::Clamp(double Low, double High, double input){


    if (High < input) 
        
        return High;

    else if(Low > input)

        return Low;

    return input;

}


float robos::angleError(double target, double actual){

    target = robos::BoundAngle(target);

    target = robos::BoundAngle(target);

    const float max = 360;

    const float rawError = target - actual;

    return std::remainder(rawError, max);

}