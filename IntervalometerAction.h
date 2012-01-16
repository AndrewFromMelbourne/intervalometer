#ifndef INTERVALOMETER_ACTION_H
#define INTERVALOMETER_ACTION_H

//-------------------------------------------------------------------------

#include "IntervalAction.h"

//-------------------------------------------------------------------------

class IntervalTimerManagerInterface;
class LiquidCrystal;

//-------------------------------------------------------------------------

class IntervalometerAction
:
    public IntervalAction
{
public:

    enum Menu { INTERVAL, FOCUS_SHOOT_DELAY, NUMBER_OF_SHOTS };

    IntervalometerAction(
        uint8_t id,
        uint32_t shotInterval,
        uint8_t focusPin,
        uint8_t shootPin,
        IntervalTimerManagerInterface& itmi,
        LiquidCrystal& lcd);

	void begin();

	void startShooting();
	void stopShooting();

    void right();
    void up();
    void down();
    void left();
    void select();

    virtual void action();

private:

    void display();
	void formatShots(uint32_t number);

	static uint16_t incrementInterval(uint16_t interval);
	static uint16_t decrementInterval(uint16_t interval);

    uint8_t _focusPin;
    uint8_t _shootPin;
    uint32_t _numberOfShots;
    uint32_t _shotNumber;
	uint16_t _shotInterval;
	uint16_t _shotTimeCount;
    uint16_t _focusShootDelay;
    uint8_t _menu;
    boolean _shooting;
    LiquidCrystal& _lcd;
};

//-------------------------------------------------------------------------

typedef void (IntervalometerAction::*IntervalometerActionCallback)();

//-------------------------------------------------------------------------

#endif
