/*
    This file is part of SunPostion.

    SunPosition is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    SunPosition is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with SunPosition.  If not, see <http://www.gnu.org/licenses/>.

    This implementation is taken and modified from Mike Chirico at
    http://souptonuts.sourceforge.net/code/sunrise.c.html

    Modifications done have been in the spirit of the GPL, and
    any copying or reuse of this header and class are subject to
    the GPL v2 or any later GPL at the users discretion.
    All thanks for the original work go to Mike who made it pretty easy.
*/

#include "SunPosition.h"

SunPosition::SunPosition()
{
  latitude = 0.0;
  longitude = 0.0;
  julianDate = 0.0;
  tzOffset = 0;
}

SunPosition::SunPosition(double lat, double lon, int tz)
{
  latitude = lat;
  longitude = lon;
  julianDate = 0.0;
  tzOffset = tz;
}

SunPosition::~SunPosition()
{

}

double SunPosition::degToRad(double angleDeg)
{
  return (M_PI * angleDeg / 180.0);
}

double SunPosition::radToDeg(double angleRad)
{
  return (180.0 * angleRad / M_PI);
}

double SunPosition::calcMeanObliquityOfEcliptic(double t)
{
  double seconds = 21.448 - t*(46.8150 + t*(0.00059 - t*(0.001813)));
  double e0 = 23.0 + (26.0 + (seconds/60.0))/60.0;

  return e0;              // in degrees
}

double SunPosition::calcGeomMeanLongSun(double t)
{
  double L = 280.46646 + t * (36000.76983 + 0.0003032 * t);

  while ((int) L > 360) {
    L -= 360.0;
  }

  while (L <  0) {
    L += 360.0;
  }

  return L;              // in degrees
}

double SunPosition::calcObliquityCorrection(double t)
{
  double e0 = calcMeanObliquityOfEcliptic(t);
  double omega = 125.04 - 1934.136 * t;
  double e = e0 + 0.00256 * cos(degToRad(omega));

  return e;               // in degrees
}

double SunPosition::calcEccentricityEarthOrbit(double t)
{
  double e = 0.016708634 - t * (0.000042037 + 0.0000001267 * t);
  return e;               // unitless
}

double SunPosition::calcGeomMeanAnomalySun(double t)
{
  double M = 357.52911 + t * (35999.05029 - 0.0001537 * t);
  return M;               // in degrees
}

double SunPosition::calcEquationOfTime(double t)
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

double SunPosition::calcTimeJulianCent(double jd)
{
  double T = ( jd - 2451545.0)/36525.0;
  return T;
}

double SunPosition::calcSunTrueLong(double t)
{
  double l0 = calcGeomMeanLongSun(t);
  double c = calcSunEqOfCenter(t);

  double O = l0 + c;
  return O;               // in degrees
}

double SunPosition::calcSunApparentLong(double t)
{
  double o = calcSunTrueLong(t);

  double  omega = 125.04 - 1934.136 * t;
  double  lambda = o - 0.00569 - 0.00478 * sin(degToRad(omega));
  return lambda;          // in degrees
}

double SunPosition::calcSunDeclination(double t)
{
  double e = calcObliquityCorrection(t);
  double lambda = calcSunApparentLong(t);

  double sint = sin(degToRad(e)) * sin(degToRad(lambda));
  double theta = radToDeg(asin(sint));
  return theta;           // in degrees
}

double SunPosition::calcHourAngleSunrise(double lat, double solarDec)
{
  double latRad = degToRad(lat);
  double sdRad  = degToRad(solarDec);
  double HA = (acos(cos(degToRad(90.833))/(cos(latRad)*cos(sdRad))-tan(latRad) * tan(sdRad)));

  return HA;              // in radians
}

double SunPosition::calcHourAngleSunset(double lat, double solarDec)
{
  double latRad = degToRad(lat);
  double sdRad  = degToRad(solarDec);
  double HA = (acos(cos(degToRad(90.833))/(cos(latRad)*cos(sdRad))-tan(latRad) * tan(sdRad)));

  return -HA;              // in radians
}

double SunPosition::calcJD(int y, int m, int d)
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

double SunPosition::calcJDFromJulianCent(double t)
{
  double JD = t * 36525.0 + 2451545.0;
  return JD;
}

double SunPosition::calcSunEqOfCenter(double t)
{
  double m = calcGeomMeanAnomalySun(t);
  double mrad = degToRad(m);
  double sinm = sin(mrad);
  double sin2m = sin(mrad+mrad);
  double sin3m = sin(mrad+mrad+mrad);
  double C = sinm * (1.914602 - t * (0.004817 + 0.000014 * t)) + sin2m * (0.019993 - 0.000101 * t) + sin3m * 0.000289;

  return C;		// in degrees
}

double SunPosition::calcSunriseUTC()
{
  double t = calcTimeJulianCent(julianDate);
  // *** First pass to approximate sunrise
  double  eqTime = calcEquationOfTime(t);
  double  solarDec = calcSunDeclination(t);
  double  hourAngle = calcHourAngleSunrise(latitude, solarDec);
  double  delta = longitude - radToDeg(hourAngle);
  double  timeDiff = 4 * delta;	// in minutes of time
  double  timeUTC = 720 + timeDiff - eqTime;	// in minutes
  double  newt = calcTimeJulianCent(calcJDFromJulianCent(t) + timeUTC/1440.0);

  eqTime = calcEquationOfTime(newt);
  solarDec = calcSunDeclination(newt);

  hourAngle = calcHourAngleSunrise(latitude, solarDec);
  delta = longitude - radToDeg(hourAngle);
  timeDiff = 4 * delta;
  timeUTC = 720 + timeDiff - eqTime; // in minutes

  return timeUTC * 60;
}

double SunPosition::calcSunsetUTC()
{
  double t = calcTimeJulianCent(julianDate);
  // *** First pass to approximate sunset
  double  eqTime = calcEquationOfTime(t);
  double  solarDec = calcSunDeclination(t);
  double  hourAngle = calcHourAngleSunset(latitude, solarDec);
  double  delta = longitude - radToDeg(hourAngle);
  double  timeDiff = 4 * delta;	// in minutes of time
  double  timeUTC = 720 + timeDiff - eqTime;	// in minutes
  double  newt = calcTimeJulianCent(calcJDFromJulianCent(t) + timeUTC/1440.0);

  eqTime = calcEquationOfTime(newt);
  solarDec = calcSunDeclination(newt);

  hourAngle = calcHourAngleSunset(latitude, solarDec);
  delta = longitude - radToDeg(hourAngle);
  timeDiff = 4 * delta;
  timeUTC = 720 + timeDiff - eqTime; // in minutes

  return timeUTC * 60;	// return time in seconds which can work with time_t
}

void SunPosition::setCurrentDate(int y, int m, int d)
{
  julianDate = calcJD(y, m, d);
}

bool SunPosition::isSunset(time_t timeNow)
{
  if ((time_t)calcSunsetUTC() <= timeNow)
    return true;

  return false;
}

void SunPosition::todaySunsetString(char *fmt, char **rval, int size)
{

	strftime(rval,size,fmt,localtime(&seconds));
}

void SunPosition::todaySunriseString(char *fmt, char **rval, int size)
{

}

bool SunPosition::isSunrise(time_t timeNow)
{
  if ((time_t)calcSunriseUTC() <= timeNow)
    return true;

  return false;
}
