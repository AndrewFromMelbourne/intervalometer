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
