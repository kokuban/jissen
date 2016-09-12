import jissen_config
from nctrb_mechctrl_io import *
from time import sleep

def forward:
	FRONT_SENSOR_VALUE = 192 #11000000
	RIGHT_SENSOR_VALUE = 48  #00110000
	LEFT_SENSOR_VALUE = 12   #00001100
	BACK_SENSOR_VALUE = 3    #00000011
	
	while 1:
		lsensorValue	= nctrb_mc_io_readLineSensor()
		
		if FRONT_SENSOR_VALUE&lsensorValue:
			in_step()
			break
		if RIGHT_SENSOR_VALUE&lsensorValue:
			nctrb_mc_io_driveWheel( whlLEFT )
			sleep(0.5)
			nctrb_mc_io_driveWheel(whlSTOPB)
		if LEFT_SENSOR_VALUE&lsensorValue:
			nctrb_mc_io_driveWheel( whlRIGHT )
			sleep(0.5)
			nctrb_mc_io_driveWheel(whlSTOPB)
			
		nctrb_mc_io_driveWheel(whlFORWARD)
		sleep(0.05)
		
	while(BACK_SENSOR_VALUE!=lsensorValue)
	{
		nctrb_mc_io_driveWheel( whlFORWARD );
		sleep(0.05);
	}
	
	nctrb_mc_io_driveWheel( whlFORWARD );
	usleep(100000);