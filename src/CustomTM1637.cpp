#include "CustomTM1637.h"

// new methods
void CustomTM1637::showFloat(float number) {
    int whole = (int)number;
    int multiplier = 1000;
    int whole_digit_num = 1;

    while (whole / 10 > 0) {
        whole /= 10;
        multiplier /= 10;
        whole_digit_num++;
    }

    uint8_t point_loc_bin = 1 << (8 - whole_digit_num);

    this->showNumberDecEx(number * multiplier, point_loc_bin, true);
}

void CustomTM1637::showOverVoltage(float voltage) {
    if (!alert) {
        this->showFloat(voltage);
        return;
    }

    if (counter_alert_voltage == animation_iterations_max) {
        next_alert_voltage = !next_alert_voltage;
        counter_alert_voltage = 0;
    }
    counter_alert_voltage++;

    if (next_alert_voltage) {
        this->setSegments(SEG_OV);
        return;
    }

    this->showFloat(voltage);
}

void CustomTM1637::showOverCurrent(float current) {
    if (!alert) {
        this->showFloat(current);
        return;
    }

    if (counter_alert_current == animation_iterations_max) {
        next_alert_current = !next_alert_current;
        counter_alert_current = 0;
    }
    counter_alert_current++;

    if (next_alert_current) {
        this->setSegments(SEG_OC);
        return;
    }

    this->showFloat(current);
}

void CustomTM1637::showOverPower(float power) {
    if (!alert) {
        this->showFloat(power);
        return;
    }

    if (counter_alert_power == animation_iterations_max) {
        next_alert_power = !next_alert_power;
        counter_alert_power = 0;
    }
    counter_alert_power++;

    if (next_alert_power) {
        this->setSegments(SEG_OP);
        return;
    }

    this->showFloat(power);
    
    
}