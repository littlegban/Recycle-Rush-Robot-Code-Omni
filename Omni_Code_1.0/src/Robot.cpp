#include "WPILib.h"

class Robot: public IterativeRobot
{
private:
	//%%% Vocabulary and definitions - if you don't know a word it will most likley be here
	//NCIU = Not Currently In Use (will be taken out in optimized code, however for ease of reading and understanding structure they are in)
	//Pointers: The little asterisk *, don't concern yoursself about this to much unless you are a coder in which case just Google it
	//Autonomous: The start of the game, where the robot runs pre-determined commands and there is no user control
	//Teleoperation: The time of the game where drivers step forward and take control of the robot
	//Deadzone: A space where there may be input, but nothing will be activated to make sure it wasn't by accident
	CANTalon *TalonSRX1;
	CANTalon *TalonSRX2;
	CANTalon *TalonSRX3;
	CANTalon *TalonSRX4;

	RobotDrive *DriveSystem; //NCIU
	float wrotation = 0.0;
	float wspeed = 0.0;
	float wdirection = 0.0;

	Joystick *LeftStick; //Left Stick
	float LeftStickInput = 0.0;
	bool LeftStickTrigger = false; // LeftStick Trigger (1)
	
	Joystick *RightStick; //Right Stick
	float RightStickInput = 0.0;
	bool RightTrigger1 = false; // NCIU
	
	Joystick *XBoxPlayer1; //Controller of basically anything that isn't drive
	//XBox Controller Buttons
	//A = 1    B = 2  X = 3   Y = 4  LB = 5  RB = 6  Back = 7  Start = 8  LeftTrigger Click = 9  RightTrigger Click = 10
	//XBox Controller Axis
	//Leftstick X = 0  Leftstick Y = 1  Left Trigger = 2  Right Trigger = 3  Right X = 4  Right Y = 5
	float LeftXBoxXInput = 0.0; //NCIU
	float LeftXboxYInput = 0.0; //NCIU
	float XBoxLeftTrigger = 0.0; //NCIU
	float XBoxRightTrigger = 0.0; //NCIU
	float RightXBoxXInput = 0.0; //NCIU
	float RightXboxYInput = 0.0; //NCIU

	Talon *LiftMotor; 
	bool MotorForward = false;
	bool MotorReverse = false;
		
		
	DigitalInput *LimitSwitchTop;
	bool LimitSwitchTopCheck = false; //NCIU
	DigitalInput *LimitSwitchBot;
	bool LimitSwitchBotCheck = false; //NCIU

	DoubleSolenoid *ArmSolenoid;
	bool SolenoidForward = false;
	bool SolenoidReverse = false;
	bool SolenoidOff = false; // NCIU

	void RobotInit()
	{
		//When the robot becomes activated it will initialize, acepting the pointers%%% from above and finding out what they are
		TalonSRX1 = new CANTalon(1);
		TalonSRX2 = new CANTalon(2);
		TalonSRX3 = new CANTalon(3);
		TalonSRX4 = new CANTalon(4);

		DriveSystem = new RobotDrive(TalonSRX1, TalonSRX2, TalonSRX3, TalonSRX4); //Keeping this in just in case we suddenly need it
		
		//adding the sticks to the robot
		LeftStick = new Joystick(0);
		RightStick = new Joystick(1);
		XBoxPlayer1 = new Joystick(2);

		LiftMotor = new Talon(0);

		LimitSwitchTop = new DigitalInput(0);
		LimitSwitchBot = new DigitalInput(1);

		ArmSolenoid = new DoubleSolenoid(5, 3, 4);
	} //End RobotInit
//////////////////////////////////////////////////////FUNCTIONS FOR AUTONOMOUS///////////////////////////////////////////////////////////////
															////Drive////
	void Drive(int wxdirection, float wxtime, float wxspeed) //Drive takes direction and time, direction choses forwards or reverse time decides the time
	{	
		float speed = wxspeed;
		
		//If the user enters a speed pass the max speed we will set their speed to the maxspeed
		if (speed > 1) {
			speed = 1;	
		}
		if (speed <= 0)      //If the value they entered is less than or equal to zero set the speed to the default. 
		{                           //This should also work if there is no value for speed 
			speed = 0.5                  
		}
		
		if (wxdirection < 0)										 //If the direction is less than 0 (when called set to -1 for reverse)
		{
			TalonSRX1->Set(speed * -1); TalonSRX2->Set(speed * -1); TalonSRX3->Set(speed); TalonSRX4->Set(speed); //Set the talons to go in reverse (wiring)
			Wait(wxtime);																	 //Wait for however long time is
			TalonSRX1->Set(0); TalonSRX2->Set(0); TalonSRX3->Set(0); TalonSRX4->Set(0);		 //Than turn them off
		}
		if (wxdirection > 0) 										//If the direction is greater than 0 (when called set to 1 for forward)
		{
			TalonSRX1->Set(speed); TalonSRX2->Set(speed); TalonSRX3->Set(speed * -1); TalonSRX4->Set(speed * -1);     //Set the talons to go forward (wiring)
			Wait(wxtime);																		//Wait for time
			TalonSRX1->Set(0); TalonSRX2->Set(0); TalonSRX3->Set(0); TalonSRX4->Set(0); 		//Than turn them off
		}
	}
	
		void Strafe(int wxdirection, float wxtime, float wxspeed) //Strafe takes direction and time, direction choses left-strafe or right-strafe time decides the time
	{	
		float speed = wxspeed;               
		if (speed > 1) {
			speed = 1;	
		}
		
		if (speed <= 0) 
		{
			speed = 0.5
		}
		
		
		if (wxdirection < 0)										 //If the direction is less than 0 (when called set to -1 for reverse)
		{                                            //I don't actually know if I'm currently controlling the right motors
			TalonSRX1->Set(speed); TalonSRX2->Set(speed * -1); TalonSRX3->Set(speed * -1); TalonSRX4->Set(speed); //Set the talons to go in reverse (wiring)
			Wait(wxtime);																	 //Wait for however long time is
			TalonSRX1->Set(0); TalonSRX2->Set(0); TalonSRX3->Set(0); TalonSRX4->Set(0);		 //Than turn them off
		}
		if (wxdirection > 0) 										//If the direction is greater than 0 (when called set to 1 for forward)
		{
			TalonSRX1->Set(speed * -1); TalonSRX2->Set(speed); TalonSRX3->Set(speed); TalonSRX4->Set(speed * -1);     //Set the talons to go forward (wiring)
			Wait(wxtime);																//Wait for time
			TalonSRX1->Set(0); TalonSRX2->Set(0); TalonSRX3->Set(0); TalonSRX4->Set(0); 		//Than turn them off
		}
	}
															////Turn////
	void Turn (int wxdirection, float wxtime, float wxspeed) //Takes direction for left or right and time for the time to execute
	{
		float speed = wxspeed;
		if (speed > 1) {
			speed = 1;	
		}
		if (speed <= 0) {
			speed = 0.5
		}
		
		if (wxdirection < 0) 																//If direction if less than 0
		{
			TalonSRX1->Set(speed); TalonSRX2->Set(speed); TalonSRX3->Set(speed); TalonSRX4->Set(speed); //Turn the talons
			Wait(wxtime);																	//Wait for time
			TalonSRX1->Set(0); TalonSRX2->Set(0); TalonSRX3->Set(0); TalonSRX4->Set(0);		//Turn the talons off
		}
		if (wxdirection > 0)																//If direction is greater than 1
		{
			TalonSRX1->Set(speed * -1); TalonSRX2->Set(speed * -1); TalonSRX3->Set(speed * -1); TalonSRX4->Set(speed * -1); //Turn the talons
			Wait(wxtime);																		//Wait for time
			TalonSRX1->Set(0); TalonSRX2->Set(0); TalonSRX3->Set(0); TalonSRX4->Set(0);			//Turn the talons off
		}
	}
														////Solenoid Commands////
	void ArmSolenoidCommand (int wxopenorclose, float wxtime) //Takes open or close and time
	{
		if (wxopenorclose < 0)									//If direction is less than 0 (close)
		{														//
			ArmSolenoid->Set(DoubleSolenoid::Value::kReverse);	//Set the solenoid to reverse
			Wait(wxtime);										//Wait for time
			ArmSolenoid->Set(DoubleSolenoid::Value::kOff);		//Turn the solenoid off
		}
		if (wxopenorclose > 0)									//If direction is greater than 0
		{														//
			ArmSolenoid->Set(DoubleSolenoid::Value::kForward);	//Set the solenoid to forward
			Wait(wxtime);										//Wait for time
			ArmSolenoid->Set(DoubleSolenoid::Value::kOff);		//Turn the solenoid off
		}
	}
	
		void Lift(int wxdirection, float wxtime, float wxspeed) //Left takes direction and time, direction choses up or down time decides the time
	{	
		float speed = wxspeed;               
		if (speed > 1) {
			speed = 1;	
		}
		
		if (speed <= 0) 
		{
			speed = 0.5
		}
		
		
		if (wxdirection < 0)										 //If the direction is less than 0 (when called set to -1 for reverse)
		{                                       //I don't actually know if I'm currently controlling the right motors
			LiftMotor->Set(speed); 
			Wait(wxtime);																	 //Wait for however long time is
			LiftMotor->Set(0); 
		}
		if (wxdirection > 0) 										//If the direction is greater than 0 (when called set to 1 for forward)
		{
			LiftMotor->Set(speed * -1);    
			Wait(wxtime);																//Wait for time
			LiftMotor->Set(0); TalonSRX2->Set(0); TalonSRX3->Set(0); TalonSRX4->Set(0); 		//Than turn them off
		}
	}
	
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	void AutonomousInit() //Called at the start of Autonomous%%%. If you want to initialize any variables for Autonomous put them here
	{

	} //End AutonomousInit

	void AutonomousPeriodic() //Called periodicly during Autonomous
	{
	/*List of Autonomous Commands:
	Drive(int wxdirection, float wxtime, float wxspeed) 
	Strafe(int wxdirection, float wxtime, float wxspeed)
	Turn(int wxdirection, float wxtime, float wxspeed)
	ArmSolenoidCommand (int wxopenorclose, float wxtime)
	*/	
		Drive(1, 3);
		Turn(1, .5);
		Drive(1, 3);
		Turn(1, .5);
		ArmSolenoidCommand(1, .75);
		Drive(1, 2);
		ArmSolenoidCommand(-1, .50);
		Drive(-1, 2);
		Turn(-1, .5);
		Drive(-1, 3);
		Turn(-1, .5);
		Drive(-1, 3);
		Turn(-1, 1);
		Drive(1, 2);
		ArmSolenoidCommand(1, .75);
	} //End AutonomousPeriodic

	void TeleopInit() //Called at the start of Teloperation%%%. If you want to initialize any variables for Teleoperation put them here
	{

	} //End TeleopInit

	void TeleopPeriodic()
	{
		//Called periodicly during Teleoperation
		DriveSystem->SetSafetyEnabled(false);

		wspeed = LeftStick->GetY();
		wrotation = LeftStick->GetX();
		wdirection = RightStick->GetX();

		if (LeftStick->GetRawButton(1) == true)
		{
				wspeed = wspeed / 2;
				wrotation = wrotation / 2;
				wdirection = wdirection / 2;
		}

		DriveSystem->MecanumDrive_Cartesian(wspeed, wdirection, wrotation);

/////////////////////////////////////////////////////AREA FOR TEMPORARY CODE/////////////////////////////////////////////////////////////////
		if(XBoxPlayer1->GetRawButton(5) == true) LiftMotor->Set(-.5); //Up
		if(XBoxPlayer1->GetRawButton(6) == true) LiftMotor->Set(.4); //Down
		if(XBoxPlayer1->GetRawButton(5) != true and XBoxPlayer1->GetRawButton(6) != true) LiftMotor->Set(0.0);

		if (XBoxPlayer1->GetRawButton(1) == true) ArmSolenoid->Set(DoubleSolenoid::Value::kForward);
		if (XBoxPlayer1->GetRawButton(2) == true) ArmSolenoid->Set(DoubleSolenoid::Value::kReverse);
		if (XBoxPlayer1->GetRawButton(1) != true and XBoxPlayer1->GetRawButton(2) != true) ArmSolenoid->Set(DoubleSolenoid::Value::kOff);
//////////////////////////////////////////////////LIFT MOTOR AND LIMIT SWITCH////////////////////////////////////////////////////////////////
															////Up////
		if (XBoxPlayer1->GetRawButton(6) == true) //If RightBumper is pressed
		{
			if (MotorForward == false) //If bool is false
			{
				MotorForward = true; //Set it to true
				if (LimitSwitchTop->Get() != true) //If LimitSwitchTop is not sending a true signal
				{
					LiftMotor->Set(-.5); //Set LiftMotor to 50% reverse (reverse moves our system up)
				}
			}
			else //If MotorForward is not false (true)
			{
				if (LimitSwitchTop->Get() == true) //If the limit switch is activated
				{
					LiftMotor->Set(0.0); //Set the LiftMotor to 0% speed
				}
			}
		}
		else MotorForward = false; //If RightBumper is not pressed set MotorForward to false
														////Down////
		if (XBoxPlayer1->GetRawButton(5) == true) //If LeftBumper is pressed
		{
			if (MotorReverse == false) //If bool is false
			{
				MotorReverse = true; //Set it to true
				if (LimitSwitchBot->Get() != true) //If LimitSwitchBot is not sending a true signal
				{
					LiftMotor->Set(.5); //Set LiftMotor to 50% forward (this will move the arm down)
				}
			}
			else //If the bool is true
			{
				if (LimitSwitchBot->Get() == true) //If LimitSwitchBot is sending a true signal
				{
					LiftMotor->Set(0.0); //Set the motors to 0% speed
				}
			}
		}
		else //If the LeftBumper is not pressed
		{
			MotorReverse = false; //Set the bool to false
		}

		if (XBoxPlayer1->GetRawButton(6) != true and XBoxPlayer1->GetRawButton(5) != true) //If RightBumper and LeftBumper are not pressed
		{
			LiftMotor->Set(0.0); //Set it to 0.0 (off)
		}
///////////////////////////////////////////////////////////////SOLENOID//////////////////////////////////////////////////////////////////////
															////FORWARD////
		if (XBoxPlayer1->GetRawButton(1) == true) //if XBoxPlayer1 A gets activated
		{
			if (SolenoidForward == false) //If SolenoidForward is false
			{
				SolenoidForward = true; //Set it to true
				ArmSolenoid->Set(DoubleSolenoid::Value::kForward); //And set ArmSolenoid to forward
			}
		}
		else SolenoidForward = false; //If XBoxPlayer1 A is not activated set SolenoidForward to false
															////REVERSE////
		if (XBoxPlayer1->GetRawButton(2) == true) //If XBoxPlayer1 B  is activated
		{
			if (SolenoidReverse == false) //If SolenoidReverse is false
			{
				SolenoidReverse = true; //Set it to true
				ArmSolenoid->Set(DoubleSolenoid::Value::kReverse); //And set ArmSolenoid to reverse
			}
		}
		else SolenoidReverse = false; //If XBoxPlayer1 B is not activated set SolenoidReverse to false
															////Off////
		if (XBoxPlayer1->GetRawButton(1) != true and XBoxPlayer1->GetRawButton(2) != true) //If neither button is pressed
		{
			ArmSolenoid->Set(DoubleSolenoid::Value::kOff); //Set ArmSolenoid to off
		}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	}//End TeleopPeriodic

}; //End Robot Class

START_ROBOT_CLASS(Robot); //Starts the class Robot (see the top of the page, that is what we are starting and thefore it starts everything
