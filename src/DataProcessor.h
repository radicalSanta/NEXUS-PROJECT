#ifndef DATA_PROCESSOR_H
#define DATA_PROCESSOR_H

class DataProcessor
{
public:
    static float normalizeSoil(float rawValue);

    static float calculateSoilScore(float moisture);

    static float normalizeSound(float rawValue);

    static float calculateSoundScore(float soundActivity);
};

#endif