#include "SparkTime/SparkTime.h"
#include "SunRise/SunRise.h"

/* I'm in the midwest, so this is what I use for my home */
#define LATITUDE        41.12345
#define LONGITUDE       87.98765
#define CST_OFFSET      -6
#define DST_OFFSET      -5

SunPosition sun;
UDP UDPClient;
SparkTime rtc;

void setup()
{
	Serial.begin(9600);
	/* Get our time sync started */
	rtc.begin(&UDPClient, "pool.ntp.org");
	rtc.setTimeZone(CST_OFFSET);
	/* Set our position and a default timezone value */
	sun.setPosition(LATITUDE, LONGITUDE, DST_OFFSET);
}

void loop()
{
	double sunrise;
	double sunset;

	/* Check to see if we have a valid time sync yet, if not, just wait a bit and loop */
	if (!rtc.hasSynced()) {
		Particle.publish("No time sync yet");
		delay(5000);
		return;
	}
	else {
		/* Get the current time, and set the Sunrise code to use the current date */
		currentTime = rtc.now();
		sun.setCurrentDate(rtc.year(currentTime), rtc.month(currentTime), rtc.day(currentTime));
		/* Check to see if we need to update our timezone value */
		if (rtc.isUSDST(currentTime))
			sun.setTZOffset(DST_OFFSET);
		else
			sun.setTZOffset(CST_OFFSET);
	}

	sunrise = sun.calcSunrise();
	sunset = sun.calcSunset();

	Serial.print("Sunrise is ");
	Serial.print(sunrise);
	Serial.println(" minutes past midnight.");
	Serial.print("Sunset is ");
	Serial.print(sunset);
	Serial.print(" minutes past midnight.");
	delay(1000);
}

