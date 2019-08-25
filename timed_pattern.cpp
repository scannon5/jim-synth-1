#include <Arduino.h>
#include "timed_pattern.h"

TimedPattern::TimedPattern(int* a_pattern, int a_patternLength, void (*a_onChange)(int))
{
    pattern = a_pattern;
    patternLength = a_patternLength;
    onChange = a_onChange;
    reset();
}

int TimedPattern::get()
{
    return patternIndex;
}

void TimedPattern::set(int index)
{
    patternIndex = index;
    startTime = millis();
    calcNextTime(startTime);
}

void TimedPattern::reset()
{
    set(0);
}

void TimedPattern::update()
{
    unsigned long currentTime = millis();
    if (currentTime >= nextTime)
    {
        (*onChange)(patternIndex);
        patternIndex++;
        if (patternIndex >= patternLength)
        {
            patternIndex = 0;
        }
        calcNextTime(currentTime);
    }
}

void TimedPattern::calcNextTime(unsigned long currentTime)
{
    nextTime = currentTime + pattern[patternIndex];
}
