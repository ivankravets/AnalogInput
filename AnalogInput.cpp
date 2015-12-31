#include "Arduino.h"
#include "AnalogInput.h"

#define INPUT_MIN 0
#define INPUT_MAX 1023

AnalogInput::AnalogInput(int pin) {
    _pin = pin;
    _autoCalibrate = false;
    _autoConstrain = false;
    pinMode(_pin, INPUT);
}

void AnalogInput::setupAutoCalibrate(bool enable) {
    _autoCalibrate = enable;
    if(enable) {
        _min = INPUT_MAX;
        _max = INPUT_MIN;
    }
}

void AnalogInput::setupAutoConstrain(bool enable, int min, int max) {
    _constrainMin = min;
    _constrainMax = max;
    _autoConstrain = enable;
}

int AnalogInput::read() {
    int rawValue = analogRead(_pin);
    int outputValue = rawValue;
    
    if(_autoCalibrate) {
        if(rawValue < _min) {
            _min = rawValue;
        }
        if(rawValue > _max) {
            _max = rawValue;
        }
        
        if(_autoConstrain) {
            outputValue = map(outputValue, _min, _max, _constrainMin, _constrainMax);
        } else {
            outputValue = map(outputValue, _min, _max, INPUT_MIN, INPUT_MAX);
        }
    }
    
    if(_autoConstrain) {
        outputValue = constrain(outputValue, _constrainMin, _constrainMax);
    }
    
    return outputValue;
}