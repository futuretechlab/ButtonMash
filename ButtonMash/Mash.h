// Mash.h

#ifndef _MASH_h
#define _MASH_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include <Bounce2.h>

extern "C" {
	typedef void(*Callback)(void);
}

enum MomentaryStates {
	UnPressed,
	PressedDown,
	PressedUp,
	DoublePressedDown,
	DoublePressedUp,
	PressAndHoldDown,
	PressAndHoldUp,
};

class Mash
{
private:
	Bounce debouncer;
	int _pin; // pin address
	int _buttonReleased; // Released value 1/0
	int _buttonPressed; // Pressed value 1/0
	volatile uint16_t debounceInterval;
	volatile uint16_t doublePressInterval;
	volatile uint16_t holdInterval;
	volatile uint16_t pressDownTime;
	Callback PressUpCallback;
	Callback PressDownCallback;
	Callback DoublePressUpCallback;
	Callback DoublePressDownCallback;
	Callback PressAndHoldDownCallback;
	Callback PressAndHoldUpCallback;
	Callback UnpressCallback;
public:
	Mash();
	MomentaryStates CurrentState;
	MomentaryStates LastState;
	MomentaryStates ComboState;
	void attach(int pin, bool isActiveLow);
	void update();
	void DebounceInterval(uint16_t interval_millis);
	void HoldInterval(uint16_t interval_millis);
	void DoublePressInterval(uint16_t interval_millis);
	void OnPressDown(Callback callback);
	void OnPressUp(Callback callback);
	void OnDoublePressDown(Callback callback);
	void OnDoublePressUp(Callback callback);
	void OnPressAndHoldDown(Callback callback);
	void OnPressAndHoldUp(Callback callback);
	void OnUnpress(Callback callback);
	void SetComboState(MomentaryStates state);
};

class Combo {
private:
	Mash *Mashes;
	Callback ComboCallback;
	int comboLen;
public:
	Combo(Mash mashes[]);
	void OnCombo(Callback callback);
	void update();
};

#endif

