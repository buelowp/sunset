/*
    This file is part of WindowLights.

    SunPosition is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    SunPosition is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with Foobar.  If not, see <http://www.gnu.org/licenses/>.

    This implementation is taken and modified from Mike Chirico at
    http://souptonuts.sourceforge.net/code/sunrise.c.html

    Modifications done have been in the spirit of the GPL, and
    any copying or reuse of this header and class are subject to
    the GPL v2 or any later GPL at the users discretion.
    All thanks for this work go to Mike who made it pretty easy.
*/
#ifndef __SUNPOSITION_H__
#define __SUNPOSITION_H__

#include <math.h>
#include <time.h>

class SunPosition {
public:
  SunPosition();
  SunPosition(double, double, int);
  ~SunPosition();

  void setPosition(double, double, int);
  bool isSunset(time_t);
  bool isSunrise(time_t);
  void setTZOffset(int);
  void setCurrentDate(int, int, int);
  double calcSunriseUTC();
  double calcSunsetUTC();
  void todaySunsetString(char*, char**, int);
  void todaySunriseString(char*, char**, int);

private:
  double degToRad(double);
  double radToDeg(double);
  double calcMeanObliquityOfEcliptic(double);
  double calcGeomMeanLongSun(double);
  double calcObliquityCorrection(double);
  double calcEccentricityEarthOrbit(double);
  double calcGeomMeanAnomalySun(double);
  double calcEquationOfTime(double);
  double calcTimeJulianCent(double);
  double calcSunTrueLong(double);
  double calcSunApparentLong(double);
  double calcSunDeclination(double);
  double calcHourAngleSunrise(double, double);
  double calcHourAngleSunset(double, double);
  double calcJD(int,int,int);
  double calcJDFromJulianCent(double);
  double calcSunEqOfCenter(double);

  double latitude;
  double longitude;
  double julianDate;
  int tzOffset;
};

#endif
