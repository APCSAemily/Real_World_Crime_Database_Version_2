// src/Crime.h
// src/Crime.h
#pragma once
#include <string>

struct TimePoint {
    int hour = 0;
    int minute = 0;
    bool operator<(const TimePoint& o) const {
        return hour != o.hour ? hour < o.hour : minute < o.minute;
    }
    std::string str() const {
        char buf[6];
        std::snprintf(buf, sizeof(buf), "%02d:%02d", hour, minute);
        return buf;
    }
};

struct Crime {
    std::string INCIDENT_NUMBER;
    std::string OFFENSE_CODE;
    std::string OFFENSE_CODE_GROUP;
    std::string OFFENSE_DESCRIPTION;
    std::string DISTRICT;
    std::string REPORTING_AREA;
    std::string SHOOTING;
    std::string OCCURRED_ON_DATE;
    int YEAR = 0;
    int MONTH = 0;
    std::string DAY_OF_WEEK;
    TimePoint time;
    std::string UCR_PART;
    std::string STREET;
    double Lat = 0.0;
    double Long = 0.0;
    std::string Location;
};
