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
    intervalTimerManager,
    lcd);

IntervalometerButton b1(
    IntervalometerButton::RIGHT,
    0,                        // low analog value
    20,                        // high analog value
    analogButtonManager,
    intervalometerAction,
    &IntervalometerAction::right);

IntervalometerButton b2(
    IntervalometerButton::UP,
    135,                        // low analog value
    155,                        // high analog value
    analogButtonManager,
    intervalometerAction,
    &IntervalometerAction::up);

IntervalometerButton b3(
    IntervalometerButton::DOWN,
    319,                        // low analog value
    339,                        // high analog value
    analogButtonManager,
    intervalometerAction,
    &IntervalometerAction::down);

IntervalometerButton b4(
    IntervalometerButton::LEFT,
    495,                        // low analog value
    515,                        // high analog value
    analogButtonManager,
    intervalometerAction,
    &IntervalometerAction::left);

IntervalometerButton b5(
    IntervalometerButton::SELECT,
    731,                        // low analog value
    751,                        // high analog value
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

