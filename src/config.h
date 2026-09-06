#ifndef CONFIG_H
#define CONFIG_H

// ============================
// SENSOR PINS
// ============================

#define DHT_PIN 4
#define SOIL_PIN 34
#define SOUND_PIN 35

// ============================
// GPS PINS
// ============================

#define GPS_RX_PIN 16
#define GPS_TX_PIN 17

// ============================
// Wi-Fi
// ============================

#define WIFI_SSID "moto g54 5g"
#define WIFI_PASSWORD "SAMRIDH123"

// ============================
// MQTT
// ============================

#define MQTT_BROKER "10.36.232.114"
#define MQTT_PORT 1883
#define MQTT_TOPIC "nexus/telemetry"

// ============================
// SENSOR TIMING
// ============================

#define SENSOR_INTERVAL_MS 2000

// ============================
// CIRCULAR BUFFER
// ============================

#define SOIL_BUFFER_SIZE 10
#define SOUND_BUFFER_SIZE 10

// ============================
// SOIL CALIBRATION
// ============================

// Raw ADC value when soil is dry
#define SOIL_DRY_RAW 4095

// Raw ADC value when soil is wet
#define SOIL_WET_RAW 1500

// ============================
// SOUND CALIBRATION
// ============================

// Raw ADC range used for sound activity
#define SOUND_MIN_RAW 0
#define SOUND_MAX_RAW 4095

#define SOUND_SAMPLE_COUNT 100
#define SOUND_SAMPLE_INTERVAL_US 1000

// ============================
// GPS FALLBACK
// ============================

// Used only when the GPS has no valid fix
#define FALLBACK_LATITUDE 25.5788
#define FALLBACK_LONGITUDE 91.8933

#endif