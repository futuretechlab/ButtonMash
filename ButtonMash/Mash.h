// Mash.h

#ifndef _MASH_h
#define _MASH_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include <Bounce2.h>
#include <stdio.h>

extern "C" {
	typedef void(*Callback)(void);
}

enum MashStates {
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
	uint8_t _buttonReleased; // Released value 1/0
	uint8_t _buttonPressed; // Pressed value 1/0
	volatile unsigned long debounceInterval;
	volatile unsigned long doublePressInterval;
	volatile unsigned long holdInterval;
	volatile unsigned long pressDownTime;
	Callback PressUpCallback;
	Callback PressDownCallback;
	Callback DoublePressUpCallback;
	Callback DoublePressDownCallback;
	Callback PressAndHoldDownCallback;
	Callback PressAndHoldUpCallback;
	Callback UnpressCallback;
public:
	Mash();
	uint8_t _pin; // pin address
	MashStates CurrentState;
	MashStates LastState;
	void Attach(int pin, bool isActiveLow);
	void Update();
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
};

class Simul {
private:
	Mash* Mashes[20]; // Ten fingers ten toes
	Callback SimulCallback;
	uint8_t simulLen;
	bool simulFired;
	MashStates SimulState;
public:
	Simul(MashStates simulState);
	void Attach(Mash *mash);
	void OnSimul(Callback callback);
	void Update();
};

class Combo {
public:
	Combo(byte length);
	bool Part(int part);
	void OnCombo(Callback callback);
private:
	int comboLen;
	int previousPart;
	Callback ComboCallback;
};

#endif

