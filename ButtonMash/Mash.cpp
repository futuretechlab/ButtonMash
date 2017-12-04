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

void Mash::attach(int pin, bool isActiveLow)
{
	_pin = pin;
	Serial.print(pin);
	Serial.println(" Attached");
	debouncer.attach(pin);
	
	if (isActiveLow)
	{
		_buttonPressed = 0;
		_buttonReleased = 1;
	}

}

void Mash::update()
{
	/*Serial.print(millis());
	Serial.println(" - update called.");*/
	debouncer.update();
	LastState = CurrentState;
	if (debouncer.read() == _buttonPressed)
	{
		if (CurrentState == UnPressed) {
			if (millis() - pressDownTime < doublePressInterval) {
				CurrentState = DoublePressedDown;
			}
			else
			{
				CurrentState = PressedDown;
				pressDownTime = millis();
			}
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
		//Serial.print("State change detected on ");
		//Serial.println(_pin);
		switch (CurrentState)
		{
		case UnPressed:
			//Serial.println("UnPressed");
			if(UnpressCallback != NULL)
				UnpressCallback();
			break;
		case PressedDown:
			//Serial.println("PressedDown");
			if (PressDownCallback != NULL)
				PressDownCallback();
			break;
		case PressedUp:
			//Serial.println("PressedUp");
			if (PressUpCallback != NULL)
				PressUpCallback();
			break;
		case DoublePressedDown:
			//Serial.println("DoublePressedDown");
			if (DoublePressDownCallback != NULL)
				DoublePressDownCallback();
			break;
		case DoublePressedUp:
			//Serial.println("DoublePressedUp");
			if (DoublePressUpCallback != NULL)
				DoublePressUpCallback();
			break;
		case PressAndHoldDown:
			//Serial.println("PressAndHoldDown");
			if (PressAndHoldDownCallback != NULL)
				PressAndHoldDownCallback();
			break;
		case PressAndHoldUp:
			//Serial.println("PressAndHoldUp");
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

void Mash::SetComboState(MomentaryStates state)
{
	ComboState = state;
}

Combo::Combo(Mash mashes[])
{
	Mashes = mashes;
	comboLen = sizeof(mashes) / sizeof(*mashes);
}

void Combo::OnCombo(Callback callback)
{
	ComboCallback = callback;
}

void Combo::update()
{
	for (int i = 0; i < comboLen; i++)
		if (Mashes[i].CurrentState != Mashes[i].ComboState) return;
	if(ComboCallback != NULL)
		ComboCallback();
}
