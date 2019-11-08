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

#ifndef __SUNPOSITION_H__
#define __SUNPOSITION_H__

#define JD_EPOCH2000 2451545.0
#define SECONDS_PER_DAY 60.0*60.0*24.0
#define MOON_MONTH_SECONDS 2551443
#define MOON_MONTH_DAYS MOON_MONTH_SECONDS/SECONDS_PER_DAY




enum EVENT{RISE, SET};

enum MOON_EVENT{NEW,WAXING_CRESCENT,FIRST_QUARTER,WAXING_GIBBOUS,FULL,WANING_GIBBOUS,LAST_QUARTER, WANING_CRESCENT};


class SunSet {
public:
  SunSet();
  SunSet(double, double, int);
  ~SunSet();

  void setPosition(double, double, int);
  void setTZOffset(int);
  double setCurrentDate(int, int, int);
  double calcSunriseUTC();
  double calcSunsetUTC();
  double calcSunrise();
  double calcSunset();
  int moonPhase(int);
  int moonPhase();
  double moonRiseTime();
  double moonSetTime();
  double moonRiseUTC(int);
  double moonRise(int);
  double moonSetUTC(int);
  double moonSet(int);
  //


private:
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
  double calcSunrise_setUTC(int);
  double calcHourAngleSunrise(double, double);
  double calcHourAngleSunset(double, double);
  double calcJD(int,int,int);
  double calcJDFromJulianCent(double);
  double calcSunEqOfCenter(double);
  double moonShift(int fromepoch, EVENT e);
  //Utilities
  double timeToDeg(double);
  double degToTime(double);
  double degToRad(double);
  double radToDeg(double);
  double adjustDeg(double);
  double adjustTime(double);
  double adjustRad(double);
  double latitude;
  double longitude;
  double julianDate;
  int m_year;
  int m_month;
  int m_day;
  int tzOffset;

};
#endif
