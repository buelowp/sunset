#include <gtest/gtest.h>
#include <ctime>
#include <string>
#include <sstream>
#include <math.h>

#include "sunset.h"

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

#define INVALID_NEG_TZ  -13
#define INVALID_POS_TZ  15

namespace
{
    TEST(SunsetTesting, ValidReturnValueSunrise)
    {
        SunSet sun;
        std::string expected("437.817");
        std::stringstream ss(std::stringstream::in | std::stringstream::out);
        
        sun.setPosition(LATITUDE_AH, LONGITUDE_AH, TIMEZONE_AH);
        sun.setCurrentDate(2020, 1, 15);
        ss << std::setprecision(6) << sun.calcSunrise();
        
        EXPECT_EQ(ss.str(), expected) << "Returned: " << ss.str();
    }
    
    TEST(SunsetTesting, ValidReturnValueSunset)
    {
        SunSet sun;

        std::string expected("1005.0013");
        std::stringstream ss(std::stringstream::in | std::stringstream::out);
        
        sun.setPosition(LATITUDE_AH, LONGITUDE_AH, TIMEZONE_AH);
        sun.setCurrentDate(2020, 1, 15);
        ss << std::setprecision(8) << sun.calcSunset();
        
        EXPECT_EQ(ss.str(), expected) << "Returned: " << ss.str();
    }

    TEST(SunsetTesting, ValidReturnValueCustomSunrise)
    {
        SunSet sun;
        std::string expected("437.817");
        std::stringstream ss(std::stringstream::in | std::stringstream::out);
        
        sun.setPosition(LATITUDE_AH, LONGITUDE_AH, TIMEZONE_AH);
        sun.setCurrentDate(2020, 1, 15);
        ss << std::setprecision(6) << sun.calcCustomSunrise(90.833);
        
        EXPECT_EQ(ss.str(), expected) << "Returned: " << ss.str();
    }
    
    TEST(SunsetTesting, ValidReturnValueCustomSunset)
    {
        SunSet sun;

        std::string expected("1005.0013");
        std::stringstream ss(std::stringstream::in | std::stringstream::out);
        
        sun.setPosition(LATITUDE_AH, LONGITUDE_AH, TIMEZONE_AH);
        sun.setCurrentDate(2020, 1, 15);
        ss << std::setprecision(8) << sun.calcCustomSunset(90.833);
        
        EXPECT_EQ(ss.str(), expected) << "Returned: " << ss.str();
    }

    TEST(SunsetTesting, MoonPhase)
    {
        SunSet sun;
        
        sun.setPosition(LATITUDE_AH, LONGITUDE_AH, TIMEZONE_AH);
        sun.setCurrentDate(2020, 1, 15);
        
        EXPECT_EQ(sun.moonPhase(1579097467), 20) << "Returned: " << sun.moonPhase() << ", epoch is " << 1579097467;
    }
    
    TEST(SunsetTesting, NegativeLatitudeCapeTown)
    {
        SunSet sun;
        std::string expected("350.35");
        std::stringstream ss(std::stringstream::in | std::stringstream::out);
        
        sun.setPosition(LATITUDE_CT, LONGITUDE_CT, TIMEZONE_CT);
        sun.setCurrentDate(2020, 1, 15);
        ss << std::setprecision(6) << sun.calcSunrise();
        
        EXPECT_EQ(ss.str(), expected) << "Returned: " << ss.str();
    }
    
    TEST(SunsetTesting, PositiveLongitudeMoscow)
    {
        SunSet sun;
        std::string expected("530.075");
        std::stringstream ss(std::stringstream::in | std::stringstream::out);
        
        sun.setPosition(LATITUDE_MC, LONGITUDE_MC, TIMEZONE_MC);
        sun.setCurrentDate(2020, 1, 15);
        ss << std::setprecision(6) << sun.calcSunrise();
        
        EXPECT_EQ(ss.str(), expected) << "Returned: " << ss.str();
    }
    
    TEST(SunsetTesting, AllNegativeBuenosAires)
    {
        SunSet sun;
        std::string expected("356.131");
        std::stringstream ss(std::stringstream::in | std::stringstream::out);
        
        sun.setPosition(LATITUDE_BA, LONGITUDE_BA, TIMEZONE_BA);
        sun.setCurrentDate(2020, 1, 15);
        ss << std::setprecision(6) << sun.calcSunrise();
        
        EXPECT_EQ(ss.str(), expected) << "Returned: " << ss.str();
    }

    TEST(SunsetTesting, ValidAstronomicalSunriseArlingtonHeights)
    {
        SunSet sun;
        std::string expected("138.945");
        std::stringstream ss(std::stringstream::in | std::stringstream::out);
        
        sun.setPosition(LATITUDE_AH, LONGITUDE_AH, TIMEZONE_AH);
        sun.setCurrentDate(2020, 5, 25);
        ss << std::setprecision(6) << sun.calcAstronomicalSunrise();
        
        EXPECT_EQ(ss.str(), expected) << "Returned: " << ss.str();
    }
    
    TEST(SunsetTesting, ValidAstronomicalSunsetArlingtonHeights)
    {
        SunSet sun;
        std::string expected("1280.07");
        std::stringstream ss(std::stringstream::in | std::stringstream::out);
        
        sun.setPosition(LATITUDE_AH, LONGITUDE_AH, TIMEZONE_AH);
        sun.setCurrentDate(2020, 5, 25);
        ss << std::setprecision(6) << sun.calcAstronomicalSunset();
        
        EXPECT_EQ(ss.str(), expected) << "Returned: " << ss.str();
    }

    TEST(SunsetTesting, ValidNauticalSunriseArlingtonHeights)
    {
        SunSet sun;
        std::string expected("187.513");
        std::stringstream ss(std::stringstream::in | std::stringstream::out);
        
        sun.setPosition(LATITUDE_AH, LONGITUDE_AH, TIMEZONE_AH);
        sun.setCurrentDate(2020, 5, 25);
        ss << std::setprecision(6) << sun.calcNauticalSunrise();
        
        EXPECT_EQ(ss.str(), expected) << "Returned: " << ss.str();
    }
    
    TEST(SunsetTesting, ValidNauticalSunsetArlingtonHeights)
    {
        SunSet sun;
        std::string expected("1231.17");
        std::stringstream ss(std::stringstream::in | std::stringstream::out);
        
         sun.setPosition(LATITUDE_AH, LONGITUDE_AH, TIMEZONE_AH);
        sun.setCurrentDate(2020, 5, 25);
        ss << std::setprecision(6) << sun.calcNauticalSunset();
        
        EXPECT_EQ(ss.str(), expected) << "Returned: " << ss.str();
    }

    TEST(SunsetTesting, ValidCivilSunriseArlingtonHeights)
    {
        SunSet sun;
        std::string expected("229.355");
        std::stringstream ss(std::stringstream::in | std::stringstream::out);
        
        sun.setPosition(LATITUDE_AH, LONGITUDE_AH, TIMEZONE_AH);
        sun.setCurrentDate(2020, 5, 25);
        ss << std::setprecision(6) << sun.calcCivilSunrise();
        
        EXPECT_EQ(ss.str(), expected) << "Returned: " << ss.str();
    }
    
    TEST(SunsetTesting, ValidCivilSunsetArlingtonHeights)
    {
        SunSet sun;
        std::string expected("1189.15");
        std::stringstream ss(std::stringstream::in | std::stringstream::out);
        
        sun.setPosition(LATITUDE_AH, LONGITUDE_AH, TIMEZONE_AH);
        sun.setCurrentDate(2020, 5, 25);
        ss << std::setprecision(6) << sun.calcCivilSunset();
        
        EXPECT_EQ(ss.str(), expected) << "Returned: " << ss.str();
    }

    TEST(SunsetTesting, ValidJulianDate)
    {
        SunSet sun;
        std::string expected("2458994.5");
        std::stringstream ss(std::stringstream::in | std::stringstream::out);
        
        sun.setPosition(LATITUDE_AH, LONGITUDE_AH, TIMEZONE_AH);
        double jd = sun.setCurrentDate(2020, 5, 25);
        ss << std::setprecision(8) << jd;
        
        EXPECT_EQ(ss.str(), expected) << "Returned: " << ss.str();
    }
        
    TEST(SunsetTesting, HighLatitudeTestSummer)
    {
        SunSet sun;
        
        sun.setPosition(LATITUDE_PB, LONGITUDE_PB, TIMEZONE_PB);
        sun.setCurrentDate(2020, 6, 21);
        double rval = sun.calcSunrise();
        
        EXPECT_EQ(isnan(rval), true) << "Returned: " << rval;
    }

    TEST(SunsetTesting, HighLatitudeTestSpring)
    {
        SunSet sun;
        
        std::string expected("495.2976");
        std::stringstream ss(std::stringstream::in | std::stringstream::out);
        sun.setPosition(LATITUDE_PB, LONGITUDE_PB, TIMEZONE_PB);
        sun.setCurrentDate(2020, 3, 21);
        double rval = sun.calcSunrise();

        ss << std::setprecision(8) << rval;
        
        EXPECT_EQ(ss.str(), expected) << "Returned: " << ss.str();
    }

    TEST(SunsetTesting, HighLatitudeTestWinter)
    {
        SunSet sun;
        
        sun.setPosition(LATITUDE_PB, LONGITUDE_PB, TIMEZONE_PB);
        sun.setCurrentDate(2020, 12, 21);
        double rval = sun.calcSunrise();
        
        EXPECT_EQ(isnan(rval), true) << "Returned: " << rval;
    }

    TEST(SunsetTesting, SouthernMostPointMay)
    {
        SunSet sun;
        std::string expected("576.8452");
        std::stringstream ss(std::stringstream::in | std::stringstream::out);
        
        sun.setPosition(LATITUDE_US, LONGITUDE_US, TIMEZONE_US);
        sun.setCurrentDate(2020, 5, 26);
        ss << std::setprecision(8) << sun.calcSunrise();
        
        EXPECT_EQ(ss.str(), expected) << "Returned: " << ss.str();
    }

    TEST(SunsetTesting, SouthernMostPointWinter)
    {
        SunSet sun;
        std::string expected("294.96866");
        std::stringstream ss(std::stringstream::in | std::stringstream::out);
        
        sun.setPosition(LATITUDE_US, LONGITUDE_US, TIMEZONE_US);
        sun.setCurrentDate(2020, 12, 26);
        ss << std::setprecision(8) << sun.calcSunrise();
        
        EXPECT_EQ(ss.str(), expected) << "Returned: " << ss.str();
    }

    TEST(SunsetTesting, ValidReturnFractionalTimezoneSunrise)
    {
        SunSet sun;
        std::string expected("325.266");
        std::stringstream ss(std::stringstream::in | std::stringstream::out);
        
        sun.setPosition(LATITUDE_ND, LONGITUDE_ND, TIMEZONE_ND);
        sun.setCurrentDate(2020, 5, 26);
        ss << std::setprecision(6) << sun.calcSunrise();
        
        EXPECT_EQ(ss.str(), expected) << "Returned: " << ss.str();
    }
    
    TEST(SunsetTesting, ValidReturnFractionalTimezoneSunset)
    {
        SunSet sun;

        std::string expected("1151.4867");
        std::stringstream ss(std::stringstream::in | std::stringstream::out);
        
        sun.setPosition(LATITUDE_ND, LONGITUDE_ND, TIMEZONE_ND);
        sun.setCurrentDate(2020, 5, 26);
        ss << std::setprecision(8) << sun.calcSunset();
        
        EXPECT_EQ(ss.str(), expected) << "Returned: " << ss.str();
    }

    TEST(SunsetTesting, InvalidNegativeTimezone)
    {
        SunSet sun;

        std::string expected("821.48674");
        std::stringstream ss(std::stringstream::in | std::stringstream::out);
        
        sun.setPosition(LATITUDE_ND, LONGITUDE_ND, INVALID_NEG_TZ);
        sun.setCurrentDate(2020, 5, 26);
        ss << std::setprecision(8) << sun.calcSunset();
        
        EXPECT_EQ(ss.str(), expected) << "Returned: " << ss.str();
    }

    TEST(SunsetTesting, InvalidPositiveTimezone)
    {
        SunSet sun;

        std::string expected("821.48674");
        std::stringstream ss(std::stringstream::in | std::stringstream::out);
        
        sun.setPosition(LATITUDE_ND, LONGITUDE_ND, INVALID_POS_TZ);
        sun.setCurrentDate(2020, 5, 26);
        ss << std::setprecision(8) << sun.calcSunset();
        
        EXPECT_EQ(ss.str(), expected) << "Returned: " << ss.str();
    }
}
