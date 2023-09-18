
#include <Wire.h>
#include <INA226.h>
#include "ConvStateManager.h"
#include "CustomTM1637.h"

#define CLK 2
#define PWR_OFF 4
#define DIO_V 5
#define DIO_I 6
#define DIO_P 7
#define DIS_BRIGHTNESS 1

INA226 ina(Wire);

CustomTM1637 display_v(CLK, DIO_V);
CustomTM1637 display_i(CLK, DIO_I);
CustomTM1637 display_p(CLK, DIO_P);

void setup() 
{
  digitalWrite(PWR_OFF, LOW);

  display_v.setBrightness(DIS_BRIGHTNESS);
  display_i.setBrightness(DIS_BRIGHTNESS);
  display_p.setBrightness(DIS_BRIGHTNESS);

  Serial.begin(9600);

  Wire.begin();

  bool success = ina.begin();

  // Check if the connection was successful, stop if not
  if(!success)
  {
    Serial.println("Connection error");
    while(1);
  }

  // Configure INA226
  ina.configure(INA226_AVERAGES_128, INA226_BUS_CONV_TIME_1100US, INA226_SHUNT_CONV_TIME_1100US, INA226_MODE_SHUNT_BUS_CONT);

  // Calibrate INA226. Rshunt = 0.002 ohm, Max excepted current = 10A
  ina.calibrate(0.002, 10);
}

float readSensorVoltage(float offset = 0) {
  float voltage = ina.readBusVoltage();
  if (voltage < 0.0f) {
    return 0.0f;
  }
  return ina.readBusVoltage() + offset;
}

float readSensorCurrent(float offset = 0) {
  float current = ina.readShuntCurrent();
  if (current < 0.0f) {
    return 0.0f;
  }
  return ina.readShuntCurrent() + offset;
}


void loop() {

  ConvStateManager pcm;

  float old_voltage = 0.000f;
  float old_current = 0.000f;
  
  while(true) {
    float new_voltage = readSensorVoltage();
    float new_current = readSensorCurrent(-0.01f);

    old_voltage = pcm.isVoltageChangeGreaterThanDelta(old_voltage, new_voltage) ? new_voltage : old_voltage;
    old_current = pcm.isCurrentChangeGreaterThanDelta(old_current, new_current) ? new_current : old_current;
    float new_power = new_voltage * new_current;
    
    if (pcm.isOverVoltage(new_voltage)) {
      display_v.showOverVoltage(new_voltage);
    }
    else {
      display_v.showFloat(new_voltage);
    }
    
    if (pcm.isOverCurrent(new_current)) {
      display_i.showOverCurrent(new_current);
    }
    else {
      display_i.showFloat(new_current);
    }

    if (pcm.isOverPower(new_power)) {
      display_p.showOverPower(new_power);
    }
    else {
      display_p.showFloat(new_power);
    }
  }
  
}

