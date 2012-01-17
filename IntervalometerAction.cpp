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
    _shotTimeCount(0),
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
        _shotTimeCount = _shotInterval;
        action();
        display();
    }
}

//-------------------------------------------------------------------------

void
IntervalometerAction:: stopShooting()
{
    _shooting = false;
    _shotNumber = 0;
    _shotTimeCount = 0;
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
    display();

    if (_shotTimeCount >= _shotInterval)
    {
        _shotNumber += 1;

        _focusShootDelayAction.focusAndShoot();


        if ((_numberOfShots > 0) && (_shotNumber >= _numberOfShots))
        {
            stopShooting();
        }
        else
        {
            _shotTimeCount = 0;
        }
    }
    else
    {
    }

    ++_shotTimeCount;
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
            uint16_t remains = _shotInterval - _shotTimeCount;
            uint16_t minutes = remains / 60;
            uint16_t seconds = remains % 60;

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
            _lcd.print("     ");
        }

        _lcd.print(" shot:");
        formatShots(_shotNumber % 10000);
    }
    else
    {
        switch (_menu)
        {
        case INTERVAL:

            _lcd.print("shot interval   ");
            break;

        case FOCUS_SHOOT_DELAY:
        {
            _lcd.print("FS Delay: ");

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
            _lcd.print(" ms");

            break;
        }
        case NUMBER_OF_SHOTS:

            _lcd.print("number of shots ");
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

    _lcd.print("  shots:");
    formatShots(_numberOfShots);
}

//-------------------------------------------------------------------------

void
IntervalometerAction:: formatShots(
    uint32_t number)
{
    if (number == 0)
    {
        _lcd.print("-----");
    }

    if (number < 10000)
    {
        _lcd.print(' ');
    }

    if (number < 1000)
    {
        _lcd.print(' ');
    }

    if (number < 100)
    {
        _lcd.print(' ');
    }

    if (number < 10)
    {
        _lcd.print(' ');
    }

    _lcd.print(number, DEC);
}

//-------------------------------------------------------------------------

uint16_t
IntervalometerAction:: incrementInterval(
    uint16_t interval)
{
    if (interval < 1)
    {
        interval = 1;
    }
    else if (interval < 2)
    {
        interval = 2;
    }
    else if (interval < 4)
    {
        interval = 4;
    }
    else if (interval < 5)
    {
        interval = 5;
    }
    else if (interval < 10)
    {
        interval = 10;
    }
    else if (interval < 20)
    {
        interval = 20;
    }
    else if (interval < 30)
    {
        interval = 30;
    }
    else if (interval < 40)
    {
        interval = 40;
    }
    else
    {
        interval = 60;
    }

    return interval;
}

//-------------------------------------------------------------------------

uint16_t
IntervalometerAction:: decrementInterval(
    uint16_t interval)
{
    if (interval > 60)
    {
        interval = 60;
    }
    else if (interval > 40)
    {
        interval = 40;
    }
    else if (interval > 30)
    {
        interval = 30;
    }
    else if (interval > 20)
    {
        interval = 20;
    }
    else if (interval > 10)
    {
        interval = 10;
    }
    else if (interval > 5)
    {
        interval = 5;
    }
    else if (interval > 4)
    {
        interval = 4;
    }
    else if (interval > 2)
    {
        interval = 2;
    }
    else
    {
        interval = 1;
    }

    return interval;
}

//-------------------------------------------------------------------------
