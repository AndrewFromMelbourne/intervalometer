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

