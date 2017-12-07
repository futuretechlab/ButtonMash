/*
 Name:		ButtonMash.ino
 Created:	11/30/2017 11:20:40
 Author:	FTL
*/

// the setup function runs once when you press reset or power the board

#include "Mash.h"

Mash mashB;
Mash mashA;
Simul simulAB = Simul(PressedDown);
Simul simulHoldAB = Simul(PressAndHoldDown);
Combo comboS1 = Combo(3);
Combo comboS2 = Combo(3);
const int A = 2;
const int B = 3;

void setup() {
	Serial.begin(9600);
	Serial.println("Setup started!");

	// Set pins to input
	pinMode(A, INPUT);
	pinMode(B, INPUT);

	// Attach pins to mash
	mashB.Attach(A, false);
	mashA.Attach(B, false);

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
	comboS1.OnCombo(MyComboCallbackS1);
	comboS2.OnCombo(MyComboCallbackS2);
	Serial.println("Setup complete!");
}

// the loop function runs over and over again until power down or reset
void loop() {
	// Call update() for all mashes/simuls
	mashA.Update();
	mashB.Update();
	simulAB.Update();
	simulHoldAB.Update();
}

void MySimulCallback()
{
	Serial.println("Simul AB press down fired!");
}

void MySimulHoldCallback()
{
	Serial.println("Simul AB press and hold down fired!");
}

void MyPressDownCallbackA()
{
	comboS2.Part(1);
	comboS1.Part(0);
	Serial.println("A pressed down!");
}

void MyPressDownCallbackB()
{
	comboS1.Part(1);
	Serial.println("B pressed down!");
}

void MyPressAndHoldDownCallbackA()
{
	comboS2.Part(2);
	Serial.println("A held down!");
}

void MyComboCallbackS1()
{
	comboS2.Part(0);
	Serial.println(" A, B-, Combo FIRED!!!");
}

void MyPressAndHoldDownCallbackB()
{
	comboS1.Part(2);
	Serial.println("B held down!");
}

void MyComboCallbackS2()
{
	Serial.println("A, B-, A-, Combo FIRED!!!");
}