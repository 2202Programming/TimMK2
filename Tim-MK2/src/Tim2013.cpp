/* Timothy robot,

 * Soaring disks throw to the goals.
 * Also, climbs. Maybe.
 */
#include "WPILib.h"
#include "Math.h"
#include "XboxController.h"
#include "DriveControl.h"
#include "ShooterControl.h"
#include "PneumaticsControl.h"

#define AUTODRIVETIME .5
//#include "LiftControl.h"

class Tim2013: public IterativeRobot {

	DriverStation *driverStation;
	DriveControl driveControl;
	ShooterControl *shooterControl;
	PneumaticsControl pneumaticsControl;
	Relay *ledRelay;

public:
	Tim2013(void) {
		shooterControl = ShooterControl::getInstance();
		ledRelay = new Relay(8, Relay::kForwardOnly);
		ledRelay->Set(Relay::kOn);
	}



	void OperatorControl(void) {
		shooterControl->initialize();
		driveControl.initialize();
		pneumaticsControl.initialize();
		while (IsOperatorControl() && IsEnabled()) {
			driveControl.runArcadeNoAcceleration();
			shooterControl->run();
			pneumaticsControl.run();
			//	liftControl->run();
			Wait(0.005); // wait for a motor update time
		}
	}

};
START_ROBOT_CLASS(Tim2013);


