#ifndef AnalogInput_h
#define AnalogInput_h

#include "Arduino.h"

class AnalogInput {
    public:
        AnalogInput(int pin);
        void setupAutoCalibrate(bool enable);
        void setupAutoConstrain(bool enable, int min, int max);
        int read();
    private:
        int _pin;
        bool _autoCalibrate;
        bool _autoConstrain;
        int _min;
        int _max;
        int _constrainMin;
        int _constrainMax;
};

#endif