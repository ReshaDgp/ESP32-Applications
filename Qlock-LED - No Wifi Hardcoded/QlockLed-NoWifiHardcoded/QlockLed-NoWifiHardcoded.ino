#include <WiFiManager.h>
#include <time.h>

// NTP Server
const char* ntpServer = "pool.ntp.org";
const long  gmtOffset_sec = 3600;       // Berlin (CET: UTC+1)
const int   daylightOffset_sec = 3600;  // Additional 1 hour for CEST (UTC+2 in summer)

void setup() {
    Serial.begin(115200);
    
    WiFiManager wm;
    // wm.resetSettings();

    bool connectionResult;
    connectionResult = wm.autoConnect("ESP32 Configuration","abcd1234"); // password protected access point

    if(!connectionResult) {
        Serial.println("Failed to connect");
    } else { 
        Serial.println("Connected to Internet...");
        Serial.println(WiFi.localIP());
    }

    // Configure time using NTP
    configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
    Serial.println("Time synchronization complete!");
}

void loop() {
    struct tm timeinfo;
    if (!getLocalTime(&timeinfo)) {
        Serial.println("Failed to obtain time");
        return;
    }

    int hour = timeinfo.tm_hour;
    int minute = timeinfo.tm_min;

    // Convert hour to 12-hour format
    int displayHour = hour % 12;
    if (displayHour == 0) displayHour = 12; // 12-hour format fix

    String timeMessage = formatTime(displayHour, minute);
    Serial.println(timeMessage);

    delay(5000);  // Print every 5 second
}

String formatTime(int hour, int minute) {
    if (minute >= 0 && minute <= 3) {
        return "It is " + String(hour) + " O'Clock";
    } else if (minute >= 4 && minute <= 7) {
        return "It's 5 past " + String(hour);
    } else if (minute >= 8 && minute <= 13) {
        return "It's 10 past " + String(hour);
    } else if (minute >= 14 && minute <= 17) {
        return "It's a quarter past " + String(hour);
    } else if (minute >= 18 && minute <= 23) {
        return "It's 20 past " + String(hour);
    } else if (minute >= 24 && minute <= 27) {
        return "It's 25 past " + String(hour);
    } else if (minute >= 28 && minute <= 33) {
        return "It's Half past " + String(hour);
    } else if (minute >= 34 && minute <= 37) {
        return "It's 25 to " + String(hour + 1);
    } else if (minute >= 38 && minute <= 43) {
        return "It's 20 to " + String(hour + 1);
    } else if (minute >= 43 && minute <= 47) {
        return "It's a quarter to " + String(hour + 1);
    } else if (minute >= 48 && minute <= 53) {
        return "It's 10 to " + String(hour + 1);
    } else {
        return "It's 5 to " + String(hour + 1);
    }
}