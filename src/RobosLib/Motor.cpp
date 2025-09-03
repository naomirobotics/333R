

#include "main.h"
#include "pros/misc.h"
#include <cstdio>


using namespace robos;

    Motor::Motor(int PORT, pros::v5::MotorGearset Cart, double Ratio)

    :MotorTask([this]{this->MotorLoop();}),

    Master(pros::E_CONTROLLER_MASTER),

    m1(PORT,Cart,pros::v5::MotorEncoderUnits::degrees),

    sensor(0),

    MOTORPID(2,0,20,0)

    {

        GearRatio = Ratio;

        SetConstants(3, 0.001, 40, 2);

        

    }

    Motor::Motor(int PORT, int Sensor ,pros::v5::MotorGearset Cart, double Ratio)

    :MotorTask([this]{this->MotorLoop();}),

    Master(pros::E_CONTROLLER_MASTER),

    m1(PORT,Cart,pros::v5::MotorEncoderUnits::degrees),

    sensor(Sensor),

    MOTORPID(2,0,5,0)

    {

        GearRatio = Ratio;

        // SetConstants(10, 5, 1, 2);

        FailSafe = false;

        

    }

    double Motor::GetRatio(){return GearRatio;}

    int Motor::GetState(){return States;}

    double Motor::GetEncoders(){
        if (sensor.get_port() > 0) {
            
            return sensor.get_position()/100.0/GearRatio;

        }
        
        return m1.get_position() / GearRatio;
    
    }

    void Motor::MaxSpeed(int MaxSpeed){MaxSpeed = MaxSpeed;}

    void Motor::Private_Voltage(int Voltage){m1.move_voltage(Voltage*12000/127);}

    void Motor::Move(int Voltage){

        States = 2; 

        CurrentOutput = Voltage;
        
        if (FailSafe) {

            

            return;
        
        }

    
        Private_Voltage(Voltage); 
        
        }

    void Motor::MoveTo(double Degree){MotorTarget = Degree; States = 3;}

    void Motor::Hold(){States = 1; MotorTarget = GetEncoders();}

    void Motor::Stop(){Private_Voltage(0);States = 0;}

    void Motor::Tare(){m1.tare_position();}

    void Motor::SetConstants(double iKp, double iKi, double iKd, double iExitError){return;}

    void Motor::MotorLoop(){

        

        while (true) {

                    if (States == 1) {
                
                    

                    

                    Private_Voltage(MOTORPID.Compute(MotorTarget- GetEncoders()));

                    }

                    else if (States == 3) {
                        
                   
                    

                    Private_Voltage(MOTORPID.Compute(MotorTarget - GetEncoders()));
                 

                    }

                    else if(States == 2){

                        if (FailSafe) {

                            if(m1.get_efficiency() < 5 && !Stuck){

                                timerOn = true;

                                Stuck = true;

                                Private_Voltage(-CurrentOutput);

                            }else if(!Stuck && !timerOn){

                                Private_Voltage(CurrentOutput);

                            }

                            if (timerOn) {

                                timer++;
                            
                            }

                            if (timer > 150) {

                                Stuck = false;

                                timerOn = false;

                                timer = 0;
                            
                            }
                            
                            
                        }

                    }else{

                    

                    }
                
            pros::Task::delay(10);

        }

    }


    