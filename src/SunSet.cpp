/*
 * Provides the ability to calculate the local time for sunrise,
 * sunset, and moonrise at any point in time at any location in the world
 *
 * Original work used with permission maintaining license
 * Copyright (GPL) 2004 Mike Chirico mchirico@comcast.net
 * Modifications copyright
 * Copyright (GPL) 2015 Peter Buelow
 *
 * This file is part of the Sunset library
 *
 * Sunset is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * Sunset is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with source code and documentation.  If not, see <http://www.gnu.org/licenses/>.
 */
#include "SunSet.h"

SunSet::SunSet()
{
  latitude = 0.0;
  longitude = 0.0;
  julianDate = 0.0;
  tzOffset = 0;
}

SunSet::SunSet(double lat, double lon, int tz)
{
  latitude = lat;
  longitude = lon;
  julianDate = 0.0;
  tzOffset = tz;
}

SunSet::~SunSet()
{

}

void SunSet::setPosition(double lat, double lon, int tz)
{
    latitude = lat;
    longitude = lon;
    tzOffset = tz;
}

double SunSet::degToRad(double angleDeg)
{
  return (M_PI * angleDeg / 180.0);
}

double SunSet::radToDeg(double angleRad)
{
  return (180.0 * angleRad / M_PI);
}
double SunSet::hourToDeg(double hour)
{
  return hour*15;
  }
double SunSet::degToTime(double angle)
{
  return angle / 15.0;
  }

double SunSet::adjustDeg(double L){
while ( L >= 360) {
  L -= 360.0;
}

while (L <  0) {
  L += 360.0;
}
return L;
}

double SunSet::adjustRad(double L){
	return degToRad(adjustDeg(radToDeg(L)));
}

double SunSet::adjustTime(double L){
	return degToTime(adjustDeg(hourToDeg(L)));
}


double SunSet::calcMeanObliquityOfEcliptic(double t)
{
  double seconds = 21.448- t*(46.8150 + t*(0.00059 - t*(0.001813)));
  double e0 = 23.0 + (26.0 + (seconds/60.0))/60.0;

  return e0;              // in degrees
}

double SunSet::calcGeomMeanLongSun(double t)
{
  double L = 280.46646 + t * (36000.76983 + 0.0003032 * t);



  return adjustDeg(L);              // in degrees
}

double SunSet::calcObliquityCorrection(double t)
{
  double e0 = calcMeanObliquityOfEcliptic(t);
  double omega = 125.04 - 1934.136 * t;
  double e = e0 + 0.00256 * cos(degToRad(omega));

  return adjustDeg(e);               // in degrees
}

double SunSet::calcEccentricityEarthOrbit(double t)
{
  double e = 0.016708634 - t * (0.000042037 + 0.0000001267 * t);
  return e;               // unitless
}

double SunSet::calcGeomMeanAnomalySun(double t)
{
  double M = 357.52911 + t * (35999.05029 - 0.0001537 * t);
  return adjustDeg(M);               // in degrees
}

double SunSet::calcEquationOfTime(double t)
{
  double epsilon = calcObliquityCorrection(t);
  double l0 = calcGeomMeanLongSun(t);
  double e = calcEccentricityEarthOrbit(t);
  double m = calcGeomMeanAnomalySun(t);
  double y = tan(degToRad(epsilon)/2.0);

  y *= y;

  double sin2l0 = sin(2.0 * degToRad(l0));
  double sinm   = sin(degToRad(m));
  double cos2l0 = cos(2.0 * degToRad(l0));
  double sin4l0 = sin(4.0 * degToRad(l0));
  double sin2m  = sin(2.0 * degToRad(m));
  double Etime = y * sin2l0 - 2.0 * e * sinm + 4.0 * e * y * sinm * cos2l0 - 0.5 * y * y * sin4l0 - 1.25 * e * e * sin2m;
  return radToDeg(Etime)*4.0;	// in minutes of time
}

double SunSet::calcTimeJulianCent(double jd)
{
  double T = ( jd - 2451545.0)/36525.0;
  return T;
}

double SunSet::calcSunTrueLong(double t)
{
  double l0 = calcGeomMeanLongSun(t);
  double c = calcSunEqOfCenter(t);

  double O = l0 + c;
  return adjustDeg(O);               // in degrees
}

double SunSet::calcSunApparentLong(double t)
{
  double o = calcSunTrueLong(t);

  double  omega = 125.04 - 1934.136 * t;
  double  lambda = o - 0.00569 - 0.00478 * sin(degToRad(omega));
  return adjustDeg(lambda);          // in degrees
}

double SunSet::calcSunDeclination(double t)
{
  double e = calcObliquityCorrection(t);
  double lambda = calcSunApparentLong(t);

  double sint = sin(degToRad(e)) * sin(degToRad(lambda));
  double theta = radToDeg(asin(sint));
  return adjustDeg(theta);           // in degrees
}

double SunSet::calcHourAngleSunrise(double lat, double solarDec)
{
  double latRad = degToRad(lat);
  double sdRad  = degToRad(solarDec);
  double HA = (acos(cos(degToRad(90.833))/(cos(latRad)*cos(sdRad))-tan(latRad) * tan(sdRad)));

  return adjustRad(HA);              // in radians
}

double SunSet::calcHourAngleSunset(double lat, double solarDec)
{

  return adjustRad(-calcHourAngleSunrise(lat,solarDec));           // in radians
}

double SunSet::calcJD(int y, int m, int d)
{
  if (m <= 2) {
    y -= 1;
    m += 12;
  }
  int A = floor(y/100);
  int B = 2 - A + floor(A/4);

  double JD = floor(365.25*(y + 4716)) + floor(30.6001*(m+1)) + d + B - 1524.5;
  return JD;
}

double SunSet::calcJDFromJulianCent(double t)
{
  double JD = t * 36525.0 + JD_EPOCH2000;
  return JD;
}

double SunSet::calcSunEqOfCenter(double t)
{
  double m = calcGeomMeanAnomalySun(t);
  double mrad = degToRad(m);
  double sinm = sin(mrad);
  double sin2m = sin(mrad+mrad);
  double sin3m = sin(mrad+mrad+mrad);
  double C = sinm * (1.914602 - t * (0.004817 + 0.000014 * t)) + sin2m * (0.019993 - 0.000101 * t) + sin3m * 0.000289;

  return adjustDeg(C);		// in degrees
}
double SunSet::calcSunrise_setUTC(int event)
{
  double t = calcTimeJulianCent(julianDate);
  // *** First pass to approximate sunrise
  double  eqTime = calcEquationOfTime(t);
  double  solarDec = calcSunDeclination(t);
  double  hourAngle = calcHourAngleSunrise(latitude, solarDec);
  double  delta = longitude + radToDeg(hourAngle);
  double  timeDiff = 4 * delta;	// in minutes of time
  double  timeUTC = 720 - timeDiff - eqTime;	// in minutes
  double  newt = calcTimeJulianCent(calcJDFromJulianCent(t) + timeUTC/1440.0);

  eqTime = calcEquationOfTime(newt);
  solarDec = calcSunDeclination(newt);

  hourAngle = (event==RISE)? calcHourAngleSunrise(latitude, solarDec):calcHourAngleSunset(latitude, solarDec);
  delta = longitude + radToDeg(hourAngle);
  timeDiff = 4 * delta;
  timeUTC = 720 - timeDiff - eqTime; // in minutes

  return timeUTC;
}
double SunSet::calcSunriseUTC()
{
    return calcSunrise_setUTC(RISE);
}

double SunSet::calcSunrise()
{
double timeUTC = calcSunriseUTC();

  double localTime = timeUTC + (60 * tzOffset);

  return localTime;	// return time in minutes from midnight
}

double SunSet::calcSunsetUTC()
{
	return calcSunrise_setUTC(SET);  // return time in minutes from midnight
}

double SunSet::calcSunset()
{
double timeUTC=calcSunsetUTC();
  double localTime = timeUTC + (60 * tzOffset);

  return localTime;	// return time in minutes from midnight
}

double SunSet::setCurrentDate(int y, int m, int d)
{
	m_year = y;
	m_month = m;
	m_day = d;
	julianDate = calcJD(y, m, d);
	return julianDate;
}

void SunSet::setTZOffset(int tz)
{
	tzOffset = tz;
}

int SunSet::moonPhase(int fromepoch)
{
	const int moonepoch = 614100;

        int phase = (fromepoch - moonepoch) % MOON_MONTH_SECONDS;
        int res = floor(phase / SECONDS_PER_DAY) + 1;
	if (res == 30)
		res = 0;

        return res;
}

double SunSet::moonRiseTime()
{
	//To do
        return moonRise((julianDate-JD_EPOCH2000)*SECONDS_PER_DAY);
}
double SunSet::moonSetTime()
{
	//To do
        return moonSet((julianDate-JD_EPOCH2000)*SECONDS_PER_DAY);
}
double SunSet::moonRiseUTC(int fromepoch)
{
	//To do
	  return moonRise(fromepoch) -(60 * tzOffset);
}
double SunSet::moonSetUTC(int fromepoch)
{
	//To do
	  return moonSet(fromepoch) -(60 * tzOffset);
}
double SunSet::moonRise(int fromepoch)
{
	//To do 1st approximation
	return 6 + moonShift(fromepoch,RISE);
}
double SunSet::moonSet(int fromepoch)
{
	//To do 1st approximation
	  return 18 + moonShift(fromepoch,SET);

}
double SunSet::moonShift(int fromepoch, EVENT e)
{
	//To do 1st approximation - from wikipedia - orbit circular?
	  return  moonPhase(fromepoch)*(24/MOON_MONTH_DAYS);

}

int main(){

}
