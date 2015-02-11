/*
 * main.cpp
 *
 *  Created on: Feb 9, 2015
 *      Author: pete
 */

#include <stdio.h>
#include "SunPosition.h"

int main(int argc, char *argv[])
{
	SunPosition sun(42.0, 88.0);
	sun.setCurrentDate(2014, 1, 8);

	printf("Sunrise is %f, sunset is %f\n", sun.calcSunriseUTC(), sun.calcSunsetUTC());
	return 0;
}


