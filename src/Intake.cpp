#include "main.h"
#include "pros/misc.h"

using namespace robos;

Intake::Intake(std::vector<int> Motors):
IntakeTask([this]{this->IntakeLoop();}),
c1(10),
Master(pros::E_CONTROLLER_MASTER),
d1(14)
{

    for(auto i : Motors){

        pros::Motor temp(i);

        IntakeMotors.push_back(temp);

    }

    c1.set_integration_time(1);

    c1.set_led_pwm(127);

    


    State = Moving;


}

void Intake::Move(int volt, int index){

    State = Moving;

    PrivateVoltage(Clamp(-127, 127, volt), index);

}

void Intake::ON(){

    State = On;

}

void Intake::OFF(){

    State = Off;

}

void Intake::REVERSED(){

    State = Reversed;

}

void Intake::PrivateVoltage(int input, int index){

    if (index == -1) {

    for (auto i : IntakeMotors)

        i.move_voltage(input *(12000/127.0));


    }else{

    IntakeMotors[index].move_voltage(input * (12000/127.0));

    }

}



void Intake::OP(){

    State = Op;

}

void Intake::ColorSortOn(bool Enabled){

    ColorSort = Enabled;

}

void Intake::SetColor(robos::Colors i){

    Color = i;

}

//Modify the function below to control which button controls which motors

void Intake::IntakeLoop(){

    while (true) {

    switch (State){

        case On:

            if (ColorSort) {

                PrivateVoltage(127);

                switch (Color) {

                    case Red:

                     if ((c1.get_hue() > 340 || c1.get_hue() < 30) && d1.get_distance() < 90) {
                            
                            pros::Task::delay(scanDelay);
                            PrivateVoltage(-127);
                            pros::Task::delay(throwDelay);
                            PrivateVoltage(127);                    
                    }


                    break;

                    case Blue:

                    if (c1.get_hue() > 190 && c1.get_hue() < 230 && d1.get_distance() < 90) {
                            
                            pros::Task::delay(scanDelay);
                            PrivateVoltage(-127);
                            pros::Task::delay(throwDelay);
                            PrivateVoltage(127);                    
                        }

                    break;

                    


                
                }

                

                
            
            }else{


            if (IntakeMotors[1].get_efficiency() < 1 && Fail) {

                PrivateVoltage(127);

                pros::Task::delay(50);
                
                PrivateVoltage(-127);

                pros::Task::delay(100);

            
            }

            PrivateVoltage(127);

            }

        break;

        case Off:

            PrivateVoltage(0);

        break;

        case Reversed:

            PrivateVoltage(-127);

        break;

        case Op:



            if (ColorSort) {

                
                switch (Color) {

                    case Red:
                    
                        if ((c1.get_hue() > 350 || c1.get_hue() < 30) && Master.get_digital(pros::E_CONTROLLER_DIGITAL_R1) && d1.get_distance() < 90) {
                            
                            pros::Task::delay(scanDelay);
                            PrivateVoltage(-127);
                            pros::Task::delay(throwDelay);
                            PrivateVoltage(127);                    
                        }
                    
                        else if (Master.get_digital(pros::E_CONTROLLER_DIGITAL_R1)) {

                            PrivateVoltage(127);
                        
                        }else if(Master.get_digital(pros::E_CONTROLLER_DIGITAL_L1)){

                            PrivateVoltage(-127);

                        }else{

                            PrivateVoltage(0);

                        }

                    break;

                    case Blue:

                        if (c1.get_hue() > 190 && c1.get_hue() < 240 && Master.get_digital(pros::E_CONTROLLER_DIGITAL_R1) && d1.get_distance() < 90) {
                            
                            pros::Task::delay(scanDelay);
                            PrivateVoltage(-127);
                            pros::Task::delay(throwDelay);
                            PrivateVoltage(127);                    
                        }

                        else if (Master.get_digital(pros::E_CONTROLLER_DIGITAL_R1)) {

                            PrivateVoltage(127);
                        
                        }else if(Master.get_digital(pros::E_CONTROLLER_DIGITAL_L1)){

                            PrivateVoltage(-127);

                        }else{

                            PrivateVoltage(0);

                        }

                        break;

                        }
                    
                    }   else{
                        
                        //Intake 
                        if (Master.get_digital(pros::E_CONTROLLER_DIGITAL_R1)) {

                            PrivateVoltage(127, 0);
                            PrivateVoltage(-127, 2);

                        //expel the ball, this would be for the buttom tubes or to get rid of opposing team's balls
                        }else if(Master.get_digital(pros::E_CONTROLLER_DIGITAL_R2)){
                            //When you created the intake motors, you should've put them all in a list. To control a specific motor, 
                            //add a comma and the index like below. The first value will send 127 volts to the motor at index 0.
                            //PrivateVoltage(-127, 0);
                            //PrivateVoltage(-127); will send 127 volts to all motors in the Intake List

                            PrivateVoltage(-127, 0);
                            PrivateVoltage(127, 2);
                            

                        }
                        

                        //expel the ball from the very top
                        else if (Master.get_digital(pros::E_CONTROLLER_DIGITAL_L1)) {
                            PrivateVoltage(127, 0);
                            PrivateVoltage(127, 2);
                            PrivateVoltage(127, 1);

                        }

                        //expel the ball from the top middle

                        else if(Master.get_digital(pros::E_CONTROLLER_DIGITAL_L2)) {
                            PrivateVoltage(127, 0);
                            PrivateVoltage(127, 2);
                            PrivateVoltage(-127, 1);
                        }

                        //if no buttons are pressed, motors stop running. 


                        else{

                            PrivateVoltage(0);

                        }

                    }
                    

                    

                    break;

                
        case Moving:




        break;

    }

    pros::Task::delay(1);
    
    }

}
