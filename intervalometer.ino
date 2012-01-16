#include "AnalogButtonManager.h"
#include "IntervalTimerManager.h"
#include "IntervalometerAction.h"
#include "IntervalometerButton.h"
#include "LcdColumnGraph.h"

#include <LiquidCrystal.h>

//-------------------------------------------------------------------------

LiquidCrystal lcd(8, 9, 4, 5, 6, 7);
AnalogButtonManager<5> analogButtonManager(A0, 30);
IntervalTimerManager<1> intervalTimerManager;

IntervalometerAction intervalometerAction(
    0,
    1,
    2,
    3,
    intervalTimerManager,
    lcd);

IntervalometerButton b1(
    IntervalometerButton::RIGHT,
    0,
    20,
    analogButtonManager,
    intervalometerAction,
    &IntervalometerAction::right);

IntervalometerButton b2(
    IntervalometerButton::UP,
    135,
    155,
    analogButtonManager,
    intervalometerAction,
    &IntervalometerAction::up);

IntervalometerButton b3(
    IntervalometerButton::DOWN,
    319,
    339,
    analogButtonManager,
    intervalometerAction,
    &IntervalometerAction::down);

IntervalometerButton b4(
    IntervalometerButton::LEFT,
    495,
    515,
    analogButtonManager,
    intervalometerAction,
    &IntervalometerAction::left);

IntervalometerButton b5(
    IntervalometerButton::SELECT,
    731,
    751,
    analogButtonManager,
    intervalometerAction,
    &IntervalometerAction::select);

//-------------------------------------------------------------------------

void setup()
{
	pinMode(13, OUTPUT);
    lcd.begin(16, 2);
	intervalometerAction.begin();
}

//-------------------------------------------------------------------------

void loop()
{
    analogButtonManager.task();
    intervalTimerManager.task();
}

