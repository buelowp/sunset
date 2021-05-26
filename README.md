# Calculate Sunrise and Sunset based on time and latitude and longitude
This is a modification of the sunrise.c posted by Mike Chirico back in 2004. See the link below to find it. I needed an algorithm that could tell me when it was dark out for all intents and purposes. I found Mike’s code, and modified it a bit to be a library that can be used again and again.

Since then, I have updated it a bit to do some more work. It will calculate the Moon position generically. Since version 1.1.0, it will also calculate other sunrise/sunset times depending on your needs.

* Can accurately calculate Standard Sunrise and Sunset
* Can accurately calculate Nautical Sunrise and Sunset
* Can accurately calculate Civil Sunrise and Sunset
* Can accurately calculate Astronomical Sunrise and Sunset

# New Github Pages
Find Doxygen documentation at https://buelowp.github.io/sunset/
 
# Version 1.1.1 IMPORTANT changes
I have migrated to an all lower case file name structure. Starting with master and 1.1.1, you must use

```
#include <sunset.h>
```

Instead of SunSet.h in the previous versions. This change was originally caused by the changes to the Particle build system where I use this library extensively. They forced me to name the file the same as the package name which resulted in an upper and lower case name. Now it's all lower case, pry the way I should have started it.

I've also change the google test enable variable, though I'm not sure many used that. I've updated the readme below to reflect the change.

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
cmake -DBUILD_TESTS=ON ..
make
./sunset-test
```

# Supported targets

This should work on any platform that supports C++ 14 and later. There is a hard requirement on 32 bit systems at a minimum due to needing full 32 bit integers for some of the work.

I have used this library on the following systems successfully, and test it on a Raspberry PI. It really does require a 32 bit system at a minimum, and due to the math needs, a 32 bit processor that has native floating point support is best. This does mean that the original Arudino and other similar 8 bit micros cannot use this library correctly.

## Tested against directly
* Ubuntu 20.04 g++
* Particle Photon (latest ParticleOS release 1.5.2 works with Sunset 1.1.0)

## Used with historically
* Raspberry PI
* Omega Onion
* Teensy with GPS
* SAMD targets using PIO/VSCode

I have used the following build systems with this library as well

* Raspberry PI command line
* Onion cross compiled using KDevelop and Eclipse
* Arudino IDE (must be for 32 bit micros)
* VS Code for Particle

I don't use PlatformIO for much but some compile time testing. I can't help much with that platform.

See notes below for the ESP devices, ESP32 and ESP8266.

# Testing

I primarily use google test to validate the code running under Linux. This is done with the cmake config test above. I also run a small ino on a Particle Photon to prove that it works against a micro as well. Test results can be found for the latest release on the release page.

# Details
To use SunSet, you need to a few bits of local information.
1. Accurate time. If you’re running this with something that can get GPS time or use NTP, then results will always be very accurate. If you do not have a good clock source, then the results are going to be very accurate relative to your not so accurate clock. For best results, make sure your clock is accurate to within a second if possible. Note that you also need an accurate timezone as the calculation is to UTC, and then the timezone is applied before the value is returned. If your results seem off by some set number of hours, a bad or missing timezone is probably why.
1. You need an accurate position, both latitude and longitude, which the library needs to provide accurate timing. Note that it does rely on positive or negative longitude, so you are at -100 longitude, but put 100 longitude in, you will get invalid results.
1. To get accurate results for your location, you need both the Latitude and Longitude, AND a local timezone.
   * All math is done without a timezone, (timezone = 0). Therefore, to make sure you get accurate results for your location, you must set a local timezone for the LAT and LON you are using. You can tell if you made a mistake when the result you get is negative for sunrise.
1. Prior to calculating sunrise or sunset, you must update the current date for the library, including the required timezone. The library doesn’t track the date, so calling it every day without changing the date means you will always get the calculation for the last accurate date you gave it. If you do not set the date, it defaults to midnight, January 1st of year 0 in the Gregorian calendar.
1. Since all calculations are done in UTC, it is possible to know what time sunrise is in your location without a timezone. Call calcSunriseUTC for this detail.
   * This isn't very useful in the long run, so the UTC functions will be deprecated. The new civil, astro, and nautical API's do not include the UTC analog. This is by design.
1. The library returns a double that indicates how many minutes past midnight relative to the set date that sunrise or sunset will happen. If the sun will rise at 6am local to the set location and date, then you will get a return value of 360.0. Decimal points indicate fractions of a minute.
   * Note that the library may return 359.89 for a 6 AM result. Doubles don't map to times very well, so the actual return value IS correct, but should be rounded up if so desired to match other calculators.
1. The library may return NaN or 0 for instances where there is no real sunrise or sunset value (above the arctic circle in summer as an example). The differences seem to be compiler and platform related, and is not something I am currently doing something about. Correctly checking for return value is a critical need and not ignoring 0 or NaN will make this library work better for you in the long run.
   * This library does some pretty intensive math, so devices without an FPU are going to run slower because of it. As of version 1.1.3, this library does work for the ESP8266, but this is not an indication that it will run on all non FPU enabled devices.
1. This library has a hard requirement on 32 bit precision for the device you are using. 8 or 16 bit micros are not supported.


The example below gives some hints for using the library, it's pretty simple. Every time you need the calculation, call for it. I wouldn't suggest caching the value unless you can handle changes in date so the calculation is correct relative to a date you need.

SunSet is C++, no C implementation is provided. It is compiled using C++14, and any code using it should use C++14 as well as there is a dependency on C++14 at a minimum. Newer C++ versions work as well.

# Releases
* 1.1.6 Fixing issues with library version numbering
* 1.1.5 Bug fixes
  * Issue #26 - Code quality issue in function calcGeomMeanLongSun?
  * Issue #28 - Add option to override cmake build settings via variables
  * Issue #29 - Fix warning for platforms that cannot build shared objects
  * Issue #31 - Member functions that should be const aren't
  * Issue #32 - Expose calcAbsSunset style interface, so custom offsets can be used
  * Issue #33 - Remove unnecessary define statements
  * Issue #34 - Fix missing precision cast in calcJD
  * Issue #37 - typo in examples/esp/example.ino
* 1.1.4 Making this work for Arduino and the library manager via Include Library
* 1.1.3 Performance improvements to enable the ESP8266 to function better. Thank you to https://github.com/Glichy.
* 1.1.2 Bumping the library.properties license field to be correct. This forced a new release number so it would work with build systems.
* 1.1.1 Changes to support case insensitive file systems.
* 1.1.0 New capabilities. Added Civil, Nautical, and Astronomical sunrise and sunset.
  * New API's for the new functionality. See the code for details.
  * Begin to deprecate UTC functions. These will not be removed until later if ever. They are not tested as well.
  * Migrate timezone to be a double for fractional timezones. IST for example works correctly now.
* 1.0.11 Fixes related to making SAMD targets compile. SAMD doesn't like std::chrono it seems.
* 1.0.10 Fixed a bug in a header file, it should build for all platforms now.
* 1.0.9: Revert some imported changes which broke the system.
* 1.0.8: Fix installation path issue and update README to include installation instructions.
* 1.0.7: Allows for use of positive or negative longitude values. Thank you to https://github.com/nliviu.

# Moon Phases
This library also allows you to calculate the moon phase for the current day to an integer value. This means it's not perfectly accurate, but it's pretty close. To use it, you call moonPhase() with an integer value that is the number of seconds from the January 1, 1970 epoch. It will do some simple math and return an integer value that represents the current phase of the moon, from 0 to 29. In this case, 0 is new, and 29 is new, 15 is full. The code handles times that may cause the calculation to return 30 to avoid some limits confusion (there aren't 30 days in the lunar cycle, but it's close enough that some time values will cause it to return 30 anyway).

# Examples
This example is relative to an .ino file. Create a global object, initialize it and use it in loop().

```
#include <time>
#include <sunset.h>
#define TIMEZONE	-5
#define LATITUDE	40.0000
#define LONGITUDE	-89.0000
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
    int moonphase = sun.moonPhase(std::time(nullptr));
}
```

This example is for the Raspberry Pi using C++

```
#include <ctime>
#include <sunset.h>

#define ONE_HOUR	(60 * 60)
#define TIMEZONE	-5
#define LATITUDE	40.0000
#define LONGITUDE	-89.0000
// This location is near Chicago, Illinois USA
void main(int argc, char *argv)
{
    SunSet sun;
    
    auto rightnow = std::time(nullptr);
    struct tm *tad = std::localtime(&rightnow);
    
    sun.setPosition(lat, lon, tad->tm_gmtoff / ONE_HOUR);
    sun.setCurrentDate(tad->tm_year + 1900, tad->tm_mon + 1, tad->tm_mday);
    double sunrise = sun.calcSunrise();
    double sunset = sun.calcSunsetLocal();
    double civilSunrise = sun.calcCivilSunrise();
    double nauticalSunrise = sun.calcNauticalSunrise();
    double astroSunrise = sun.calcAstronomicalSunrise();
    int moonphase = sun.moonPhase(static_cast<int>(rightnow));
}

```

# Notes

* This is a general purpose calculator, so you could calculate when Sunrise was on the day Shakespeare died. Hence some of the design decisions.
* Date values are absolute, are not zero based, and should not be abbreviated. (e.g. don’t use 15 for 2015 or 0 for January)
* This library has a hard requirement on a 32 bit micro with native hard float. Soft float micros *do* work, but may have issues. The math is pretty intensive.
* It is important to remember you MUST have accurate date and time. The calculations are time sensitive, and if you aren't accurate, the results will be obvious. Note that the library does not use hours, minutes, or seconds, just the date, so syncing time a lot won't help, just making sure it's accurate at midnight so you can set the date before calling the calc functions. Knowing when to update the timzone for savings time if applicaple is also pretty important.
* It can be used as a general purpose library on any Linux machine, as well as on an Arduino or Particle Photon. You just need to compile it into your RPI or Beagle project using cmake 3.0 or later.
* UTC is not the UTC sunrise time, it is the time in Greenwhich when the sun would rise at the location specified to the library. It's weird, but allows for some flexibility when doing calcualations depending on how you keep track of time in your system. The UTC specific calls are being deprecated starting with 1.1.0.
* Use of Civil, Nautical, and Astronomical values are interesting for lots of new uses of the library. They are added as a convenience, but hopefully will prove useful. These functions do not have equal UTC functions.
* I do not build or test on a Windows target. I don't have a Windows machine to do so. I do test this on a Mac, but only lightly and not every release right now.

# ESP Devices
The popular ESP devices seem to have some inconsistencies. While it is possible to run on the 8266, which has no FPU but is 32bit, the math is slow, and if you are doing time constrained activities, there is no specific guarantee that this library will work for you. Testing shows it does work well enough, but use it at your own risk.

Using this library with an ESP8266 is not considered a valid or tested combination, though it may work for you. I will not attempt to support any issues raised against the 8266 that can't be duplicated on an ESP32.

The ESP32 also has some FPU issues, though testing confirms it works very well and does not slow the system in any measurable way.

* https://www.esp32.com/viewtopic.php?f=14&t=800
* https://blog.classycode.com/esp32-floating-point-performance-6e9f6f567a69

The conclusions in the links seem to indicate that a lot of the math used by this library may be slow on the ESP8266 processors. However, slow in this case is still milliseconds, so it may not matter on the 8266 at all. Your mileage might vary.

# Links
You can find the original math in c code at http://souptonuts.sourceforge.net/code/sunrise.c.html

I got the moon work from Ben Daglish at http://www.ben-daglish.net/moon.shtml

# Thank you to

The following contributors have helped me identify issues and add features. The individuals are listed in no particular order.

* https://github.com/ASL07
* https://github.com/ThothK
* https://github.com/CaspianMaster
* https://github.com/rhn
* https://github.com/Glichy
* https://github.com/enbyted
* https://github.com/kebekus
