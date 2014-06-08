//-------------------------------------------------------------------------
//
// The MIT License (MIT)
//
// Copyright (c) 2014 Andrew Duncan
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

#ifndef INTERVALOMETER_ACTION_H
#define INTERVALOMETER_ACTION_H

//-------------------------------------------------------------------------

#include "IntervalAction.h"
#include "FocusShootDelayAction.h"
#include "LcdRowGraph.h"

//-------------------------------------------------------------------------

class IntervalTimerManagerInterface;
class LiquidCrystal;

//-------------------------------------------------------------------------

class IntervalometerAction
:
    public IntervalAction
{
public:

    enum Menu { INTERVAL, FOCUS_SHOOT_DELAY, NUMBER_OF_SHOTS, BACKLIGHT };
    enum CountdownStyle { TIME, GRAPH };

    IntervalometerAction(
        uint8_t id,
        uint32_t shotInterval,
        uint8_t focusPin,
        uint8_t shootPin,
        uint8_t backlightPin,
        IntervalTimerManagerInterface& itmi,
        LiquidCrystal& lcd);

    void begin();

    void startShooting();
    void stopShooting();

    void toggleCountdownStyle();

    void right();
    void up();
    void down();
    void left();
    void select();

    virtual void action();

private:

    static const uint32_t ActionsPerSec = 25;
    static const uint32_t ActionInterval = 40;
    static const uint32_t DefaultFSDelay = 500;

    void display();
    void formatShots(uint32_t number);

    void incrementBacklightValue();
    void decrementBacklightValue();

    static uint32_t intervals[9];

    static uint32_t incrementInterval(uint32_t interval);
    static uint32_t decrementInterval(uint32_t interval);

    uint32_t _numberOfShots;
    uint32_t _shotNumber;
    uint32_t _shotInterval;
    uint32_t _shotTimeCountDown;
    Menu _menu;
    CountdownStyle _countdownStyle;
    boolean _shooting;
    uint8_t _backlightPin;
    uint8_t _backlightValue;
    LiquidCrystal& _lcd;
    LcdRowGraph<LiquidCrystal> _lcdRowGraph;
    FocusShootDelayAction _focusShootDelayAction;
};

//-------------------------------------------------------------------------

typedef void (IntervalometerAction::*IntervalometerActionCallback)();

//-------------------------------------------------------------------------

#endif
