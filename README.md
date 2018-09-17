# ButtonMash
A button sequence management system for Arduino

Mash:
A mash is a basic single button sequence detector with debouce build in. The default debounce method non-blocking and uses the millis()
method to deturmine stability.

To use the blocking method with delay simply use:
#define BLOCKING_DEBOUNCE true

The callback for each event is set by passing the method to the associated method for that event. The supported events are:
UnPressed,
PressedDown,
PressedUp,
DoublePressedDown,
DoublePressedUp,
PressAndHoldDown,
PressAndHoldUp

Be sure to include the mash.Update() method in the loop to keep things running.

Simul:
A simul handles multiple simultanious button press sequence events. To instantiate a simul simply pass one of the above event types
in the constructor for the simul. Then in the setup you will need to pass the address (&mash) for the mash(s) that you wish to attach
in the attach method for that simul. When the mash(s) attached to the simul fire the chosen event at the same time, the callback passed 
to OnSimul() will fire.

Combo:
A combo allows for sequences of multiple button presses to trigger a callback. To create a combo, first instantiate the class with the
desired length, and pass the callback to OnCombo(). Next add the Part() tags to the callbacks for each part of the combo. In this way,
each of the callbacks in the sequence will build up to the combo callback as they are called. To create complex combos with reapeats, you 
can place combo Part() tags in the callback for other combos, thus creating a daisy chain combo.
