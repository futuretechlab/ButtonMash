/*
Name:		ButtonMash.ino
Created:	11/30/2017 11:20:40
Author:	FTL
*/

#include "ButtonMash.h"

// Class instances

// Mash handels single press state detection and triggers single button callbacks
Mash mashB;
Mash mashA;

// Simul handles muliple press state detection and triggers multi-button callbacks
Simul simulAB = Simul(PressedDown);
Simul simulHoldAB = Simul(PressAndHoldDown);

// Combo allows you to tag other callbacks to create sequence dependant callbacks
// Two part combo:
// A, hold B
Combo combo1 = Combo(2);
// Three part combo, with combo1 as the first part to form a daisy chain:
// Combo1, A, B
Combo combo2 = Combo(3);

// Button pins
const int A = 2;
const int B = 3;

void setup() {
	Serial.begin(9600);
	Serial.println("Setup started!");

	// Set pins to input
	pinMode(A, INPUT_PULLUP);
	pinMode(B, INPUT_PULLUP);

	// Attach pins to mash
	mashB.Attach(A, true);
	mashA.Attach(B, true);

	// Set mash callbacks
	mashB.OnPressDown(MyPressDownCallbackB);
	mashA.OnPressDown(MyPressDownCallbackA);
	mashB.OnPressAndHoldDown(MyPressAndHoldDownCallbackB);
	mashA.OnPressAndHoldDown(MyPressAndHoldDownCallbackA);

	// Attach mashes to simuls
	simulAB.Attach(&mashB);
	simulAB.Attach(&mashA);
	simulHoldAB.Attach(&mashB);
	simulHoldAB.Attach(&mashA);

	// Set simul callbacks
	simulAB.OnSimul(MySimulCallback);
	simulHoldAB.OnSimul(MySimulHoldCallback);

	// Set combo callbacks
	combo1.OnCombo(MyComboCallback1);
	combo2.OnCombo(MyComboCallback2);
	Serial.println("Setup complete!");
}

void loop() {
	// Call update() for all mashes/simuls
	mashA.Update();
	mashB.Update();
	simulAB.Update();
	simulHoldAB.Update();
}

void MySimulCallback()
{
	combo2.Part(3);
	Serial.println("Simul A+B press down fired!");
}

void MySimulHoldCallback()
{
	Serial.println("Simul AB press and hold down fired!");
}

void MyPressDownCallbackA()
{
	combo1.Part(0);
	combo2.Part(1);
	Serial.println("A pressed down!");
}

void MyPressDownCallbackB()
{
	combo2.Part(2);
	Serial.println("B pressed down!");
}

void MyPressAndHoldDownCallbackA()
{
	Serial.println("A held down!");
}

void MyPressAndHoldDownCallbackB()
{
	combo1.Part(1);
	Serial.println("B held down!");
}

void MyComboCallback1()
{
	combo2.Part(0); // Start combo2
	Serial.println("A, hold B = Combo1 FIRED!!!");
}

void MyComboCallback2()
{
	Serial.println("Combo1, A, B = Combo2 FIRED!!!");
}
