#include "Autons.hpp"
#include "Intake.hpp"
#include "Systems.hpp"
#include "pros/device.hpp"
#include "pros/rtos.hpp"

void RedLeftNoStake(){

Intake.ColorSortOn(true);

Intake.SetColor(robos::Blue);

brown.sensor.set_position(0);

Drive.SetHeading(180);




Drive.Arc(-24.5, -17, 3000,{55,false});

Mogo.toggle();

pros::delay(100);



Drive.TurnTo(42, 1300);



Intake.OFF();

Drive.Move(21, 2000);

LeftClaw.toggle();

pros::delay(200);

Drive.Move(-40, 2000);

Intake.ON();

LeftClaw.toggle();
    


Drive.Arc(48, -210, 2000);


Drive.TurnTo(-150, 1000);

Drive.Move(48, 2000);

Drive.Move(10, 750);

Drive.Move(-10, 500);

Drive.Move(10, 750);

Drive.Move(-10, 500);

Drive.Move(10, 750);

Drive.Move(-30, 1500);




}

void AwpGoalRed(){

    Intake.ColorSortOn(true);

    Intake.SetColor(robos::Blue);

    brown.sensor.set_position(0);

    Drive.SetHeading(-90);

    Drive.TurnTo(-135, 1000);

    brown.MoveTo(180);

    Drive.Move(4, 1000);


    Drive.Move(-12, 2000);

    brown.MoveTo(-15);

    Drive.TurnTo(-170, 700);

    Drive.Move(-24, 1200,{70});

    Mogo.toggle();

    pros::delay(100);

    Intake.ON();

    Drive.TurnTo(90, 1000);

    Drive.Move(24, 1000);

    Drive.TurnTo(150, 800);

    Drive.Move(40, 1500);

    Drive.Move(10, 750);
    
    Drive.Move(-10, 750);

    Drive.Move(10, 750);
    
    Drive.Move(-10, 750);

    Drive.Move(10, 750);
    
    Drive.Move(-40,2000);

    Drive.TurnTo(-60, 1000);

    brown.MoveTo(200);

    Drive.Move(12, 1000);

}

void AwpGoalBlue(){

    Intake.ColorSortOn(true);

    Intake.SetColor(robos::Red);

    brown.sensor.set_position(0);

    Drive.SetHeading(90);

    Drive.TurnTo(135, 1000);

    brown.MoveTo(180);

    Drive.Move(4, 1000);


    Drive.Move(-12, 2000);

    brown.MoveTo(-15);

    Drive.TurnTo(170, 700);

    Drive.Move(-24, 1200,{70});

    Mogo.toggle();

    pros::delay(100);

    Intake.ON();

    Drive.TurnTo(-90, 1000);

    Drive.Move(24, 1000);

    Drive.TurnTo(-150, 800);

    Drive.Move(40, 1500);

    Drive.Move(10, 750);
    
    Drive.Move(-10, 750);

    Drive.Move(10, 750);
    
    Drive.Move(-10, 750);

    Drive.Move(10, 750);
    
    Drive.Move(-40,2000);

    Drive.TurnTo(60, 1000);

    brown.MoveTo(200);

    Drive.Move(12, 1000);

}

void AwpRingRed(){

Intake.ColorSortOn(true);

Intake.SetColor(robos::Blue);

brown.sensor.set_position(0);

Drive.SetHeading(90);

Drive.TurnTo(135, 1000);

brown.MoveTo(180);

Drive.Move(4, 1000);


Drive.Move(-12, 2000);

brown.MoveTo(-15);

Drive.TurnTo(170, 700);

Drive.Move(-24, 1200,{70});

Mogo.toggle();

pros::delay(100);

Intake.ON();

Drive.TurnTo(-90, 1000);

Drive.Move(24, 1000);

Drive.Move(-24, 1000);

Drive.TurnTo(-45, 1200);

Drive.Arc(22, -45, 2000);

Drive.TurnTo(-90, 800,127,false);

Drive.Move(16, 1200);

Drive.Arc(-24, -90, 2000,{60,false});

Drive.TurnTo(45, 800);



brown.MoveTo(180);

Drive.Move(4, 1000);

}

void AwpRingBlue(){

    Intake.ColorSortOn(true);

Intake.SetColor(robos::Red);

brown.sensor.set_position(0);

Drive.SetHeading(-90);

Drive.TurnTo(-135, 1000);

brown.MoveTo(180);

Drive.Move(4, 1000);


Drive.Move(-12, 2000);

brown.MoveTo(-15);

Drive.TurnTo(-170, 700);

Drive.Move(-24, 1200,{70});

Mogo.toggle();

pros::delay(100);

Intake.ON();

Drive.TurnTo(90, 1000);

Drive.Move(24, 1000);

Drive.Move(-24, 1000);

Drive.TurnTo(45, 1200);

Drive.Arc(22, 45, 2000);

Drive.TurnTo(90, 800,127,false);

Drive.Move(16, 1200);

Drive.Arc(-24, 90, 2000,{60,false});

Drive.TurnTo(-45, 800);



brown.MoveTo(180);

brown.MaxSpeed(40);

Drive.Move(8, 1000);

brown.MaxSpeed(127);


}

void AwpGoalRedNoStake(){

    

    Intake.ColorSortOn(true);

    Intake.SetColor(robos::Blue);

    Drive.SetHeading(180);

    Drive.Arc(-24.5, 17, 3000,{55,false});

    Mogo.toggle();

    Drive.TurnTo(80, 800);

    Intake.ON();

    Drive.Move(20, 1200);

    Drive.Move(-20, 1200);

    Drive.TurnTo(-45, 2000);

    Drive.Move(10, 1000);

    brown.MoveTo(200);


    
}

void AwpGoalBlueNoStake(){

    brown.sensor.set_position(0);

    Intake.ColorSortOn(true);

    Intake.SetColor(robos::Red);

    Drive.SetHeading(180);

    Drive.Arc(-24.5, -17, 3000,{55,false});

    Mogo.toggle();

    Drive.TurnTo(-80, 800);

    Intake.ON();

    Drive.Move(20, 1200);

    Drive.Move(-20, 1200);

    Drive.TurnTo(-45, 1200);

    Drive.Move(10, 2000);

    brown.MoveTo(200);

}

void AwpRingRedNoStake(){

Intake.ColorSortOn(true);

Intake.SetColor(robos::Blue);

brown.sensor.set_position(0);

Drive.SetHeading(180);




Drive.Arc(-24.5, -25, 3000,{45,false});

Mogo.toggle();

pros::delay(100);

Intake.ON();

Drive.TurnTo(-80, 1000);

Drive.Move(18, 1500);

Drive.Move(-18, 1000);

Drive.TurnTo(0, 1200);


Drive.Arc(24, -90, 2000,{80});

Drive.TurnTo(-90, 800,127,false);

Drive.Move(24, 1200);

Drive.Arc(-20, -40, 2000,{60,false});

Drive.TurnTo(135, 800);

Drive.Move(10, 1000);

Drive.TurnTo(45, 1000);


brown.MoveTo(180);

Drive.Move(6, 100);

}

void AwpRingBlueNoStake(){

    Intake.ColorSortOn(true);

Intake.SetColor(robos::Red);

brown.sensor.set_position(0);

Drive.SetHeading(180);




Drive.Arc(-24.5, 25, 3000,{45,false});

Mogo.toggle();

pros::delay(100);

Intake.ON();

Drive.TurnTo(80, 1000);

Drive.Move(18, 1500);

Drive.Move(-18, 1000);

Drive.TurnTo(0, 1200);


Drive.Arc(24, 90, 2000,{80});

Drive.TurnTo(90, 800,127,false);

Drive.Move(24, 1200);

Drive.Arc(-20, 40, 2000,{60,false});

Drive.TurnTo(-135, 800);

Drive.Move(10, 1000);

Drive.TurnTo(-45, 1000);


brown.MoveTo(180);

Drive.Move(6, 100);



}

void ElimRingRed();

void ElimGoalRed();

void ElimRingBlue();

void ElimGoalBlue();