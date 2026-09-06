#include "DataProcessor.h"
#include "config.h"
#include <Arduino.h>

float DataProcessor::normalizeSoil(float rawValue)
{
    float moisture =
        ((SOIL_DRY_RAW - rawValue) /
        (float)(SOIL_DRY_RAW - SOIL_WET_RAW)) * 100.0;

    moisture = constrain(moisture, 0.0, 100.0);

    return moisture;
}


float DataProcessor::calculateSoilScore(float moisture)
{
    float deviation = abs(moisture - 50.0);

    float score = 100.0 - (deviation * 2.0);

    score = constrain(score, 0.0, 100.0);

    return score;
}


float DataProcessor::normalizeSound(float rawValue)
{
    float activity =
        ((rawValue - SOUND_MIN_RAW) /
        (float)(SOUND_MAX_RAW - SOUND_MIN_RAW)) * 100.0;

    activity = constrain(activity, 0.0, 100.0);

    return activity;
}


float DataProcessor::calculateSoundScore(float soundActivity)
{
    float score = 100.0 - soundActivity;

    score = constrain(score, 0.0, 100.0);

    return score;
}