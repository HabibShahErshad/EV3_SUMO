/*
 \file		sumo.c
 \author	MOHAMMAD HABIB SHAH ERSHAD BIN MOHD AZRUL SHAZRIL
 \date		2/7/2022
 \brief		Sumo robot just suitable for my design
*/

#include <ev3.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

float rf = 2.75;

//declare counter
int i=1;

//declare motor rotation angle
int r;
char str[20];


void init(){

	InitEV3(); //Declare library function
	setAllSensorMode(US_DIST_MM,NO_SEN,COL_REFLECT,NO_SEN); //set what input corresponds to what sensor
}

int a(int rangle)
{
	int lower = -200, upper = 200, count = 500;
	int i;
    srand(time(0));
	int angle[500];

   // printf("The random numbers are: ");
    for (i = 0; i < count; i++) {
        int num = (rand() % (upper - lower + 1)) + lower;
        if(num < 70 && num > 0)
        {
        	num = num + 90;
		}
		else if (num > -70 && num <=0)
		{
			num = num - 90;
		}
		else
		{
			num = num;
		}

        angle[i]=num;
    }

		rangle = angle[455];
    return rangle;
}

void pushObject()
{
	while(1)
		{


		if (ReadSensor(IN_3) < 15)
		{
			RotateMotor(OUT_A,-30, 360);
			RotateMotor(OUT_BC,-50, 360);
//			RotateMotorEx(OUT_BC, -30, 360, 200 , true, true);
			Off(OUT_ABC);
			break;
		}

		else
		{
			OnFwdEx(OUT_ABC, 100,	true);
		}
		//Wait(MS_500);
	}
}

void turn(){
	int b, c;
	int count =0;
	int sonar = readSensor(IN_1);
	c = a(b);
	if (c<0)
		{
			r = -c*rf; //multiply rotation factor
			r=r/30;
			while(count<30){
				sonar = sonar/10;
			RotateMotorEx(OUT_BC, -30, r, 200 , true, true);
			if (sonar<35)
			{
				pushObject();
						//Wait(MS_100);
			}
			count++;
			sonar = readSensor(IN_1);

			}
			Wait(MS_500);
		}
		else
		{
			r = c*rf; //multiply rotation factor
			r=r/30;
						while(count<30){
							sonar = sonar/10;
						RotateMotorEx(OUT_BC, 30, r, 200 , true, true);
						if (sonar<35)
						{
							pushObject();
									//Wait(MS_100);
						}
						count++;
						sonar = readSensor(IN_1);

						}
						Wait(MS_500);
		}

}

int main(void)
{

	init();
		char SONAR[20],DISTANCE[20];
		int port = IN_1;
		int port1 = IN_3;
		int sensor = abs(ReadSensor(port));
		int sensor1 = abs(ReadSensor(port1));
		int temp;
		temp = sensor;
		while(ButtonIsUp(BTNCENTER) == 1){
			sensor = sensor/10;
			LcdClean();
			if (sensor1 > 100)
			{
				sensor1 = sensor1 - 3840;
			}
			if (sensor1 < 0)
			{
				sensor1 = 10;
			}
		sprintf(SONAR, "%d", sensor);
		sprintf(DISTANCE, "%d", sensor1);
		TermPrintln("DISTANCE    : %s",SONAR, "mm");
		TermPrintln("COLOR    : %s",DISTANCE);

		if (sensor1 <=15)
		{
			RotateMotor(OUT_BC, -30, 360);
			Wait(MS_100);
			turn();
		}
		else if (sensor1 >15)
		{
			OnFwdEx(OUT_BC, 30,	true);
		}

		Wait(MS_100);
		temp = sensor;
		sensor = abs(ReadSensor(port));
		sensor1 = abs(ReadSensor(port1));
		}


	return 0;
}
