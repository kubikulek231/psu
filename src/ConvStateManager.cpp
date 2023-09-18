#include "ConvStateManager.h"
#include <Arduino.h>

ConvStateManager::ConvStateManager(){}

void ConvStateManager::setVoltageMax(float voltage_max) {
    this->voltage_max = voltage_max;
}

void ConvStateManager::setCurrentMax(float current_max) {
    this->current_max = current_max;

}

void ConvStateManager::setPowerMax(float power_max) {
    this->power_max = power_max;
}

void ConvStateManager::setOverVoltage(float over_voltage) {
    this->over_voltage = over_voltage;
}

void ConvStateManager::setOverCurrent(float over_current) {
    this->over_current = over_current;
}

void ConvStateManager::setOverPower(float over_power) {
    this->over_power = over_power;
}

void ConvStateManager::setVoltageDelta(float voltage_delta) {
    this->voltage_delta = voltage_delta;
}

void ConvStateManager::setCurrentDelta(float current_delta) {
    this->current_delta = current_delta;
}

bool ConvStateManager::isOverCurrent(float current) {
    return current > over_current;
}

bool ConvStateManager::isOverVoltage(float voltage) {
    return voltage > over_voltage;
}

bool ConvStateManager::isOverPower(float power) {
    return power > over_power;
}

bool ConvStateManager::isOverMaxCurrent(float current) {
    return current > current_max;
}

bool ConvStateManager::isOverMaxVoltage(float voltage) {
    return voltage > voltage_max;
}

bool ConvStateManager::isOverMaxPower(float power) {
    return power > power_max;
}

bool ConvStateManager::isVoltageChangeGreaterThanDelta(float old_voltage, float new_voltage) {
    return abs(new_voltage - old_voltage) > voltage_delta;
}

bool ConvStateManager::isCurrentChangeGreaterThanDelta(float old_current, float new_current) {
    return abs(new_current - old_current) > current_delta;
}