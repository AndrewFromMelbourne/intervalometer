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

#include "IntervalometerAction.h"
#include "IntervalometerButton.h"

#include <Arduino.h>


//-------------------------------------------------------------------------

void
IntervalometerButton:: pressed()
{
    (_intervalometerAction.*_intervalometerActionCallback)();
}

//-------------------------------------------------------------------------

void
IntervalometerButton:: repeated()
{
    if (getId() != SELECT)
    {
        pressed();
    }
}

//-------------------------------------------------------------------------
