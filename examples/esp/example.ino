#include <ETH.h>
#include <WiFiSTA.h>
#include <WiFiGeneric.h>
#include <WiFiType.h>
#include <WiFiClient.h>
#include <WiFi.h>
#include <WiFiScan.h>
#include <WiFiAP.h>
#include <WiFiUdp.h>
#include <WiFiServer.h>
#include <WiFiMulti.h>

#include <TimeLib.h>
#include <sunset.h>

/**
 * This library only works for 32 bit platforms. It will not work for 8 bit AVR platforms
 */

/* I'm in the midwest, so this is what I use for my home */
#define LATITUDE        41.12345
#define LONGITUDE       -87.98765
#define DST_OFFSET      -5

const uint8_t _usDSTStart[22] = { 8,14,13,12,10, 9, 8,14,12,11,10, 9,14,13,12,11, 9};
const uint8_t _usDSTEnd[22]   = { 1, 7, 6, 5, 3, 2, 1, 7, 5, 4, 3, 2, 7, 6, 5, 4, 2};
static const char ntpServerName[] = "us.pool.ntp.org";
const int NTP_PACKET_SIZE = 48; // NTP time is in the first 48 bytes of message
byte packetBuffer[NTP_PACKET_SIZE]; //buffer to hold incoming & outgoing packets
const char ssid[] = "";  //  your network SSID (name)
const char pass[] = "";       // your network password

WiFiUDP Udp;
unsigned int localPort = 8888;  // local port to listen for UDP packets
SunSet sun;

time_t getNtpTime()
{
    IPAddress ntpServerIP; // NTP server's ip address

    while (Udp.parsePacket() > 0) ; // discard any previously received packets
    Serial.println("Transmit NTP Request");
    // get a random server from the pool
    WiFi.hostByName(ntpServerName, ntpServerIP);
    Serial.print(ntpServerName);
    Serial.print(": ");
    Serial.println(ntpServerIP);
    sendNTPpacket(ntpServerIP);
    uint32_t beginWait = millis();
    while (millis() - beginWait < 1500) {
        int size = Udp.parsePacket();
        if (size >= NTP_PACKET_SIZE) {
            Serial.println("Receive NTP Response");
            Udp.read(packetBuffer, NTP_PACKET_SIZE);  // read packet into the buffer
            unsigned long secsSince1900;
            // convert four bytes starting at location 40 to a long integer
            secsSince1900 =  (unsigned long)packetBuffer[40] << 24;
            secsSince1900 |= (unsigned long)packetBuffer[41] << 16;
            secsSince1900 |= (unsigned long)packetBuffer[42] << 8;
            secsSince1900 |= (unsigned long)packetBuffer[43];
            return secsSince1900 - 2208988800UL + (DST_OFFSET * SECS_PER_HOUR);
        }
  }
  Serial.println("No NTP Response :-(");
  return 0; // return 0 if unable to get the time
}

// send an NTP request to the time server at the given address
void sendNTPpacket(IPAddress &address)
{
    // set all bytes in the buffer to 0
    memset(packetBuffer, 0, NTP_PACKET_SIZE);
    // Initialize values needed to form NTP request
    // (see URL above for details on the packets)
    packetBuffer[0] = 0b11100011;   // LI, Version, Mode
    packetBuffer[1] = 0;     // Stratum, or type of clock
    packetBuffer[2] = 6;     // Polling Interval
    packetBuffer[3] = 0xEC;  // Peer Clock Precision
    // 8 bytes of zero for Root Delay & Root Dispersion
    packetBuffer[12] = 49;
    packetBuffer[13] = 0x4E;
    packetBuffer[14] = 49;
    packetBuffer[15] = 52;
    // all NTP fields have been given values, now
    // you can send a packet requesting a timestamp:
    Udp.beginPacket(address, 123); //NTP requests are to port 123
    Udp.write(packetBuffer, NTP_PACKET_SIZE);
    Udp.endPacket();
}

// utility function for digital clock display: prints leading 0
String twoDigits(int digits)
{
    if(digits < 10) {
        String i = '0'+String(digits);
        return i;
    }
    else {
        return String(digits);
    }
}

void setup()
{
    Serial.begin(115200);
    
    WiFi.begin(ssid, pass);
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }

    /* Get our time sync started */
    /* Set our position and a default timezone value */
    sun.setPosition(LATITUDE, LONGITUDE, DST_OFFSET);
    sun.setTZOffset(DST_OFFSET);
    setSyncProvider(getNtpTime);
    setSyncInterval(60*60);
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

    if (currentDay != day()) {
        sun.setCurrentDate(year(), month(), day());
        currentDay = day();
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
    customsunset = sun.calcCustomSunset(90.0);

    Serial.print("Sunrise at ");
    Serial.print(sunrise/60);
    Serial.print(":");
    Serial.print(twoDigits(sunrise%60));
    Serial.print("am, Sunset at ");
    Serial.print(sunset/60);
    Serial.print(":");
    Serial.print(twoDigits(sunset%60));
    Serial.println("pm");
    delay(1000);
}

