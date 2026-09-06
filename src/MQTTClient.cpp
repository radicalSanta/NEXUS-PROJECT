#include "MQTTClient.h"
#include "config.h"
#include <Arduino.h>

MQTTClient::MQTTClient()
    : mqtt(wifiClient)
{
}

void MQTTClient::begin()
{
    mqtt.setServer(MQTT_BROKER, MQTT_PORT);
}

bool MQTTClient::connect()
{
    Serial.print("Connecting to MQTT...");

    if (mqtt.connect("NEXUS-ESP32"))
    {
        Serial.println("connected");
        return true;
    }

    Serial.print("failed, state = ");
    Serial.println(mqtt.state());

    return false;
}

bool MQTTClient::isConnected()
{
    return mqtt.connected();
}

void MQTTClient::publish(const char* message)
{
    mqtt.publish(MQTT_TOPIC, message);
}

void MQTTClient::loop()
{
    mqtt.loop();
}