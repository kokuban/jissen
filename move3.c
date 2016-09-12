//main未完成

//標準ライブラリ　インクルードファイル
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>

//----------------------------------------------------------
//NCTRBロボット制御ライブラリ　インクルードファイル
#include "nctrb_mechctrl_io.h"

//-------------------------------------------------------------------
//オムニホイール駆動向け　定数宣言など
//-------------------------------------------------------------------
#define whlSTOP         0x00        //停止(ブレーキなし)
#define whlSTOPB        0xFF        //停止(ブレーキあり)
#define whlFORWARD      0x66        //前進(10011001b) 		(01100110b)
#define whlBACK         0x99        //後退(01100110b) 		()
#define whlRIGHT        0x5A        //右へ進む(10100101b)	()
#define whlLEFT         0xA5        //左へ進む(01011010b)	()
#define whlCW           0xAA        //その場で右旋回
#define whlCCW          0x55        //その場で左旋回
#define whlFRCW         0xA0        //前側モーターのみ右旋回
#define whlFRCCW        0x50        //前側モーターのみ左旋回
#define whlRRCW         0x0A        //後側モーターのみ右旋回
#define whlRRCCW        0x05        //後側モーターのみ左旋回
#define whlFR           0x81        //前右方向へ前進(10000001b)
#define whlFL           0x18        //前左方向へ前進(00011000b)





int main()
{
    //ライブラリの初期化
    //最初に一回だけ下記関数をコールすること
    nctrb_mc_io_initialize();
	
	
	
	nctrb_mc_io_driveWheel(whlFORWARD);
	usleep(300000);
	nctrb_mc_io_driveWheel(whlSTOPB);
	//base初期化
	base = init_base(1);
	n_base = init_base(2);
	
	nctrb_mc_io_driveWheel( base.tire );
	gettimeofday(&s_time, NULL);
	while(1){
		int end = move();
		if(end)
		{
			nctrb_mc_io_driveWheel(whlSTOPB);
			break;
		}
		//sleep(1);
	}
	
	basePoint flag_base = n_base;
	reverse(-1);
	
	while(base == flag_base)
	{
		move();
	}
	nctrb_mc_io_driveWheel( whlSTOPB );
	
	switch(base.baseNumber)
	{
	case 0://左下
		nctrb_mc_io_driveWheel( 0xA5 );
		break;
	case 1://左上
		nctrb_mc_io_driveWheel( 0x66 );
		break;
	case 2://右上
		nctrb_mc_io_driveWheel( 0x5A );
		break;
	case 3://右下
		nctrb_mc_io_driveWheel( 0x99 );
		break;
	}
	
	//ゴールゾーンに全部入るまで直進
	while((nctrb_mc_io_readLineSensor()&0xFF) != 0xFF)
	{
		usleep(10000);
	}
	
}


int forward()
{
	const int FRONT_SENSOR_VALUE = 192 //11000000
	const int RIGHT_SENSOR_VALUE = 48  //00110000
	const int LEFT_SENSOR_VALUE = 12   //00001100
	const int BACK_SENSOR_VALUE = 3    //00000011
	//maesensa-made
	while(1)
	{
		BYTE lsensorValue	= nctrb_mc_io_readLineSensor();
		if(FRONT_SENSOR_VALUE&lsensorValue)
		{
			in_step();
			break;
		}
		if(RIGHT_SENSOR_VALUE&lsensorValue)
		{
			nctrb_mc_io_driveWheel( whlLEFT );
			usleep(500000);
			nctrb_mc_io_driveWheel(whlSTOPB);
		}
		if(LEFT_SENSOR_VALUE&lsensorValue)
		{
			nctrb_mc_io_driveWheel( whlRIGHT );
			usleep(500000);
			nctrb_mc_io_driveWheel(whlSTOPB);
		}
		nctrb_mc_io_driveWheel(whlFORWARD);
		usleep(50000);
	}
	//koe
	while(BACK_SENSOR_VALUE!=lsensorValue)
	{
		nctrb_mc_io_driveWheel( whlFORWARD );
		usleep(50000);
	}
	
	nctrb_mc_io_driveWheel( whlFORWARD );
	usleep(100000);
}

void in_step()
{
	const int FR_SENSOR_VALUE = 64
	const int FL_SENSOR_VALUE = 128
	const int FRONT_SENSOR_VALUE = 192 //11000000
	while(1)
	{
		BYTE lsensorValue	= nctrb_mc_io_readLineSensor();
		if(FRONT_SENSOR_VALUE==lsensorValue)
		{
			break;
		}else if(FR_SENSOR_VALUE==lsensorValue)
		{
			nctrb_mc_io_driveWheel(186);//10111010
		}else if(FL_SENSOR_VALUE==lsensorValue)
		{
			nctrb_mc_io_driveWheel(213);//11010101
		}else{
			nctrb_mc_io_driveWheel(whlFORWARD);
		}
		usleep(50000);
	}
}


