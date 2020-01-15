# Calculate Sunrise and Sunset based on time and latitude and longitude</h1>
This is a modification of the sunrise.c posted by Mike Chirico back in 2004. See the link below to find it. I needed an algorithm that could tell me when it was dark out for all intents and purposes. I found Mike’s code, and modified it a bit to be a library that can be used again and again.

# License
This is governed by the GPL2 license. See the License terms in the LICENSE file. Use it as you want, make changes as you want, but please contribute back in accordance with the GPL.

# Building

## Building for any cmake target
The builder requires CMake 3.0.0 or newer, which should be available in most Linux distributions.

```
mkdir build
cd build
cmake ..
make
make DESTDIR=<some path> install
```

Note that by default, the installer will attempt to install to /usr/local/include and /usr/local/lib or the equivalent for Windows.

## Building with Google Test for library verification

You can use google test by doing the following

```
mkdir build
cd build
cmake -DPLATFORM_TESTING=ON ..
make
./sunset-test
```

# Supported targets

This should work on any platform that supports C++ 14 and later. However, it is exceptionally math intensive, and as such, will be very slow on 8 bit microcontrollers.

I have created a released library for the Particle build system, which you can find if you search for the sunset library. It is also buildable as a Linux C++ library. Porting to other build systems is possible, but outside of my willingness to support.

# Details
To use SunPosition, you need to a few bits of local information.
1. Accurate time. If you’re running this with something that can get GPS time or use NTP, then results will always be very accurate. If you do not have a good clock source, then the results are going to be very accurate relative to your not so accurate clock. For best results, make sure your clock is accurate to within a second if possible. Note that you also need an accurate timezone as the calculation is to UTC, and then the timezone is applied before the value is returned. If your results seem off by some set number of hours, a bad or missing timezone is probably why.
1. You need an accurate position, both latitude and longitude, which the library needs to provide accurate timing.
1. To get accurate results for your location, you need both the Latitude and Longitude, AND a local timezone. Without the timezone, the calcuations done are relative to UTC which may not be useful. Note that UTC isn't sunrise in Greenwhich, it is the UTC time when sunrises in your location.
1. Prior to calculating sunrise or sunset, you must update the current date for the library, including the required timezone. The library doesn’t track the date, so calling it every day without changing the date means you will always get the calculation for the last accurate date you gave it. If you do not set the date, it defaults to midnight, January 1st of year 0
1. You can calculate for both the local timezone offset and UTC with related function calls if you would like. Local time calculations will return the number of minutes past midnight relative to your provided timezone. The UTC calculation will return the UTC time at your location, not the time in Greenwich.
1. The library returns a double that indicates how many minutes past midnight relative to the set date that sunrise or sunset will happen. If the sun will rise at 6am local to the set location and date, then you will get a return value of 360.0. Decimal points indicate fractions of a minute.

The example provides the how to below, it's pretty simple. Every time you need the calculation call for it. I wouldn't suggest caching the value unless you can handle changes in date so the calculation is correct relative to a date you need.

SunPosition is C++, no C implementation is provided.

# Releases
* 1.0.9: Revert some imported changes which broke the system
* 1.0.8: Fix installation path issue and update README to include installation instructions
* 1.0.7: Allowes for use of positive or negative longitude values. Thank you to https://github.com/nliviu

# Moon Phases
This library also allows you to calculate the moon phase for the current day to an integer value. This means it's not perfectly accurate, but it's pretty close. To use it, you call moonPhase() with an integer value that is the number of seconds from the January 1, 1970 epoch. It will do some simple math and return an integer value that represents the current phase of the moon, from 0 to 29. In this case, 0 is new, and 29 is new, 15 is full. The code handles times that may cause the calculation to return 30 to avoid some limits confustion (there aren't 30 days in the lunar cycle, but it's close enough that some time values will cause it to return 30 anyway).

# Examples
This example is relative to an .ino file. Create a global object, and initialize it and use it in loop().

```
#include <time>
#include <SunSet.h>
#define TIMEZONE	-5
#define LATITUDE	40.0000
#define LONGITUDE	89.0000
// Note that LONGITUDE can be positive or negative, but the original code will fail if you use a negative value
// Using a negative longitude does not impact, as it's the same either way. The code compensates for a negative value

SunSet sun;

void setup()
{
    // Set your clock here to get accurate time and date
    // Next, tell SunRise where we are
    sun.setPosition(LATITUDE, LONGITUDE, TIMEZONE);
}

void loop()
{
    // You should always set the date to be accurate
    sun.setCurrentDate(year(), month(), day());
    // If you have daylight savings time, make sure you set the timezone appropriately as well
    sun.setTZOffset(TIMEZONE);
    double sunrise = sun.calcSunrise();
    double sunset = sun.calcSunset();
    double sunriseUTC = sun.calcSunriseUTC();
    double sunsetUTC = sun.calcSunsetUTC();
    int moonphase = sun.moonPhase(std::time(nullptr));
}
```

This example is for the Raspberry Pi using C++

```
#include <ctime>
#include <SunSet.h>

#define ONE_HOUR	(60 * 60)
#define TIMEZONE	-5
#define LATITUDE	40.0000
#define LONGITUDE	89.0000
// Note that LONGITUDE can be positive or negative, but the original code will fail if you use a negative value
// Using a negative longitude does not impact, as it's the same either way. The code compensates for a negative value

void main(int argc, char *argv)
{
    SunSet sun;
    
    auto rightnow = std::time(nullptr);
    struct tm *tad = std::localtime(&rightnow);
    
    m_sun.setPosition(lat, lon, tad->tm_gmtoff / ONE_HOUR);
    m_sun.setCurrentDate(tad->tm_year + 1900, tad->tm_mon + 1, tad->tm_mday);
    double sunrise = sun.calcSunrise();
    double sunset = sun.calcSunset();
    double sunriseUTC = sun.calcSunriseUTC();
    double sunsetUTC = sun.calcSunsetUTC();
    int moonphase = sun.moonPhase(rightnow);
}

```

# Notes

* This is a general purpose calculator, so you could calculate when Sunrise was on the day Shakespeare died. Hence some of the design decisions
* Date values are absolute, are not zero based, and should not be abbreviated (e.g. don’t use 15 for 2015 or 0 for January)
* This library may run well enough on a 16KHz Arduino, but it’s fairly math intensive and uses quite a bit of memory, so it won’t run fast. It works very well on the ARM M core chips like the Teensy and Photon though.
* It is important to remember you MUST have accurate date and time. The calculations are time sensitive, and if you aren't accurate the results will be obvious. Note that the library does not use hours, minutes, or seconds, just the date, so syncing time a lot won't help, just making sure it's accurate at midnight so you can set the date before calling the calc functions. Knowing when to update the timzone for savings time if applicaple is also pretty important.
* It can be used as a general purpose library on any Linux machine as well as on an Arduino or Particle Photon. You just need to compile it into your RPI or Beagle project using cmake 3.0 or later.
* UTC is not the UTC sunrise time, it is the time in Greenwhich when the sun would rise at the location specified to the library. It's werid, but allows for some flexibility when doing calcualations depending on how you keep track of time in your system.

# Links
You can find the original math in c code at http://souptonuts.sourceforge.net/code/sunrise.c.html

I got the moon work from Ben Daglish at http://www.ben-daglish.net/moon.shtml

