#include <gtest/gtest.h>
#include <ctime>
#include <string>
#include <sstream>

#include "SunSet.h"

namespace
{
    TEST(SunsetTesting, ValidReturnValueSunrise)
    {
        SunSet sun;
        time_t t = time(0);
        int DST_OFFSET = -6;
        double LATITUDE = 42.058102;
        double LONGITUDE = -87.984189;
        struct tm * now = localtime(&t);
        std::string expected("437.817");
        std::stringstream ss(std::stringstream::in | std::stringstream::out);
        
        sun.setPosition(LATITUDE, LONGITUDE, DST_OFFSET);
        sun.setCurrentDate(2020, 1, 15);
        ss << std::setprecision(6) << sun.calcSunrise();
        
        EXPECT_EQ(ss.str(), expected) << "Returned: " << ss.str();
    }
    
    TEST(SunsetTesting, ValidReturnValueSunset)
    {
        SunSet sun;
        time_t t = time(0);
        int DST_OFFSET = -6;
        double LATITUDE = 42.058102;
        double LONGITUDE = -87.984189;
        struct tm * now = localtime(&t);
        std::string expected("1005.0013");
        std::stringstream ss(std::stringstream::in | std::stringstream::out);
        
        sun.setPosition(LATITUDE, LONGITUDE, DST_OFFSET);
        sun.setCurrentDate(2020, 1, 15);
       ss << std::setprecision(8) << sun.calcSunset();
        
        EXPECT_EQ(ss.str(), expected) << "Returned: " << ss.str();
    }

    TEST(SunsetTesting, ValidReturnValueSunriseUTC)
    {
        SunSet sun;
        time_t t = time(0);
        int DST_OFFSET = -6;
        double LATITUDE = 42.058102;
        double LONGITUDE = -87.984189;
        struct tm * now = localtime(&t);
        std::string expected("797.817");
        std::stringstream ss(std::stringstream::in | std::stringstream::out);
        
        sun.setPosition(LATITUDE, LONGITUDE, DST_OFFSET);
        sun.setCurrentDate(2020, 1, 15);
        ss << std::setprecision(6) << sun.calcSunriseUTC();
        
        EXPECT_EQ(ss.str(), expected) << "Returned: " << ss.str();
    }
    
    TEST(SunsetTesting, ValidReturnValueSunsetUTC)
    {
        SunSet sun;
        time_t t = time(0);
        int DST_OFFSET = -6;
        double LATITUDE = 42.058102;
        double LONGITUDE = -87.984189;
        struct tm * now = localtime(&t);
        std::string expected("1365.0013");
        std::stringstream ss(std::stringstream::in | std::stringstream::out);
        
        sun.setPosition(LATITUDE, LONGITUDE, DST_OFFSET);
        sun.setCurrentDate(2020, 1, 15);
        ss << std::setprecision(8) << sun.calcSunsetUTC();
        
        EXPECT_EQ(ss.str(), expected) << "Returned: " << ss.str();
    }
    
    TEST(SunsetTesting, MoonPhaseToday)
    {
        SunSet sun;
        time_t t = time(0);
        int DST_OFFSET = -6;
        double LATITUDE = 42.058102;
        double LONGITUDE = -87.984189;
        struct tm * now = localtime(&t);
        
        sun.setPosition(LATITUDE, LONGITUDE, DST_OFFSET);
        sun.setCurrentDate(2020, 1, 15);
        
        EXPECT_EQ(sun.moonPhase(1579097467), 20) << "Returned: " << sun.moonPhase() << ", epoch is " << 1579097467;
    }

}
