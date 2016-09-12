//main������

//�W�����C�u�����@�C���N���[�h�t�@�C��
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>

//----------------------------------------------------------
//NCTRB���{�b�g���䃉�C�u�����@�C���N���[�h�t�@�C��
#include "nctrb_mechctrl_io.h"

//-------------------------------------------------------------------
//�I���j�z�C�[���쓮�����@�萔�錾�Ȃ�
//-------------------------------------------------------------------
#define whlSTOP         0x00        //��~(�u���[�L�Ȃ�)
#define whlSTOPB        0xFF        //��~(�u���[�L����)
#define whlFORWARD      0x66        //�O�i(10011001b) 		(01100110b)
#define whlBACK         0x99        //���(01100110b) 		()
#define whlRIGHT        0x5A        //�E�֐i��(10100101b)	()
#define whlLEFT         0xA5        //���֐i��(01011010b)	()
#define whlCW           0xAA        //���̏�ŉE����
#define whlCCW          0x55        //���̏�ō�����
#define whlFRCW         0xA0        //�O�����[�^�[�̂݉E����
#define whlFRCCW        0x50        //�O�����[�^�[�̂ݍ�����
#define whlRRCW         0x0A        //�㑤���[�^�[�̂݉E����
#define whlRRCCW        0x05        //�㑤���[�^�[�̂ݍ�����
#define whlFR           0x81        //�O�E�����֑O�i(10000001b)
#define whlFL           0x18        //�O�������֑O�i(00011000b)





int main()
{
    //���C�u�����̏�����
    //�ŏ��Ɉ�񂾂����L�֐����R�[�����邱��
    nctrb_mc_io_initialize();
	
	
	
	nctrb_mc_io_driveWheel(whlFORWARD);
	usleep(300000);
	nctrb_mc_io_driveWheel(whlSTOPB);
	//base������
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
	case 0://����
		nctrb_mc_io_driveWheel( 0xA5 );
		break;
	case 1://����
		nctrb_mc_io_driveWheel( 0x66 );
		break;
	case 2://�E��
		nctrb_mc_io_driveWheel( 0x5A );
		break;
	case 3://�E��
		nctrb_mc_io_driveWheel( 0x99 );
		break;
	}
	
	//�S�[���]�[���ɑS������܂Œ��i
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


