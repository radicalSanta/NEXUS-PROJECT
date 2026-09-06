#include "TelemetrySerializer.h"
#include <ArduinoJson.h>

String TelemetrySerializer::toJSON(const Telemetry& data)
{
    JsonDocument doc;

    doc["temperature_c"] = data.temperature_c;
    doc["humidity_percent"] = data.humidity_percent;

    doc["soil_moisture"] = data.soil_moisture;
    doc["soil_score"] = data.soil_score;

    doc["sound_activity"] = data.sound_activity;
    doc["sound_score"] = data.sound_score;

    doc["latitude"] = data.latitude;
    doc["longitude"] = data.longitude;
    doc["gps_source"] = data.gps_source;

    String output;

    serializeJson(doc, output);

    return output;
}