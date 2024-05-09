//
// Created by jmmar on 09/05/2024.
//

#ifndef CLOCK_H
#define CLOCK_H



class Clock {
public:
    Clock(int totalNumOfTicksToRun, int numOfWarmUpTicks);
    [[nodiscard]] int getTotalNumberOfTicksToRun() const;

private:
    int totalNumOfTicksToRun_m;
    int numOfWarmUpTicks_m;
};



#endif //CLOCK_H
