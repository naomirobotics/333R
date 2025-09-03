#include "Systems.hpp"
#include "Intake.hpp"
#include "pros/adi.hpp"
#include "pros/misc.h"


//right drive group
pros::MotorGroup r({10,20, -19});

//left drive group
pros::MotorGroup l({-12,-1, 11});

// pros::MotorGroup Intake({-1,-2});

//robos::Inertial IMU({6});
robos::Inertial IMU({21});

robos::DriveTrain Drive(&r,&l,&IMU,3.25,450);

pros::adi::Pneumatics Shifter(3,false);

pros::adi::Pneumatics Mogo(2,false);

pros::adi::Pneumatics RightClaw(4,false);

pros::adi::Pneumatics LeftClaw(5,false);

pros::adi::Pneumatics RightClawClamp(6,true);

pros::adi::Pneumatics LeftClawClamp(7,true);

//adi = 8 = h

pros::adi::Pneumatics matchLoader(8, false);

pros::Controller master(pros::E_CONTROLLER_MASTER);

robos::Motor brown(-3,4);

//Intake tutorial part 1:

//define ALL of the motors you want to use for the intake. To modify what they do, go to Intake.cpp and find the IntakeLoop function

//port 13 is the main intake motor.

//port 15 is the indexer.

//port 14 is for storage. 

//13 should spin forward for all three buttons

//button 1: 13 spins forward, 14 spins in reverse

//button 2: 13 spins forward, 14 spins forward, 15 spins forward

//button 3: 13 spins forward, 14 spins forward, 15 spins reverse

robos::Intake Intake({13,15, 14}); 


void PneumaticOp(){

    if(master.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_A)){

        matchLoader.toggle();
        pros::screen::print(pros::E_TEXT_MEDIUM, 3, "Piston clicked!");


    }

    if(master.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_LEFT)){

        Shifter.toggle();

    }

    if(master.get_digital(pros::E_CONTROLLER_DIGITAL_R2)){

        RightClaw.extend();

        RightClawClamp.retract();

    }else{

        RightClaw.retract();

        RightClawClamp.extend();

    }

    if(master.get_digital(pros::E_CONTROLLER_DIGITAL_L2)){

        LeftClaw.extend();

        LeftClawClamp.retract();

    }else{

        LeftClaw.retract();

        LeftClawClamp.extend();

    }

    

}



bool holdtoggle = false;

void LadyBrownOp(){

    if (master.get_digital(pros::E_CONTROLLER_DIGITAL_RIGHT)) {

        brown.Stop();

        brown.sensor.set_position(0);
    
    }

    else if (master.get_digital(pros::E_CONTROLLER_DIGITAL_UP)) {

        brown.Move(127);

        holdtoggle = true;
    
    }else if(master.get_digital(pros::E_CONTROLLER_DIGITAL_DOWN)){

        brown.Move(-127);

        holdtoggle = true;

    }else if (master.get_digital(pros::E_CONTROLLER_DIGITAL_Y)) {

        brown.MoveTo(30);

    }else if (master.get_digital(pros::E_CONTROLLER_DIGITAL_B)) {

        brown.MoveTo(2);

    }else if (master.get_digital(pros::E_CONTROLLER_DIGITAL_X)) {

        brown.MoveTo(160);

    }else{

        if (holdtoggle) {

            brown.Hold();

            holdtoggle = false;

        }
    }

}