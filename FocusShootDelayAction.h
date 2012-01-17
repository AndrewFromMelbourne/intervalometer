#ifndef FOCUS_SHOOT_DELAY_ACTION_H
#define FOCUS_SHOOT_DELAY_ACTION_H

//-------------------------------------------------------------------------

#include "IntervalAction.h"

//-------------------------------------------------------------------------

class IntervalTimerManagerInterface;

//-------------------------------------------------------------------------

class FocusShootDelayAction
:
    public IntervalAction
{
public:

    FocusShootDelayAction(
        uint8_t id,
        uint32_t focusShootDelay,
        uint8_t focusPin,
        uint8_t shootPin,
        IntervalTimerManagerInterface& itmi);

    void focusAndShoot();

    virtual void action();

private:

    void press();
    void release();

    uint8_t _focusPin;
    uint8_t _shootPin;
};

//-------------------------------------------------------------------------

#endif
