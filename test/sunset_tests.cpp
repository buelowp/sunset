#include <gtest/gtest.h>
#include <ctime>
#include <string>
#include <sstream>

#include "SunSet.h"

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

    TEST(SunsetTesting, ValidReturnValueSunriseLocal)
    {
        SunSet sun;
        std::string expected("437.817");
        std::stringstream ss(std::stringstream::in | std::stringstream::out);
        
        sun.setPosition(LATITUDE_AH, LONGITUDE_AH, TIMEZONE_AH);
        sun.setCurrentDate(2020, 1, 15);
        ss << std::setprecision(6) << sun.calcSunriseLocal();
        
        EXPECT_EQ(ss.str(), expected) << "Returned: " << ss.str();
    }
    
    TEST(SunsetTesting, ValidReturnValueSunsetLocal)
    {
        SunSet sun;

        std::string expected("1005.0013");
        std::stringstream ss(std::stringstream::in | std::stringstream::out);
        
        sun.setPosition(LATITUDE_AH, LONGITUDE_AH, TIMEZONE_AH);
        sun.setCurrentDate(2020, 1, 15);
        ss << std::setprecision(8) << sun.calcSunsetLocal();
        
        EXPECT_EQ(ss.str(), expected) << "Returned: " << ss.str();
    }

    TEST(SunsetTesting, ValidReturnValueSunriseUTC)
    {
        SunSet sun;
        std::string expected("797.817");
        std::stringstream ss(std::stringstream::in | std::stringstream::out);
        
        sun.setPosition(LATITUDE_AH, LONGITUDE_AH, TIMEZONE_AH);
        sun.setCurrentDate(2020, 1, 15);
        ss << std::setprecision(6) << sun.calcSunriseUTC();
        
        EXPECT_EQ(ss.str(), expected) << "Returned: " << ss.str();
    }
    
    TEST(SunsetTesting, ValidReturnValueSunsetUTC)
    {
        SunSet sun;
        std::string expected("1365.0013");
        std::stringstream ss(std::stringstream::in | std::stringstream::out);
        
        sun.setPosition(LATITUDE_AH, LONGITUDE_AH, TIMEZONE_AH);
        sun.setCurrentDate(2020, 1, 15);
        ss << std::setprecision(8) << sun.calcSunsetUTC();
        
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
        ss << std::setprecision(6) << sun.calcAstronomicalSunriseLocal();
        
        EXPECT_EQ(ss.str(), expected) << "Returned: " << ss.str();
    }
    
    TEST(SunsetTesting, ValidAstronomicalSunsetArlingtonHeights)
    {
        SunSet sun;
        std::string expected("1280.07");
        std::stringstream ss(std::stringstream::in | std::stringstream::out);
        
        sun.setPosition(LATITUDE_AH, LONGITUDE_AH, TIMEZONE_AH);
        sun.setCurrentDate(2020, 5, 25);
        ss << std::setprecision(6) << sun.calcAstronomicalSunsetLocal();
        
        EXPECT_EQ(ss.str(), expected) << "Returned: " << ss.str();
    }

    TEST(SunsetTesting, ValidNauticalSunriseArlingtonHeights)
    {
        SunSet sun;
        std::string expected("187.513");
        std::stringstream ss(std::stringstream::in | std::stringstream::out);
        
        sun.setPosition(LATITUDE_AH, LONGITUDE_AH, TIMEZONE_AH);
        sun.setCurrentDate(2020, 5, 25);
        ss << std::setprecision(6) << sun.calcNauticalSunriseLocal();
        
        EXPECT_EQ(ss.str(), expected) << "Returned: " << ss.str();
    }
    
    TEST(SunsetTesting, ValidNauticalSunsetArlingtonHeights)
    {
        SunSet sun;
        std::string expected("1231.17");
        std::stringstream ss(std::stringstream::in | std::stringstream::out);
        
         sun.setPosition(LATITUDE_AH, LONGITUDE_AH, TIMEZONE_AH);
        sun.setCurrentDate(2020, 5, 25);
        ss << std::setprecision(6) << sun.calcNauticalSunsetLocal();
        
        EXPECT_EQ(ss.str(), expected) << "Returned: " << ss.str();
    }

    TEST(SunsetTesting, ValidCivilSunriseArlingtonHeights)
    {
        SunSet sun;
        std::string expected("229.355");
        std::stringstream ss(std::stringstream::in | std::stringstream::out);
        
        sun.setPosition(LATITUDE_AH, LONGITUDE_AH, TIMEZONE_AH);
        sun.setCurrentDate(2020, 5, 25);
        ss << std::setprecision(6) << sun.calcCivilSunriseLocal();
        
        EXPECT_EQ(ss.str(), expected) << "Returned: " << ss.str();
    }
    
    TEST(SunsetTesting, ValidCivilSunsetArlingtonHeights)
    {
        SunSet sun;
        std::string expected("1189.15");
        std::stringstream ss(std::stringstream::in | std::stringstream::out);
        
        sun.setPosition(LATITUDE_AH, LONGITUDE_AH, TIMEZONE_AH);
        sun.setCurrentDate(2020, 5, 25);
        ss << std::setprecision(6) << sun.calcCivilSunsetLocal();
        
        EXPECT_EQ(ss.str(), expected) << "Returned: " << ss.str();
    }

}
