<h1>Calculate Sunrise and Sunset based on time and latitude and longitude</h1>
<p>This is a modification of the sunrise.c posted by Mike Chirico back in 2004. See the link below to find it. I needed an algorithm that could tell me when it was dark out for all intents and purposes. I found Mike’s code, and modified it a bit to be a library that can be used again and again.

<h2>License</h2>
This is governed by the MIT license. Use it as you want, make changes as you want.

<h2>Details</h2>
To use SunPosition, you need to a few bits of local information.
<ol>
<li>Accurate time. If you’re running this with something that can get GPS time or use NTP, then results will always be very accurate. If you do not have a good clock source, then the results are going to be very accurate relative to your not so accurate clock. For the Photon, I use SparkTime and an NTP source. With my Teensy, I connect up a GPS source and read the time from that.</li>
<li>You need an accurate position, both latitude and longitude, so the library can figure out where you are. The library will only take longitude as a positive value, as it doesn’t matter. Putting in a negative value because the US is -80 something, means you will get odd results.</li>
<li>Prior to calculating sunrise or sunset, you must update the current date for the library, including DST if applicable. The library doesn’t track the date, so calling it every day without changing the date means you will always get the calculation for the last accurate date you gave it.</li>
<li>If you do not set the date, it defaults to midnight, January 1st of year 0</li>
<li>The library always calculates for UTC, but does apply a timezone offset. You can calculate both the offset and UTC with related function calls if you would like.</li>
<li>The library returns a double that indicates how many seconds past midnight relative to the set date that sunrise or sunset will happen. If the sun will rise at 6am local to the set location and date, then you will get a return value of 360.0. Decimal points indicate fractions of a minute. It’s up to you to figure out how to use the data.</li>
</ol>

The example provides the how to below, it's pretty simple. Every time you need the calculation call for it. I wouldn't suggest caching the value unless 
you can handle changes in date so the calculation is correct relative to a date you need.

SunPosition is a C++ class, and no C implementation is provided.

<h2>Moon Phases</h2>
This library also allows you to calculate the moon phase for the current day to an integer value. This means it's not perfectly accurate, but it's pretty close.
To use it, you call moonPhase() with an integer value that is the number of seconds from the January 1, 1970 epoch. It will do some simple math and return
an integer value that represents the current phase of the moon, from 0 to 29. In this case, 0 is new, and 29 is new, 15 is full. The code handles times that may
cause the calculation to return 30 to avoid some limits confustion (there aren't 30 days in the lunar cycle, but it's close enough that some time values will cause
it to return 30 anyway).

<h2>Examples</h2>
This is relative to an Arduino type environment. Create a global object, and initialize it and use it in loop().

<pre>
#include &ltctime&gt
#include &ltSunSet.h&gt
#define TIMEZONE	-5
#define LATITUDE	40.0000
#define LONGITUDE	89.0000

SunRise sun;

void setup()
{
	// Set your clock here to get accurate time and date
	// Next, tell SunRise where we are
	sun.setPosition(LATITUDE, LONGITUDE, TIMEZONE);
	sun.setCurrentDate(year(), month(), day());
}

void loop()
{
	double sunrise = sun.calcSunrise();
	double sunset = sun.calcSunset();
	double sunriseUTC = sun.calcSunriseUTC();
	double sunsetUTC = sun.calcSunriseUTC();
	int moonphase = sun.moonPhase(std::time(nullptr));
}
</pre>

<h2>Notes</h2>
<ul>
<li>This is a general purpose calculator, so you could calculate when Sunrise was on the day Shakespeare died. Hence some of the design decisions</li>
<li>Again, don’t use negative values for longitude, it doesn’t matter</li>
<li>Date values are absolute, are not zero based, and should not be abbreviated (e.g. don’t use 15 for 2015 or 0 for January)</li>
<li>This library may run well enough on a 16KHz Arduino, but it’s fairly math intensive and uses quite a bit of memory, so it won’t run fast. It works very well on the ARM M core chips like the Teensy and Photon though.</li>
<li>For time, I like the SparkTime for Photon which does a good job of keeping accurate time. GPS also works, but you will need to implement a way to calculate if your are DST or not. Other platforms will need to implement a good solution for keeping an accurate date.
<li>I can be used as a general purpose library on any Linux machine as well. You just need to compile it into your RPI or Beagle project.</li>
</ul>

<h2>Links</h2>
You can find the original math in c code at http://souptonuts.sourceforge.net/code/sunrise.c.html
<br>
I got the moon work from Ben Daglish at http://www.ben-daglish.net/moon.shtml

