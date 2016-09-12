from jissen_config *
from nctrb_mechctrl_io import *
from time import sleep

def move_forward():
	
	in_step()
		
	while(BACK_SENSOR_VALUE!=lsensorValue)
	{
		nctrb_mc_io_driveWheel( whlFORWARD );
		sleep(0.05);
	}
	
	nctrb_mc_io_driveWheel( whlFORWARD );
	sleep(0.1);
	
	nctrb_mc_io_driveWheel(whlSTOPB)
	sleep(0.5)
	
	return(True)
	
	
def in_step():

	while 1:
		lsensorValue  = nctrb_mc_io_readLineSensor()
		
		if FRONT_SENSOR_VALUE&lsensorValue:
			submodule_in_step()
			break
		
		if RIGHT_SENSOR_VALUE&lsensorValue:
			nctrb_mc_io_driveWheel( whlLEFT )
			sleep(0.5)
			nctrb_mc_io_driveWheel(whlSTOPB)
			sleep(0.1)
			
		elif LEFT_SENSOR_VALUE&lsensorValue:
			nctrb_mc_io_driveWheel( whlRIGHT )
			sleep(0.5)
			nctrb_mc_io_driveWheel(whlSTOPB)
			sleep(0.1)
		else:	
			nctrb_mc_io_driveWheel(whlFORWARD)
			sleep(0.05)
	
def submodule_in_step():

	FR_SENSOR_VALUE = 64
	FL_SENSOR_VALUE = 128
	FRONT_SENSOR_VALUE = 192 #11000000
	while 1:
	
		BYTE lsensorValue	= nctrb_mc_io_readLineSensor()
		
		if FRONT_SENSOR_VALUE==lsensorValue:
			nctrb_mc_io_driveWheel(whlSTOPB)
			sleep(0.1)
			break
		elif FR_SENSOR_VALUE==lsensorValue:
			nctrb_mc_io_driveWheel(186)//10111010
		elif FL_SENSOR_VALUE==lsensorValue:
			nctrb_mc_io_driveWheel(213)//11010101
		else:
			nctrb_mc_io_driveWheel(whlFORWARD)
		
		sleep(0.05)
		
def turn_right():
	nctrb_mc_io_driveWheel( whlCW )
	sleep(0.5)
	
	in_step()
	
	nctrb_mc_io_driveWheel( whlBACK );
	sleep(0.1);
	
	nctrb_mc_io_driveWheel(whlSTOPB)
	sleep(0.5)
	
def turn_left():
	nctrb_mc_io_driveWheel( whlCCW )
	sleep(0.5)
	
	in_step()
	
	nctrb_mc_io_driveWheel( whlBACK );
	sleep(0.1);
	
	nctrb_mc_io_driveWheel(whlSTOPB)
	sleep(0.5)
	

	
	
	
 
	
