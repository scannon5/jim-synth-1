#include <Arduino.h>
#include "debounce.h"
#include "timed_pattern.h"

//const int buttonCount = 4;
//int button

const int buttonPin0 = A0;
const int buttonPin1 = A1;
const int buttonPin2 = A2;
const int buttonPin3 = A3;

const int ledPin0 = 2;
const int ledPin1 = 3;
const int ledPin2 = 4;
const int ledPin3 = 5;
const int ledPin4 = 6;
const int ledPin5 = 7;
const int ledPin6 = 8;
const int ledPin7 = 9;

const int ledCount = 8;
int leds[ledCount] = { ledPin0, ledPin1, ledPin2, ledPin3, ledPin4, ledPin5, ledPin6, ledPin7 };

Debouncer* debouncer0;
Debouncer* debouncer1;
Debouncer* debouncer2;
Debouncer* debouncer3;

const int pattern0Length = 8;
int pattern0[pattern0Length] = { 75, 75, 75, 75, 75, 75, 75, 75 };

void setPinModes();
void createDebouncers();
void debouncer0Changed(int newValue);
void debouncer1Changed(int newValue);
void debouncer2Changed(int newValue);
void debouncer3Changed(int newValue);
void lightCurrentLed();
void createPatterns();
void pattern0Changed(int index);
void fixPatternIndex();
int pattern0led(int index);

int currentLed = 0;
int showPatternIndex = -1;
bool patternUp = true;
bool lastDirectionUp = true;
const int patternCount = 1;
TimedPattern* tp0;

void setup() {
    setPinModes();
    createDebouncers();
    createPatterns();
    lightCurrentLed();
}

void loop() {
    debouncer0->update();
    debouncer1->update();
    debouncer2->update();
    debouncer3->update();
    tp0->update();
}

void setPinModes()
{
    pinMode(buttonPin0, INPUT);
    pinMode(buttonPin1, INPUT);
    pinMode(buttonPin2, INPUT);
    pinMode(buttonPin3, INPUT);
    
    pinMode(ledPin0, OUTPUT);
    pinMode(ledPin1, OUTPUT);
    pinMode(ledPin2, OUTPUT);
    pinMode(ledPin3, OUTPUT);
    pinMode(ledPin4, OUTPUT);
    pinMode(ledPin5, OUTPUT);
    pinMode(ledPin6, OUTPUT);
    pinMode(ledPin7, OUTPUT);
}

void createDebouncers()
{
    debouncer0 = new Debouncer(buttonPin0, &debouncer0Changed, LOW, LOW, LOW);
    debouncer1 = new Debouncer(buttonPin1, &debouncer1Changed, LOW, LOW, LOW);
    debouncer2 = new Debouncer(buttonPin2, &debouncer2Changed, LOW, LOW, LOW);
    debouncer3 = new Debouncer(buttonPin3, &debouncer3Changed, LOW, LOW, LOW);
}

void moveStaticLed(bool up)
{
    if (showPatternIndex != -1)
    {
        if (showPatternIndex == 0)
        {
            currentLed = pattern0led(tp0->get());
            if (currentLed % 2 != 0)
            {
                currentLed--;
            }
        }
        else
        {
            currentLed = 0;
        }
        showPatternIndex = -1;
    }
    else
    {
        if (up)
        {
            currentLed += 2;
        }
        else
        {
            currentLed -= 2;
        }
    }
    lightCurrentLed();
    lastDirectionUp = up;
}

void debouncer0Changed(int newValue)
{
    moveStaticLed(false);
}

void debouncer1Changed(int newValue)
{
    moveStaticLed(true);
}

void debouncer2Changed(int newValue)
{
    if (showPatternIndex == -1)
    {
        showPatternIndex = 0;
        patternUp = lastDirectionUp;
        tp0->set(currentLed);
    }
    else
    {
        patternUp = !patternUp;
    }
}

void debouncer3Changed(int newValue)
{
    if (pattern0[0] == 75)
    {
        changePattern0Interval(25);
    }
    else
    {
        changePattern0Interval(75);
    }
} 

void changePattern0Interval(int newInterval)
{
    for (int i = 0; i < pattern0Length; i++)
    {
        pattern0[i] = newInterval;
    }
}

void lightCurrentLed()
{
    while (currentLed < 0)
    {
        currentLed += ledCount;
    }
    while (currentLed >= ledCount)
    {
        currentLed -= ledCount;
    }
    for (int i = 0; i < ledCount; i++)
    {
        digitalWrite(leds[i], i == currentLed || i == currentLed + 1 ? HIGH : LOW);
    }
}

void createPatterns()
{
    tp0 = new TimedPattern(pattern0, pattern0Length, &pattern0Changed);
}

void pattern0Changed(int index)
{
    if (showPatternIndex == 0)
    {
        for (int i = 0; i < ledCount; i++)
        {
            //bool b = patternUp ? (index == i) :  (index == (ledCount - 1 - i));
            bool b = index == pattern0led(i);
            digitalWrite(leds[i], b ? HIGH : LOW);
        }
    }
}

void fixPatternIndex()
{
    while (showPatternIndex < 0)
    {
        showPatternIndex += patternCount;
    }
    while (showPatternIndex >= patternCount)
    {
        showPatternIndex -= patternCount;
    }
}

int pattern0led(int index)
{
    return patternUp ? index :  (ledCount - 1 - index);
}