#pragma once

#ifndef CUSTOMTM1637_H_
#include <TM1637Display.h>

class CustomTM1637 : public TM1637Display
{
private:
    const uint8_t SEG_OP[4] = {SEG_G,
                               SEG_A | SEG_B | SEG_C | SEG_D | SEG_E | SEG_F,
                               SEG_A | SEG_B | SEG_E | SEG_F | SEG_G,
                               SEG_G};
    const uint8_t SEG_OV[4] = {SEG_G,
                               SEG_A | SEG_B | SEG_C | SEG_D | SEG_E | SEG_F,
                               SEG_B | SEG_C | SEG_D | SEG_E | SEG_F,
                               SEG_G};
    const uint8_t SEG_OC[4] = {SEG_G,
                               SEG_A | SEG_B | SEG_C | SEG_D | SEG_E | SEG_F,
                               SEG_A | SEG_D | SEG_E | SEG_F,
                               SEG_G};
    
    bool alert = true;

    const int animation_iterations_max = 10;

    int counter_alert_voltage = 0;
    int counter_alert_current = 0;
    int counter_alert_power = 0;

    bool next_alert_voltage = true;
    bool next_alert_current = true;
    bool next_alert_power = true;
public:
    CustomTM1637(int clk, int dio) : TM1637Display(clk, dio) {};

    // new methods
    void showFloat(float number);

    void showOverVoltage(float voltage);
    void showOverCurrent(float current);
    void showOverPower(float power);
};

#endif