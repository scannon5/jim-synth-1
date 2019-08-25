#pragma once

class TimedPattern
{
    public:
        TimedPattern(int* pattern, int patternLength, void (*a_onChange)(int));
        int get();
        void set(int index);
        void reset();
        void update();
    private:
        int* pattern;
        int patternLength;
        void (*onChange)(int);
        int patternIndex;
        unsigned long startTime;
        unsigned long nextTime;
        void calcNextTime(unsigned long currentTime);
};
