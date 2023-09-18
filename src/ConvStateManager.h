#pragma once
#include <Arduino.h>

#ifndef CONVSTATEMANAGER_H_

class ConvStateManager
{
private:
    float voltage_max = 32.0f;
    float current_max = 8.0f;
    float power_max = 80.0f;

    float over_voltage = 30.0f;
    float over_current = 0.003f;
    float over_power = 76.0f;

    float voltage_delta = 0.0015f;
    float current_delta = 0.0015f;

public:
    // constructors
    ConvStateManager();

    // setters
    void setVoltageMax(float voltage_max);
    void setCurrentMax(float current_max);
    void setPowerMax(float power_max);

    void setOverVoltage(float over_voltage);
    void setOverCurrent(float over_current);
    void setOverPower(float over_power);

    void setVoltageDelta(float voltage_delta);
    void setCurrentDelta(float current_delta);

    // methods
    bool isOverVoltage(float voltage);
    bool isOverCurrent(float current);
    bool isOverPower(float power);

    bool isOverMaxVoltage(float voltage);
    bool isOverMaxCurrent(float current);
    bool isOverMaxPower(float power);
    
    bool isVoltageChangeGreaterThanDelta(float old_voltage, float new_voltage);
    bool isCurrentChangeGreaterThanDelta(float old_current, float old_voltage);
};

#endif