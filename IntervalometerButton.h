#ifndef INTERVALOMETER_BUTTON_H
#define INTERVALOMETER_BUTTON_H

#include "AnalogButton.h"
#include "IntervalometerAction.h"

//-------------------------------------------------------------------------

class AnalogButtonManagerInterface;

//-------------------------------------------------------------------------

class IntervalometerButton
:
    public AnalogButton
{
public:

    enum Buttons { RIGHT, UP, DOWN, LEFT, SELECT };

    IntervalometerButton(
        int id,
        int low,
        int high,
        AnalogButtonManagerInterface& abmi,
        IntervalometerAction& intervalometerAction,
        IntervalometerActionCallback intervalometerActionCallback)
    :
        AnalogButton(id, low, high, abmi),
        _intervalometerAction(intervalometerAction),
        _intervalometerActionCallback(intervalometerActionCallback)
    {
    }

    virtual void pressed();
    virtual void repeated();

private:

    IntervalometerAction& _intervalometerAction;
    IntervalometerActionCallback _intervalometerActionCallback;
};

//-------------------------------------------------------------------------

#endif
