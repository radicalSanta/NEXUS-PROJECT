#ifndef TELEMETRY_H
#define TELEMETRY_H

struct Telemetry
{
    // DHT11
    float temperature_c;
    float humidity_percent;

    // Soil
    float soil_moisture;
    float soil_score;

    // Sound
    float sound_activity;
    float sound_score;

    // GPS
    float latitude;
    float longitude;
    const char* gps_source;
};

#endif