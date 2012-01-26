//-------------------------------------------------------------------------
// Copyright (C) 2012 Andrew Duncan.
//
// This software may be distributed and modified under the terms of the GNU
// General Public License version 2 (GPL2) as published by the Free Software
// Foundation and appearing in the file GPL2.TXT included in the packaging
// of this file. Please note that GPL2 Section 2[b] requires that all works
// based on this software must also be made publicly available under the
// terms of the GPL2 ("Copyleft").
//
//-------------------------------------------------------------------------

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
