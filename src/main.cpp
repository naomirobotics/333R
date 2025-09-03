#include "main.h"
#include "Selector.hpp"
#include "Systems.hpp"
#include "Autons.hpp"



void initialize() {

	robos::Selector::init();

	robos::Selector::SetAutons({{AwpRingRed,"Red Ring Stake"},{AwpRingRedNoStake,"Red Ring No Stake"},{AwpGoalRed,"Red Goal Stake"},{AwpGoalRedNoStake,"Red Goal No Stake"},{AwpRingBlue,"Blue Ring Stake"},{AwpRingBlueNoStake,"Blue Ring No Stake"},{AwpGoalBlue,"Blue Goal Stake"},{AwpGoalBlueNoStake,"Blue Goal No Stake"}});
	
	Drive.Calibrate();

	pros::screen::print(pros::E_TEXT_MEDIUM, 3, "HOWDY");

	brown.MaxSpeed(127);

	brown.sensor.set_position(0);

	

}

void disabled() {}


void competition_initialize() {}


void autonomous() {

	// RedLeftNoStake();

	// AwpRingRedNoStake();

	// AwpRingRed();

	// AwpRingBlue();

	// AwpGoalRedNoStake();

	// Drive.TurnTo(90, 2000);

	// Drive.TurnTo(-90, 2000);

	// Drive.Move(-12, 2000);

	// Drive.Move(36, 3000);

	robos::Selector::RunAuton();
	
	
}




void opcontrol() {
	
	Intake.ColorSortOn(false);

	// Intake.SetColor(robos::Blue);

	while (true) {

		Intake.OP();

		PneumaticOp();
		
		LadyBrownOp();

		master.print(2, 1, "%f", (r.get_temperature() + l.get_temperature())/2);

		Drive.Op(true);

		pros::delay(20);                               
	}
}