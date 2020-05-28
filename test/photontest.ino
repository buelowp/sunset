// This #include statement was automatically added by the Particle IDE.
#include <sunset.h>

#define LATITUDE_AH     42.058102
#define LONGITUDE_AH    -87.984189
#define TIMEZONE_AH     -6

#define LATITUDE_CT     -33.9249
#define LONGITUDE_CT    18.4241
#define TIMEZONE_CT     2

#define LATITUDE_MC     55.7558
#define LONGITUDE_MC    37.617779
#define TIMEZONE_MC     3

#define LATITUDE_BA     -34.6037
#define LONGITUDE_BA    -58.3816
#define TIMEZONE_BA     -3

#define LATITUDE_PB     71.3875
#define LONGITUDE_PB    -156.4811
#define TIMEZONE_PB     -8

#define LATITUDE_US     -54.8019
#define LONGITUDE_US    -68.3030
#define TIMEZONE_US     -3

#define LATITUDE_ND     28.6139
#define LONGITUDE_ND    77.2090
#define TIMEZONE_ND     5.5

SunSet sun;
int g_testRun;

String Tests[] = {
    "Arlington Heights Sunrise",                    // 0
    "Arlington Heights Sunset",                     // 1
    "Moonphase",                                    // 2
    "Capetown Sunrise",                             // 3
    "Moscow Sunrise",                               // 4
    "Buenos Aires Sunrise",                        // 5
    "Astronomical Sunrise in Arlington Heights",    // 6
    "Astronomical Sunset in Arlington Heights",     // 7
    "Nautical Sunrise in Arlington Heights",        // 8
    "Nautical Sunset in Arlington Heights",         // 9
    "Civil Sunrise in Arlington Heights",           // 10
    "Civil Sunset in Arlington Heights",            // 11
    "Valid Julian Date",                            // 12
    "Point Barrow Summer",                          // 13
    "Point Barrow Spring",                          // 14
    "Point Barrow Winter",                          // 15
    "Ushuaia Argentina May",                        // 16
    "Ushuaia Argentina Winter",                     // 17
    "Fractional Sunrise IST",                       // 18
    "Fractional Sunset IST",                        // 19
    "Check above 67",                               // 20
};

String Results[] = {
    "437.817",                                      // 0
    "1005.001",                                    // 1
    "20",                                           // 2
    "350.350",                                       // 3
    "530.075",                                      // 4
    "356.131",                                      // 5
    "138.945",                                      // 6
    "1280.073",                                      // 7
    "187.513",                                      // 8
    "1231.172",                                      // 9
    "229.355",                                      // 10
    "1189.152",                                      // 11
    "2458994.5",                                    // 12
    "0.000",                                          // 13
    "495.298",                                      // 14
    "0.000",                                          // 15
    "576.845",                                      // 16
    "294.969",                                      // 17
    "325.266",                                      // 18
    "1151.487",                                      // 19
    "251",                                           // 20
};

void setup() 
{
    Serial.begin(115200);
    g_testRun = 0;
    delay(10000);
}

void loop() 
{
    String result;
    int count = 0;

    switch (g_testRun) {
        case 0:
            sun.setPosition(LATITUDE_AH, LONGITUDE_AH, TIMEZONE_AH);
            sun.setCurrentDate(2020, 1, 15);
            result = String(sun.calcSunrise(), 3);
            break;
        case 1:
            sun.setPosition(LATITUDE_AH, LONGITUDE_AH, TIMEZONE_AH);
            sun.setCurrentDate(2020, 1, 15);
            result = String(sun.calcSunset(), 3);
            break;
        case 2:
            result = String(sun.moonPhase(1579097467));
            break;
        case 3:
            sun.setPosition(LATITUDE_CT, LONGITUDE_CT, TIMEZONE_CT);
            sun.setCurrentDate(2020, 1, 15);
            result = String(sun.calcSunrise(), 3);
            break;
        case 4:
            sun.setPosition(LATITUDE_MC, LONGITUDE_MC, TIMEZONE_MC);
            sun.setCurrentDate(2020, 1, 15);
            result = String(sun.calcSunrise(), 3);
            break;
        case 5:
            sun.setPosition(LATITUDE_BA, LONGITUDE_BA, TIMEZONE_BA);
            sun.setCurrentDate(2020, 1, 15);
            result = String(sun.calcSunrise(), 3);
            break;
        case 6:
            sun.setPosition(LATITUDE_AH, LONGITUDE_AH, TIMEZONE_AH);
            sun.setCurrentDate(2020, 5, 25);
            result = String(sun.calcAstronomicalSunrise(), 3);
            break;
        case 7:
            sun.setPosition(LATITUDE_AH, LONGITUDE_AH, TIMEZONE_AH);
            sun.setCurrentDate(2020, 5, 25);
            result = String(sun.calcAstronomicalSunset(), 3);
            break;
        case 8:
            sun.setPosition(LATITUDE_AH, LONGITUDE_AH, TIMEZONE_AH);
            sun.setCurrentDate(2020, 5, 25);
            result = String(sun.calcNauticalSunrise(), 3);
            break;
        case 9:
            sun.setPosition(LATITUDE_AH, LONGITUDE_AH, TIMEZONE_AH);
            sun.setCurrentDate(2020, 5, 25);
            result = String(sun.calcNauticalSunset(), 3);
            break;
        case 10:
            sun.setPosition(LATITUDE_AH, LONGITUDE_AH, TIMEZONE_AH);
            sun.setCurrentDate(2020, 5, 25);
            result = String(sun.calcCivilSunrise(), 3);
            break;
        case 11:
            sun.setPosition(LATITUDE_AH, LONGITUDE_AH, TIMEZONE_AH);
            sun.setCurrentDate(2020, 5, 25);
            result = String(sun.calcCivilSunset(), 3);
            break;
        case 12:
            sun.setPosition(LATITUDE_AH, LONGITUDE_AH, TIMEZONE_AH);
            result = String(sun.setCurrentDate(2020, 5, 25), 1);
            break;
        case 13:
            sun.setPosition(LATITUDE_PB, LONGITUDE_PB, TIMEZONE_PB);
            sun.setCurrentDate(2020, 6, 21);
            result = String(sun.calcSunrise(), 3);
            break;
        case 14:
            sun.setPosition(LATITUDE_PB, LONGITUDE_PB, TIMEZONE_PB);
            sun.setCurrentDate(2020, 3, 21);
            result = String(sun.calcSunrise(), 3);
            break;
        case 15:
            sun.setPosition(LATITUDE_PB, LONGITUDE_PB, TIMEZONE_PB);
            sun.setCurrentDate(2020, 12, 21);
            result = String(sun.calcSunrise(), 3);
            break;
        case 16:
            sun.setPosition(LATITUDE_US, LONGITUDE_US, TIMEZONE_US);
            sun.setCurrentDate(2020, 5, 26);
            result = String(sun.calcSunrise(), 3);
            break;
        case 17:
            sun.setPosition(LATITUDE_US, LONGITUDE_US, TIMEZONE_US);
            sun.setCurrentDate(2020, 12, 26);
            result = String(sun.calcSunrise(), 3);
            break;
        case 18:
            sun.setPosition(LATITUDE_ND, LONGITUDE_ND, TIMEZONE_ND);
            sun.setCurrentDate(2020, 5, 26);
            result = String(sun.calcSunrise(), 3);
            break;
        case 19:
            sun.setPosition(LATITUDE_ND, LONGITUDE_ND, TIMEZONE_ND);
            sun.setCurrentDate(2020, 5, 26);
            result = String(sun.calcSunset(), 3);
            break;
        case 20:
            sun.setCurrentDate(2020, 5, 26);
            for (double i = 65.0; i < 90; i += .1) {
                sun.setPosition(i, LONGITUDE_AH, TIMEZONE_AH);
                sun.calcSunrise();
                count++;
            }
            result = String(count);
            break;
        default:
            return;
    }

        
    Serial.print("Running test ");
    Serial.print(Tests[g_testRun]);
    Serial.print(": ");

    if (result == Results[g_testRun]) {
        Serial.println("passed");
    }
    else {
        Serial.print("failed: Got ");
        Serial.print(result);
        Serial.print(" != ");
        Serial.println(Results[g_testRun]);
    }
    g_testRun++;
}
