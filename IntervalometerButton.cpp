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
