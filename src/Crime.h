// src/Crime.h
#pragma once
#include <string>
#include <cstdio>

struct TimePoint {
    int hour = 0, minute = 0;
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
    std::string INCIDENT_NUMBER, OFFENSE_CODE, OFFENSE_CODE_GROUP,
                OFFENSE_DESCRIPTION, DISTRICT, REPORTING_AREA,
                SHOOTING, OCCURRED_ON_DATE, DAY_OF_WEEK,
                UCR_PART, STREET, Location;
    int YEAR = 0, MONTH = 0;
    double Lat = 0.0, Long = 0.0;
    TimePoint time;

    // ADD THIS METHOD
    int severity() const {
        try {
            return std::stoi(OFFENSE_CODE);
        } catch (...) {
            return 0;
        }
    }
};
