# -*- coding: utf-8 -*-

#const
HEIGHT = 6
WIDTH = 9

FORWARD = 1
RIGHT = 2
BACK = 3
LEFT = 4

KEY_EDGE_WEIGHT = 'weight'
UNVISITED_EDGE_WEIGHT = 1
VISITED_EDGE_WEIGHT = 2

KEY_VISIT_FREQ = 'visit_frequency'

whlSTOP      =   0x00        #停止(ブレーキなし)
whlSTOPB     =   0xFF        #停止(ブレーキあり)
whlFORWARD   =   0x66        #前進(10011001b) 		(01100110b)
whlBACK      =   0x99        #後退(01100110b) 		()
whlRIGHT     =   0x5A        #右へ進む(10100101b)	()
whlLEFT      =   0xA5        #左へ進む(01011010b)	()
whlCW        =   0xAA        #その場で右旋回
whlCCW       =   0x55        #その場で左旋回
whlFRCW      =   0xA0        #前側モーターのみ右旋回
whlFRCCW     =   0x50        #前側モーターのみ左旋回
whlRRCW      =   0x0A        #後側モーターのみ右旋回
whlRRCCW     =   0x05        #後側モーターのみ左旋回
whlFR        =   0x81        #前右方向へ前進(10000001b)
whlFL        =   0x18        #前左方向へ前進(00011000b)


FRONT_SENSOR_VALUE = 192 #11000000
RIGHT_SENSOR_VALUE = 48  #00110000
LEFT_SENSOR_VALUE = 12   #00001100
BACK_SENSOR_VALUE = 3    #00000011

