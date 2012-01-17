#include "IntervalTimerManager.h"
#include "FocusShootDelayAction.h"

#include <Arduino.h>

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
