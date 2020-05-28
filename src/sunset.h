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
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.    See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Foobar.    If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef __SUNPOSITION_H__
#define __SUNPOSITION_H__

#include <cmath>
#include <ctime>

#define SUNSET_OFFICIAL         90.833
#define SUNSET_NAUTICAL         102
#define SUNSET_CIVIL            96
#define SUNSET_ASTONOMICAL      108

#define SUNSET_INVALID_TZ_D     99.9
#define SUNSET_INVALID_TZ_I     99

/**
 * \class SunSet
 * 
 * This class controls all aspects of the operations. The math is done in private
 * functions, and the public API's allow for returning a sunrise/sunset value for the
 * given coordinates and timezone.
 * 
 * The resulting calculations are relative to midnight of the day you set in the
 * setCurrentDate() function. It does not return a time_t value for delta from the
 * current epoch as that would not make sense as the sunrise/sunset can be calculated
 * thousands of years in the past. The library acts on a day timeframe, and doesn't
 * try to assume anything about any other unit of measurement other than the current
 * set day.
 * 
 * You can instantiate this class a few different ways, depending on your needs. It's possible
 * to set your location one time and forget about doing that again if you don't plan to move.
 * Then you only need to change the date and timezone to get correct data. Or, you can
 * simply create an object with no location or time data and then do that later. This is
 * a good mechanism for the setup()/loop() construct.
 * 
 * The most important thing to remember is to make sure the library knows the exact date and
 * timezone for the sunrise/sunset you are trying to calculate. Not doing so means you are going
 * to have very odd results. It's reasonably easy to know when you've forgotten one or the other
 * by looking at the time the sun would rise and noticing that it is X hours earlier or later.
 * That is, if you get a return of 128 minutes (2:08 AM) past midnight when the sun should rise 
 * at 308 (6:08 AM), then you probably forgot to set your EST timezone.
 * 
 * The library also has no idea about daylight savings time. If your timezone changes during the
 * year to account for savings time, you must update your timezone accordingly.
 */
class SunSet {
public:
    SunSet();
    SunSet(double, double, int);
    SunSet(double, double, double);
    ~SunSet();

    void setPosition(double, double, int);
    void setPosition(double, double, double);
    void setTZOffset(int);
    void setTZOffset(double);
    double setCurrentDate(int, int, int);
    double calcNauticalSunrise();
    double calcNauticalSunset();
    double calcCivilSunrise();
    double calcCivilSunset();
    double calcAstronomicalSunrise();
    double calcAstronomicalSunset();
    [[deprecated("UTC specific calls may not be supported in the future")]] double calcSunriseUTC();
    [[deprecated("UTC specific calls may not be supported in the future")]] double calcSunsetUTC();
    double calcSunrise();
    double calcSunset();
    int moonPhase(int);
    int moonPhase();

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
    double calcHourAngleSunrise(double, double, double);
    double calcHourAngleSunset(double, double, double);
    double calcJD(int,int,int);
    double calcJDFromJulianCent(double);
    double calcSunEqOfCenter(double);
    double calcAbsSunrise(double);
    double calcAbsSunset(double);

    double m_latitude;
    double m_longitude;
    double m_julianDate;
    double m_tzOffset;
    int m_year;
    int m_month;
    int m_day;
};

#endif
