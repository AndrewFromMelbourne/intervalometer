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

#include "IntervalTimerManager.h"
#include "FocusShootDelayAction.h"

#include <Arduino.h>

//-------------------------------------------------------------------------

FocusShootDelayAction:: FocusShootDelayAction(
    uint8_t id,
    uint32_t focusShootDelay,
    uint8_t focusPin,
    uint8_t shootPin,
    IntervalTimerManagerInterface& itmi)
:
    IntervalAction(id, focusShootDelay, itmi),
    _focusPin(focusPin),
    _shootPin(shootPin)
{
    pinMode(13, OUTPUT);
    //pinMode(_focusPin, OUTPUT);
    //pinMode(_shootPin, OUTPUT);
}

//-------------------------------------------------------------------------

void
FocusShootDelayAction:: focusAndShoot()
{
    press();

    if (getInterval() > 0)
    {
        activate();
    }
    else
    {
        release();
    }
}

//-------------------------------------------------------------------------

void
FocusShootDelayAction:: press()
{
    digitalWrite(13, HIGH);

    // FIXME focus
    //digitalWrite(_focusPin, HIGH);
    //digitalWrite(_shootPin, HIGH);

}

//-------------------------------------------------------------------------

void
FocusShootDelayAction:: release()
{
    digitalWrite(13, LOW);

    // FIXME shoot
    //digitalWrite(_shootPin, LOW);
    //digitalWrite(_focusPin, LOW);
}

//-------------------------------------------------------------------------

void
FocusShootDelayAction:: action()
{
    release();
    deactivate();
}

//-------------------------------------------------------------------------
