//-------------------------------------------------------------------------
//
// The MIT License (MIT)
//
// Copyright (c) 2013 Andrew Duncan
//
// Permission is hereby granted, free of charge, to any person obtaining a
// copy of this software and associated documentation files (the
// "Software"), to deal in the Software without restriction, including
// without limitation the rights to use, copy, modify, merge, publish,
// distribute, sublicense, and/or sell copies of the Software, and to
// permit persons to whom the Software is furnished to do so, subject to
// the following conditions:
//
// The above copyright notice and this permission notice shall be included
// in all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
// OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
// MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
// IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
// CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
// TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
// SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
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
    pinMode(_focusPin, OUTPUT);
    pinMode(_shootPin, OUTPUT);
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
    digitalWrite(_focusPin, HIGH);
    digitalWrite(_shootPin, HIGH);

}

//-------------------------------------------------------------------------

void
FocusShootDelayAction:: release()
{
    digitalWrite(_shootPin, LOW);
    digitalWrite(_focusPin, LOW);
}

//-------------------------------------------------------------------------

void
FocusShootDelayAction:: action()
{
    release();
    deactivate();
}

//-------------------------------------------------------------------------
