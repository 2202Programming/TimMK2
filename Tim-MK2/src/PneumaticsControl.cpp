/*
 * PneumaticsController.cpp
 *
 *  Created on: Feb 4, 2013
 *      Author: Beasty
 */
#include "ShooterControl.h"
#include "PneumaticsControl.h"

PneumaticsControl::PneumaticsControl() {

	xbox = XboxController::getInstance();
	shooterControl = ShooterControl::getInstance();

	// pressure switch is at Digital input 5,
	// compressor channel is at relay output 4,
	compressor = new Compressor(5);
	//solenoid module is 2,
	//solenoid channel is at port 1 of the module
	triggerSolenoid = new Solenoid(1, 1);
	retractSolenoid = new Solenoid(1, 2);
	firing = false;
	chambered = false;
}
void PneumaticsControl::initialize() {
	// the solenoid shuts itself off automatically at about 120 psi so we do not have to shut it off for safety reasons.
	compressor->Start();
	triggerSolenoid->Set(false);
	retractSolenoid->Set(true);

}

//void PneumaticsControl::initializeAutonomous() {
//	compressor->Start();
//	triggerSolenoid->Set(false);
//	retractSolenoid->Set(true);
//}
/*
 * when Trigger is pressed, the solenoid switches so that it moves a disk into the shooter wheels
 * otherwise it is back and allows a disk to be loaded.
 */
void PneumaticsControl::fire() {

	if (xbox->isRightTriggerHeld() && shooterControl->isRunning()) {
		if (triggerSolenoid->Get() == false) {
			triggerSolenoid->Set(true);
			retractSolenoid->Set(false);
			solenoidTimer.Start();
		}
	}
	if (solenoidTimer.Get() > .5) {
		solenoidTimer.Stop();
		solenoidTimer.Reset();
		triggerSolenoid->Set(false);
		retractSolenoid->Set(true);
	}

}
void PneumaticsControl::chambering() {
	if (xbox->isLeftTriggerHeld()) {
		if (retractSolenoid->Get()) {
			triggerSolenoid->Set(true);
			retractSolenoid->Set(true);
		}
	} else {
		triggerSolenoid->Set(false);
		retractSolenoid->Set(false);
	}
}

void PneumaticsControl::autoFire(bool fireNow) {
	if (triggerSolenoid->Get() == false && fireNow) {
		triggerSolenoid->Set(true);
		retractSolenoid->Set(false);
		autoTimer.Start();
	}

	if (autoTimer.Get() > .5) {
		autoTimer.Stop();
		autoTimer.Reset();
		triggerSolenoid->Set(false);
		retractSolenoid->Set(true);
	}
}

void PneumaticsControl::springFire() {
	if (triggerSolenoid->Get() == false) {
		triggerSolenoid->Set(true);
		solenoidTimer.Reset();
		solenoidTimer.Start();
	}

	if (solenoidTimer.Get() > 1) {
		solenoidTimer.Stop();
		triggerSolenoid->Set(false);
	}
}

/*
 void PneumaticsControl::runAutonomous(){
 autonomousTimer.Start();
 if(autonomousTimer.Get()<SHOOTERBOOTTIME)
 {
 retractSolenoid->Set(true);
 triggerSolenoid->Set(false);
 dsLCD->PrintfLine(DriverStationLCD::kUser_Line5, "retract");
 }
 else
 {
 retractSolenoid->Set(false);
 triggerSolenoid->Set(true);
 if(autonomousTimer.Get()>SHOOTERRESTPERIOD)
 {
 autonomousTimer.Reset();
 }
 dsLCD->PrintfLine(DriverStationLCD::kUser_Line5, "fire");
 }
 // dsLCD->PrintfLine(DriverStationLCD::kUser_Line6, "Time %f", autonomousTimer.Get());
 dsLCD->UpdateLCD();
 }*/

bool PneumaticsControl::CompressorFull() {
	if ((compressor->GetPressureSwitchValue()) > 0) {
		return true;
	}
	return false;
}

void PneumaticsControl::run() {
	fire();
	//chambering();
//	dsLCD->PrintfLine(DriverStationLCD::kUser_Line6, "T: %i R: %i",
//			triggerSolenoid->Get(), retractSolenoid->Get());
//	dsLCD->UpdateLCD();

}
