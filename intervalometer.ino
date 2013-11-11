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

#include "AnalogButtonManager.h"
#include "IntervalTimerManager.h"
#include "IntervalometerAction.h"
#include "IntervalometerButton.h"

#include <LiquidCrystal.h>
#include <LcdRowGraph.h>

//-------------------------------------------------------------------------

LiquidCrystal lcd(8, 9, 4, 5, 6, 7);
AnalogButtonManager<5> analogButtonManager(A0);
IntervalTimerManager<2> intervalTimerManager;

IntervalometerAction intervalometerAction(
    0,                        // id
    1,                        // default shot interval (seconds)
    2,                        // focus pin
    3,                        // shoot pin
    10,                       // backlight pin
    intervalTimerManager,
    lcd);

IntervalometerButton b1(
    IntervalometerButton::RIGHT,
    0,                        // low analog value
    20,                       // high analog value
    analogButtonManager,
    intervalometerAction,
    &IntervalometerAction::right);

IntervalometerButton b2(
    IntervalometerButton::UP,
    135,                      // low analog value
    155,                      // high analog value
    analogButtonManager,
    intervalometerAction,
    &IntervalometerAction::up);

IntervalometerButton b3(
    IntervalometerButton::DOWN,
    319,                      // low analog value
    339,                      // high analog value
    analogButtonManager,
    intervalometerAction,
    &IntervalometerAction::down);

IntervalometerButton b4(
    IntervalometerButton::LEFT,
    495,                      // low analog value
    515,                      // high analog value
    analogButtonManager,
    intervalometerAction,
    &IntervalometerAction::left);

IntervalometerButton b5(
    IntervalometerButton::SELECT,
    731,                      // low analog value
    751,                      // high analog value
    analogButtonManager,
    intervalometerAction,
    &IntervalometerAction::select);

//-------------------------------------------------------------------------

void setup()
{
    lcd.begin(16, 2);
    intervalometerAction.begin();
}

//-------------------------------------------------------------------------

void loop()
{
    analogButtonManager.task();
    intervalTimerManager.task();
}

