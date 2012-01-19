#include "IntervalTimerManager.h"
#include "IntervalometerAction.h"

#include <Arduino.h>
#include <LiquidCrystal.h>

IntervalometerAction:: IntervalometerAction(
    uint8_t id,
    uint32_t shotInterval,
    uint8_t focusPin,
    uint8_t shootPin,
    IntervalTimerManagerInterface& itmi,
    LiquidCrystal& lcd)
:
    IntervalAction(id, 1000, itmi),
    _numberOfShots(0),
    _shotNumber(0),
    _shotInterval(shotInterval),
    _shotTimeCountDown(0),
    _menu(INTERVAL),
    _shooting(false),
    _lcd(lcd),
    _focusShootDelayAction(1, 500, focusPin, shootPin, itmi)
{
}

//-------------------------------------------------------------------------

void
IntervalometerAction:: begin()
{
    display();
}

//-------------------------------------------------------------------------

void
IntervalometerAction:: startShooting()
{
    activate();
    _shooting = isActive();
    if (_shooting)
    {
        _shotTimeCountDown = 0;
        action();
    }
}

//-------------------------------------------------------------------------

void
IntervalometerAction:: stopShooting()
{
    _shooting = false;
    _shotNumber = 0;
    deactivate();
    display();
}

//-------------------------------------------------------------------------

void
IntervalometerAction:: up()
{
    if (not _shooting)
    {
        switch (_menu)
        {
        case INTERVAL:

            _menu = NUMBER_OF_SHOTS;
            break;

        case FOCUS_SHOOT_DELAY:

            _menu = INTERVAL;
            break;

        case NUMBER_OF_SHOTS:

            _menu = FOCUS_SHOOT_DELAY;
            break;

        }

        display();
    }
}

//-------------------------------------------------------------------------

void
IntervalometerAction:: down()
{
    if (not _shooting)
    {
        switch (_menu)
        {
        case INTERVAL:

            _menu = FOCUS_SHOOT_DELAY;
            break;

        case FOCUS_SHOOT_DELAY:

            _menu = NUMBER_OF_SHOTS;
            break;

        case NUMBER_OF_SHOTS:

            _menu = INTERVAL;
            break;

        }

        display();
    }
}

//-------------------------------------------------------------------------

void
IntervalometerAction:: left()
{
    if (not _shooting)
    {
        switch (_menu)
        {
        case INTERVAL:

            if (_shotInterval >= 60)
            {
                uint32_t minutes = _shotInterval/60;

                if (minutes > 1)
                {
                    minutes = decrementInterval(minutes);
                    _shotInterval = minutes * 60;
                }
                else
                {
                    _shotInterval = 40;
                }
            }
            else
            {
                _shotInterval = decrementInterval(_shotInterval);
            }

            break;

        case FOCUS_SHOOT_DELAY:
        {
            uint32_t focusShootDelay = _focusShootDelayAction.getInterval();

            if (focusShootDelay > 100)
            {
                focusShootDelay -= 100;
            }
            else if (focusShootDelay > 10)
            {
                focusShootDelay -= 10;
            }
            else if (focusShootDelay > 0)
            {
                focusShootDelay -= 1;
            }

            _focusShootDelayAction.setInterval(focusShootDelay);

            break;
        }
        case NUMBER_OF_SHOTS:

            if (_numberOfShots > 1000)
            {
                _numberOfShots -= 1000;
            }
            else if (_numberOfShots > 100)
            {
                _numberOfShots -= 100;
            }
            else if (_numberOfShots > 10)
            {
                _numberOfShots -= 10;
            }
            else if (_numberOfShots > 0)
            {
                _numberOfShots -= 1;
            }

            break;
        }

        display();
    }
}

//-------------------------------------------------------------------------

void
IntervalometerAction:: right()
{
    if (not _shooting)
    {
        switch (_menu)
        {
        case INTERVAL:

            if (_shotInterval >= 60)
            {
                uint32_t minutes = _shotInterval/60;
                minutes = incrementInterval(minutes);
                _shotInterval = minutes * 60;
            }
            else
            {
                _shotInterval = incrementInterval(_shotInterval);
            }

            break;

        case FOCUS_SHOOT_DELAY:
        {
            uint32_t focusShootDelay = _focusShootDelayAction.getInterval();

            if (focusShootDelay < 10)
            {
                focusShootDelay += 1;
            }
            else if (focusShootDelay < 100)
            {
                focusShootDelay += 10;
            }
            else if (focusShootDelay < 1000)
            {
                focusShootDelay += 100;
            }

            _focusShootDelayAction.setInterval(focusShootDelay);

            break;
        }
        case NUMBER_OF_SHOTS:

            if (_numberOfShots < 10)
            {
                _numberOfShots += 1;
            }
            else if (_numberOfShots < 100)
            {
                _numberOfShots += 10;
            }
            else if (_numberOfShots < 1000)
            {
                _numberOfShots += 100;
            }
            else if (_numberOfShots < 10000)
            {
                _numberOfShots += 1000;
            }

            break;
        }

        display();
    }
}

//-------------------------------------------------------------------------

void
IntervalometerAction:: select()
{
    if (_shooting)
    {
        stopShooting();
    }
    else
    {
        startShooting();
    }
}

//-------------------------------------------------------------------------

void
IntervalometerAction:: action()
{
    if (_shotTimeCountDown == 0)
    {
        _shotNumber += 1;

        _focusShootDelayAction.focusAndShoot();

        display();

        if ((_numberOfShots > 0) && (_shotNumber >= _numberOfShots))
        {
            stopShooting();
        }
        else
        {
            _shotTimeCountDown = _shotInterval;
        }
    }
    else
    {
        display();
    }

    if (_shotTimeCountDown > 0)
    {
        --_shotTimeCountDown;
    }
}

//-------------------------------------------------------------------------

void
IntervalometerAction:: display()
{
    // ROW 0

    _lcd.setCursor(0, 0);

    if (_shooting)
    {
        if (_shotInterval > 1)
        {
            uint16_t minutes = _shotTimeCountDown / 60;
            uint16_t seconds = _shotTimeCountDown % 60;

            if (minutes < 10)
            {
                _lcd.print('0');
            }

            _lcd.print(minutes, DEC);
            
            _lcd.print(':');

            if (seconds < 10)
            {
                _lcd.print('0');
            }

            _lcd.print(seconds, DEC);
        }
        else
        {
            _lcd.print(F("     "));
        }

        _lcd.print(F(" shot:"));
        formatShots(_shotNumber % 10000);
    }
    else
    {
        switch (_menu)
        {
        case INTERVAL:

            _lcd.print(F("shot interval   "));
            break;

        case FOCUS_SHOOT_DELAY:
        {
            _lcd.print(F("FS Delay: "));

            uint32_t focusShootDelay = _focusShootDelayAction.getInterval();

            if (focusShootDelay < 100)
            {
                _lcd.print(' ');
            }

            if (focusShootDelay < 10)
            {
                _lcd.print(' ');
            }

            _lcd.print(focusShootDelay, DEC);
            _lcd.print(F(" ms"));

            break;
        }
        case NUMBER_OF_SHOTS:

            _lcd.print(F("number of shots "));
            break;
        }
    }

    // ROW 1

    _lcd.setCursor(0, 1);

    if (_shotInterval >= 60)
    {
        uint32_t minutes = _shotInterval/60;

        if (minutes < 10)
        {
            _lcd.print(' ');
        }

        _lcd.print(minutes, DEC);
        _lcd.print('M');
    }
    else
    {
        if (_shotInterval < 10)
        {
            _lcd.print(' ');
        }

        _lcd.print(_shotInterval, DEC);
        _lcd.print('S');
    }

    _lcd.print(F("  shots:"));
    formatShots(_numberOfShots);
}

//-------------------------------------------------------------------------

void
IntervalometerAction:: formatShots(
    uint32_t number)
{
    if (number == 0)
    {
        _lcd.print(F("-----"));
    }
    else
    {
        for (uint32_t placeValue = 10000; placeValue > 1; placeValue /= 10)
        {
            if (number < placeValue)
            {
                _lcd.print(' ');
            }
            else
            {
                break;
            }
        }

        _lcd.print(number, DEC);
    }
}

//-------------------------------------------------------------------------

uint16_t
IntervalometerAction:: intervals[9] = { 1, 2, 4, 5, 10, 20, 30, 40, 60 };

//-------------------------------------------------------------------------

uint16_t
IntervalometerAction:: incrementInterval(
    uint16_t interval)
{
    uint16_t numberOfIntervals = sizeof(intervals)/sizeof(intervals[0]);

    if (interval >= intervals[numberOfIntervals - 1])
    {
        interval = intervals[numberOfIntervals - 1];
    }
    else
    {
        for (uint8_t i = 0 ; i < numberOfIntervals ; ++i)
        {
            if (interval < intervals[i])
            {
                interval = intervals[i];
                break;
            }
        }
    }

    return interval;
}

//-------------------------------------------------------------------------

uint16_t
IntervalometerAction:: decrementInterval(
    uint16_t interval)
{
    uint16_t numberOfIntervals = sizeof(intervals)/sizeof(intervals[0]);

    if (interval  <= intervals[0])
    {
        interval = intervals[0];
    }
    else
    {
        for (int8_t i = numberOfIntervals - 1 ; i >= 0 ; --i)
        {
            if (interval > intervals[i])
            {
                interval = intervals[i];
                break;
            }
        }
    }

    return interval;
}

//-------------------------------------------------------------------------
