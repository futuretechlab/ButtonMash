#include "Mash.h"

Mash::Mash()
{
	debouncer = Bounce();
	_buttonPressed = 1;
	_buttonReleased = 0;
	debounceInterval = 50;
	doublePressInterval = 700;
	holdInterval = 5000;
	debouncer.interval(debounceInterval);
}

void Mash::Attach(int pin, bool isActiveLow)
{
	_pin = pin;
	debouncer.attach(pin);
	if (isActiveLow)
	{
		_buttonPressed = 0;
		_buttonReleased = 1;
	}

}

void Mash::Update()
{
	/*Serial.print(millis());
	Serial.println(" - update called.");*/
	debouncer.update();
	LastState = CurrentState;
	if (debouncer.read() == _buttonPressed)
	{
		if (CurrentState == UnPressed) {
			if (millis() - pressDownTime < doublePressInterval && DoublePressDownCallback != NULL) {
				CurrentState = DoublePressedDown;
			}
			else
			{
				CurrentState = PressedDown;
			}
			pressDownTime = millis();
		}
		else if (CurrentState == PressedDown && millis() - pressDownTime > holdInterval) {
			CurrentState = PressAndHoldDown;
		}
	}
	else
	{
		if (CurrentState == PressedDown) {
			CurrentState = PressedUp;
		}
		else if (CurrentState == PressAndHoldDown) {
			CurrentState = PressAndHoldUp;
		}
		else if (CurrentState == DoublePressedDown) {
			CurrentState = DoublePressedUp;
		}
		else
		{
			CurrentState = UnPressed;
		}
	}

	if (CurrentState != LastState) {
		switch (CurrentState)
		{
		case UnPressed:
			if(UnpressCallback != NULL)
				UnpressCallback();
			break;
		case PressedDown:
			if (PressDownCallback != NULL)
				PressDownCallback();
			break;
		case PressedUp:
			if (PressUpCallback != NULL)
				PressUpCallback();
			break;
		case DoublePressedDown:
			if (DoublePressDownCallback != NULL)
				DoublePressDownCallback();
			break;
		case DoublePressedUp:
			if (DoublePressUpCallback != NULL)
				DoublePressUpCallback();
			break;
		case PressAndHoldDown:
			if (PressAndHoldDownCallback != NULL)
				PressAndHoldDownCallback();
			break;
		case PressAndHoldUp:
			if (PressAndHoldUpCallback != NULL)
				PressAndHoldUpCallback();
			break;
		default:
			break;
		}
	}
}

void Mash::DebounceInterval(uint16_t interval_millis)
{
	debounceInterval = interval_millis;
	debouncer.interval(debounceInterval);
}

void Mash::HoldInterval(uint16_t interval_millis)
{
	holdInterval = interval_millis;
}

void Mash::DoublePressInterval(uint16_t interval_millis)
{
	doublePressInterval = interval_millis;
}

void Mash::OnPressDown(Callback callback)
{
	PressDownCallback = callback;
}

void Mash::OnPressUp(Callback callback)
{
	PressUpCallback = callback;
}

void Mash::OnDoublePressDown(Callback callback)
{
	DoublePressDownCallback = callback;
}

void Mash::OnDoublePressUp(Callback callback)
{
	DoublePressUpCallback = callback;
}

void Mash::OnPressAndHoldDown(Callback callback)
{
	PressAndHoldDownCallback = callback;
}

void Mash::OnPressAndHoldUp(Callback callback)
{
	PressAndHoldUpCallback = callback;
}

void Mash::OnUnpress(Callback callback)
{
	UnpressCallback = callback;
}

Simul::Simul(MashStates simulState)
{
	SimulState = simulState;
	simulLen = 0;
}

void Simul::Attach(Mash *mash)
{
	if (simulLen >= 9) return;
	Mashes[simulLen] = mash;
	simulLen++;
}

void Simul::OnSimul(Callback callback)
{
	SimulCallback = callback;
}

void Simul::Update()
{
	Mash *m;
	int i = 0;
	while ((m = Mashes[i]) != NULL)
	{
		if (Mashes[i]->CurrentState != SimulState)
		{
			simulFired = false;
			return;
		}
		i++;
	}
	if(SimulCallback != NULL && !simulFired)
		SimulCallback();
	simulFired = true;
}

Combo::Combo(byte length)
{
	comboLen = length;
	previousPart = -1;
}

bool Combo::Part(int p)
{
	// out of range
	if (p > comboLen || previousPart + 1 != p)
	{
		previousPart = -1;
		return false;
	}

	previousPart = p;

	if (p == comboLen - 1)
	{
		previousPart = -1;
		if(ComboCallback != NULL)
			ComboCallback();
	}
	return true;
}

void Combo::OnCombo(Callback callback)
{
	ComboCallback = callback;
}

