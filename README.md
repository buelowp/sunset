<h1>SunPosition</h1>
<h2>Uses GPS source (or alternate time source from a local RTC) to figure out sunrise and sunset times</h2>
<p>This is a modification of the sunrise.c posted by Mike Chirico back in 2004. See the link below to find it. I needed a mechanism to figure out when the sun would rise and set, but I was doing this with an Arduino and Teensy, which didn't have RTC capability, nor the standard time functions that Linux gives you. So, I found this, and glued a GPS receiver into my system. Now I can simply seed the class and ask for the local minutes past midnight when the sun will rise and set. I'm posting it here in case someone might find use in it.

<h2>Usage</h2>
SunPosition as a class is mostly simple. It expects a bunch of data for the calculations, and will return the number of minutes past midnight of the current day of when the sun will rise and set. You do this the following way.

One note is that this class uses a lot of memory. I haven't tried on an Uno or similar, but it probably won't fit. My suggestion is to use it on a Mega or Teensy to avoid space issues with memory.

```C++
SunPosition sun(latitude, longitude, timezone offset);
```
<ul>
<li>My usage is all stationary, so I can set the location up front and not worry about it. There is a setLocation call that takes the same arguments which can be called prior to each get operation.
<li>By default, SunPosition works without a DST factor applied. If you need DST enabled, then you set it. The setting persists until you turn it off specifically.
<li>latitude and longitude are in degrees and fractions of a degree, not degrees, minutes, and seconds. This is an important distinction, but one that GPS gives you for free. The values are double, and offset is a signed integer.
<li>offset is the TimeZone offset from UTC either positive or negative. If you're in NYC, then your offset would be -5. If you're in Munich, it would be 1.
</ul>
```C++
sun.setCurrentDate(year, month, date);
```
<ul>
<li>The values for year, month, and date are integer 1 based values. Don't zero base the month, or assume from 1900 such as the unix localtime() call does. If you want February 2nd, 2015, then the values for this call are 2015, 2, 2.
</li>
</ul>
```C++
sun.enabledDST();
sun.disableDST();
```
<ul>
<li>GPS doesn't give us a lot of heads up about DST values. And generally, we don't know because the systems this runs on generally do not have knowledge of DST values. You will have to set it yourself prior to asking for sunrise time.
</li>
</ul>
```C++
double sunrise = sun.calcSunrise();
double sunset = sun.calcSunset();
```
<ul>
<li>This returns the number of minutes past midnight for the specific event in your local timezone set above. Up to you how to use it. If you have access to time_t, then you can convert this to seconds past midnight by multiplying by 60.
<li>Call calcSunsetUTC() or calcSunriseUTC() for the UTC values
</ul>

I'll document more in the WiKi when I find the time. this is a good first start though.

You can find the original at http://souptonuts.sourceforge.net/code/sunrise.c.html

This updates it to be a C++ class for easier use by Arduino, Teensy, and other
embedded projects.
