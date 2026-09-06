#include <Arduino.h>

#include "config.h"
#include "DHTSensor.h"
#include "SoilSensor.h"
#include "SoundSensor.h"
#include "GPS.h"
#include "CircularBuffer.h"
#include "DataProcessor.h"
#include "Telemetry.h"
#include "TelemetrySerializer.h"
#include "WiFiManager.h"
#include "MQTTClient.h"


// ================================
// Sensor Objects
// ================================

DHTSensor dhtSensor(DHT_PIN);
SoilSensor soilSensor(SOIL_PIN);
SoundSensor soundSensor(SOUND_PIN);
GPS gps(GPS_RX_PIN, GPS_TX_PIN);


// ================================
// Wi-Fi and MQTT
// ================================

WiFiManager wifi;
MQTTClient mqtt;


// ================================
// Circular Buffers
// ================================

float soilSamples[SOIL_BUFFER_SIZE];
float soundSamples[SOUND_BUFFER_SIZE];

CircularBuffer soilBuffer(
    soilSamples,
    SOIL_BUFFER_SIZE
);

CircularBuffer soundBuffer(
    soundSamples,
    SOUND_BUFFER_SIZE
);


// ================================
// Telemetry
// ================================

Telemetry data;


// ================================
// Timing
// ================================

unsigned long lastSensorRead = 0;


void setup()
{
    Serial.begin(115200);

    // ----------------------------
    // Sensors
    // ----------------------------

    dhtSensor.begin();
    soilSensor.begin();
    soundSensor.begin();


    // ----------------------------
    // Wi-Fi
    // ----------------------------

    Serial.println();
    Serial.println("================================");
    Serial.println("       NEXUS FIRMWARE");
    Serial.println("================================");

    wifi.begin();


    // ----------------------------
    // MQTT
    // ----------------------------

    mqtt.begin();

    if (mqtt.connect())
    {
        Serial.println("MQTT connection successful");
    }
    else
    {
        Serial.println("MQTT connection failed");
    }
}


void loop()
{
    // ============================
    // Continuously process GPS
    // ============================

    gps.update();


    // ============================
    // Keep MQTT connection alive
    // ============================

    if (mqtt.isConnected())
    {
        mqtt.loop();
    }
    else
    {
        Serial.println("MQTT disconnected");

        mqtt.connect();
    }


    // ============================
    // Sensor timing
    // ============================

    unsigned long currentTime = millis();

    if (currentTime - lastSensorRead >= SENSOR_INTERVAL_MS)
    {
        lastSensorRead = currentTime;


        // ============================
        // DHT11
        // ============================

        data.temperature_c =
            dhtSensor.readTemperature();

        data.humidity_percent =
            dhtSensor.readHumidity();


        // ============================
        // Soil Moisture
        // ============================

        int soilRaw =
            soilSensor.readRaw();

        soilBuffer.add(soilRaw);

        float soilAverageRaw =
            soilBuffer.average();

        data.soil_moisture =
            DataProcessor::normalizeSoil(
                soilAverageRaw
            );

        data.soil_score =
            DataProcessor::calculateSoilScore(
                data.soil_moisture
            );


        // ============================
        // Sound
        // ============================

        int soundRaw =
            soundSensor.readRaw();

        soundBuffer.add(soundRaw);

        float soundAverageRaw =
            soundBuffer.average();

        data.sound_activity =
            DataProcessor::normalizeSound(
                soundAverageRaw
            );

        data.sound_score =
            DataProcessor::calculateSoundScore(
                data.sound_activity
            );


        // ============================
        // GPS
        // ============================

        data.latitude =
            gps.getLatitude();

        data.longitude =
            gps.getLongitude();

        data.gps_source =
            gps.getSource();


        // ============================
        // Convert Telemetry → JSON
        // ============================

        String json =
            TelemetrySerializer::toJSON(data);


        // ============================
        // Serial Output
        // ============================

        Serial.println();
        Serial.println("----------- NEXUS -----------");

        Serial.print("Temperature: ");
        Serial.print(data.temperature_c);
        Serial.println(" C");

        Serial.print("Humidity: ");
        Serial.print(data.humidity_percent);
        Serial.println(" %");

        Serial.print("Soil Moisture: ");
        Serial.print(data.soil_moisture);
        Serial.println(" %");

        Serial.print("Soil Score: ");
        Serial.println(data.soil_score);

        Serial.print("Sound Activity: ");
        Serial.println(data.sound_activity);

        Serial.print("Sound Score: ");
        Serial.println(data.sound_score);

        Serial.print("Latitude: ");
        Serial.println(data.latitude, 6);

        Serial.print("Longitude: ");
        Serial.println(data.longitude, 6);

        Serial.print("GPS Source: ");
        Serial.println(data.gps_source);

        Serial.println("-----------------------------");

        Serial.println("JSON:");
        Serial.println(json);


        // ============================
        // MQTT Publish
        // ============================

        if (mqtt.isConnected())
        {
            mqtt.publish(json.c_str());

            Serial.println("MQTT: Telemetry published");
        }
        else
        {
            Serial.println(
                "MQTT: Not connected - telemetry not published"
            );
        }
    }
}