#pragma once

class Debouncer
{
    public:
        Debouncer(int theInputPin, void (*onChangeHandler)(int), int initialInputState, int initialOutputState, int initialLastOutputState);
        void update();
    private:
        int inputPin;
        void (*onChange)(int);
        int outputState;
        int inputState;
        int lastOutputState;
        
        unsigned long lastDebounceTime;
        const unsigned long debounceDelay = 50;
};
