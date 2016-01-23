#ifndef PNEUMATICSCONTROL_H
#define PNEUMATICSCONTROL_H

#include "WPILib.h"
#include "XboxController.h"

#define SHOOTERBOOTTIME 2.0
#define SHOOTERRESTPERIOD 3.0

class PneumaticsControl {

public:
	~PneumaticsControl() {
	}
	PneumaticsControl();
	void initialize();
	//void initializeAutonomous();
	void run();
//	void runAutonomous();
	bool CompressorFull();
	void fire();
	void chambering();
	void springFire();
	void autoFire(bool fireNow);
private:
	
	Timer autoTimer;
	Timer solenoidTimer;
	//Timer autonomousTimer;
	XboxController *xbox;
	Compressor *compressor;
	Solenoid *triggerSolenoid;
	Solenoid *retractSolenoid;
	bool firing;
	bool chambered;
	ShooterControl *shooterControl;
	

};
#endif 
