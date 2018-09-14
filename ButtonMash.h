/***************************************************************************
The MIT License (MIT)
Copyright (c) 2017, Alexander Juskovic

Permission is hereby granted, free of charge, to any person obtaining a copy of
this software and associated documentation files (the "Software"), to deal in
the Software without restriction, including without limitation the rights to
use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
the Software, and to permit persons to whom the Software is furnished to do so,
subject to the following conditions:
The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.
THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
/***************************************************************************/

#ifndef _BUTTONMASH_h
#define _BUTTONMASH_h

/***************************************************************************/

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

#include <stdio.h>

/***************************************************************************/

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

/***************************************************************************/

class Mash
{
private:
	uint8_t _buttonReleased; // Released value 1/0
	uint8_t _buttonPressed; // Pressed value 1/0
	unsigned long debounceDelay;
	unsigned long lastDebounceTime;
	unsigned long doublePressInterval;
	unsigned long holdInterval;
	unsigned long pressDownTime;
	Callback PressUpCallback;
	Callback PressDownCallback;
	Callback DoublePressUpCallback;
	Callback DoublePressDownCallback;
	Callback PressAndHoldDownCallback;
	Callback PressAndHoldUpCallback;
	Callback UnpressCallback;
	uint8_t Debounce();
	uint8_t lastButtonState;
	uint8_t buttonState;
public:
	Mash();
	uint8_t _pin; // pin address
	MashStates CurrentState;
	MashStates LastState;
	void Attach(int pin, bool isActiveLow);
	void Update();
	void DebounceDelay(uint16_t delay_millis);
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

/***************************************************************************/

class Simul {
private:
	Mash *Mashes[20]; // Ten fingers ten toes
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

/***************************************************************************/

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

