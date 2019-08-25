#include <Arduino.h>
#include "debounce.h"

Debouncer::Debouncer(int theInputPin, void (*onChangeHandler)(int), int initialInputState, int initialOutputState, int initialLastOutputState)
{
    inputPin = theInputPin;
    inputState = initialInputState;
    outputState = initialOutputState;
    lastOutputState = initialLastOutputState;
    onChange = onChangeHandler;
    lastDebounceTime = 0;
}


void Debouncer::update()
{
    int reading = digitalRead(inputPin);

    if (reading != lastOutputState) {
        lastDebounceTime = millis();
    }

    if ((millis() - lastDebounceTime) > debounceDelay) {
        if (reading != inputState) {
            inputState = reading;
    
            if (inputState == HIGH) {
                outputState = !outputState;
                (*onChange)(outputState);
            }
        }
    }
    
    lastOutputState = reading;
}
