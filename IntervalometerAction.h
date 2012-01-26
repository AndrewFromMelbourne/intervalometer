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

    static const uint8_t ActionsPerSec = 25;
    static const uint8_t ActionInterval = 40;
    static const uint8_t DefaultFSDelay = 500;

    void display();
    void formatShots(uint32_t number);

    void incrementBacklightValue();
    void decrementBacklightValue();

    static uint16_t intervals[9];

    static uint16_t incrementInterval(uint16_t interval);
    static uint16_t decrementInterval(uint16_t interval);

    uint32_t _numberOfShots;
    uint32_t _shotNumber;
    uint16_t _shotInterval;
    uint16_t _shotTimeCountDown;
    Menu _menu;
    CountdownStyle _countdownStyle;
    boolean _shooting;
    uint8_t _backlightPin;
    uint8_t _backlightValue;
    LiquidCrystal& _lcd;
    LcdRowGraph _lcdRowGraph;
    FocusShootDelayAction _focusShootDelayAction;
};

//-------------------------------------------------------------------------

typedef void (IntervalometerAction::*IntervalometerActionCallback)();

//-------------------------------------------------------------------------

#endif
