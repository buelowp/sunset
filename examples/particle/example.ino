#include <sunset.h>

/* I'm in the midwest, so this is what I use for my home */
#define LATITUDE        41.12345
#define LONGITUDE       -87.98765
#define DST_OFFSET      -5

SunSet sun;
SerialLogHandler logHandler;

void setup()
{
    sun.setPosition(LATITUDE, LONGITUDE, DST_OFFSET);
}

void loop()
{
    static int currentDay = 32;
    int sunrise;
    int sunset;
    double civilsunrise;
    double civilsunset;
    double astrosunrise;
    double astrosunset;
    double nauticalsunrise;
    double nauticalsunset;
    double customsunrise;
    double customsunset;
    
    if (currentDay != Time.day()) {
        Particle.syncTime();
        waitUntil(Particle.syncTimeDone);
        sun.setCurrentDate(Time.year(), Time.month(), Time.day());
        currentDay = Time.day();
    }
    sunrise = static_cast<int>(sun.calcSunrise());
    sunset = static_cast<int>(sun.calcSunset());
    civilsunrise = sun.calcCivilSunrise();
    civilsunset = sun.calcCivilSunset();
    nauticalsunrise = sun.calcNauticalSunrise();
    nauticalsunset = sun.calcNauticalSunset();
    astrosunrise = sun.calcAstronomicalSunrise();
    astrosunset = sun.calcAstronomicalSunset();
    customsunrise = sun.calcCustomSunrise(90.0);
    customsunset = sun.calcCustomSuset(90.0);
    
    Log.info("Sunrise at %d:%dam, Sunset at %d:%dpm", (sunrise/60), (sunrise%60), (sunset/60), (sunset%60));
    Log.info("Civil Sunrise at %f mpm, Sunset at %f mpm", civilsunrise, civilsunset);
    Log.info("Nautical Sunrise at %f mpm, Sunset at %f mpm", nauticalsunrise, nauticalsunset);
    Log.info("Astronomical Sunrise at %f mpm, Sunset at %f mpm", astrosunrise, astrosunset);
    Log.info("Custom Sunrise at %f mpm, Sunset at %f mpm", customsunrise, customsunset);
    delay(1000);
}
