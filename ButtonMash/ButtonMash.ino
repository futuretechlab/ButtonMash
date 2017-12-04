/*
 Name:		ButtonMash.ino
 Created:	11/30/2017 11:20:40
 Author:	FTL
*/

// the setup function runs once when you press reset or power the board

#include "Mash.h"

Mash mash2;
Mash mash3;
//Mash mashes[] = { mash2, mash3 };
//Combo combo23 = Combo(mashes);

//int lb2 = 0;
//int lb3 = 0;

void setup() {
	Serial.begin(9600);
	Serial.println("Setup started!");
	pinMode(2, INPUT);
	pinMode(3, INPUT);
	mash2.attach(2, false);
	mash3.attach(3, false);
	/*mash2.ComboState = PressedDown;
	mash3.ComboState = PressedDown;
	combo23.OnCombo(MyComboCallback);*/
	
	mash3.OnPressDown(MyPressDownCallback3);
	mash2.OnPressDown(MyPressDownCallback2);
	Serial.println("Setup complete!");
}

// the loop function runs over and over again until power down or reset
void loop() {
	mash3.update();
	mash2.update();
	
	//combo23.update();
	/*int b2 = digitalRead(2);
	int b3 = digitalRead(3);
	if (lb2 != b2)
		Serial.println("Button 2 pressed!");

	if (lb3 != b3)
		Serial.println("Button 3 pressed!");
	lb2 = b2;
	lb3 = b3;*/
}

void MyComboCallback()
{
	Serial.println("Combo callback fired!");
}

void MyPressDownCallback2()
{
	Serial.println("Button 2 pressed!");
}

void MyPressDownCallback3()
{
	Serial.println("Button 3 pressed!");
}