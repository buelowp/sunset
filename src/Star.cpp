/*
 * Star.cpp
 *
 *  Created on: Nov 8, 2019
 *      Author: kiros
 */

#include "/home/kiros/git/sunset/src/Star.h"

#include <math.h>

Star::Star() {
	// TODO Auto-generated constructor stub

}

Star::~Star() {
	// TODO Auto-generated destructor stub
}
double Star::degToRad(double angleDeg) {
	return (M_PI * angleDeg / 180.0);
}

double Star::radToDeg(double angleRad) {
	return (180.0 * angleRad / M_PI);
}
double Star::timeToDeg(double hour) {
	return hour * 15;
}
double Star::degToTime(double angle) {
	return angle / 15.0;
}

double Star::adjustDeg(double L) {
	while (L >= 360) {
		L -= 360.0;
	}

	while (L < 0) {
		L += 360.0;
	}
	return L;
}

double Star::adjustRad(double L) {
	return degToRad(adjustDeg(radToDeg(L)));
}

double Star::adjustTime(double L) {
	return degToTime(adjustDeg(timeToDeg(L)));
}

double Star::udaysFromSid(double jd_fromEpoch, double sidTime,
		double longitude) {
	double midDay = adjustRad(SID_CONST + longitude + SID_COEF * jd_fromEpoch);
	return ((sidTime - midDay) / M_PI) * (180 / 15) / 24;
}
double Star::localSidTime(double days, double longitude) {
	return SID_CONST + SID_COEF * days + longitude;
}

double Star::starSetTimeSidereal(double ra, double decl, double lat,
		int event) {

	return (event == SET) ?
			ra + acos(-tan(decl) * tan(lat)) : ra - acos(-tan(decl) * tan(lat));;
}
int Star::starRise_SetTime(double jd, double ra_deg, double decl_deg, double lat_deg, double longitude_deg, int event) {
    double tzOffset = 3.0;
	double ra = degToRad(ra_deg);
	double decl = degToRad(decl_deg);
	double lat = degToRad(lat_deg);
	double longitude = degToRad(longitude_deg);
	if (fabs(decl + lat) > M_PI / 2)
			return -1; //Always Below Horizon
		if (fabs(decl + lat) < M_PI / 2)
			return -2; // Always Above Horizon
	double eventTime = adjustRad(starSetTimeSidereal(ra, decl, lat, event)); //:adjustRad(starRiseTimeSidereal(ra,decl,lat));
	double daysFromJ2000 = jd - JD_EPOCH_2000;
	return adjustTime(12 + (60 * tzOffset)	+ 24 * udaysFromSid(daysFromJ2000, eventTime, longitude));
}

