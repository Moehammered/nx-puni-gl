#include "Timer.h"
#include <switch\arm\counter.h>

const double puni::Timer::NANO_TO_SECONDS = 1000000000.0;
// puni::Timer* puni::Timer::_instance = nullptr;

puni::Timer& puni::Timer::Instance()
{
    // if(!_instance)
    //     _instance = new Timer();

    // return *_instance;
    static Timer _instance;

    return _instance;
}

float puni::Timer::DeltaTime()
{
    return Instance().deltaTime;
}

float puni::Timer::ElapsedTime()
{
    return Instance().currentFrameTime - Instance().startTime;
}

void puni::Timer::Tick()
{
    //get cpu tick info
    Instance().currentTick = armGetSystemTick();
    Instance().deltaTick = Instance().currentTick - Instance().lastTick;
    //workout frametime info
    Instance().currentFrameTime = armTicksToNs(Instance().currentTick) / NANO_TO_SECONDS;
    Instance().deltaTime = Instance().currentFrameTime - Instance().lastFrameTime;
    Instance().lastTick = Instance().currentTick;
    Instance().lastFrameTime = Instance().currentFrameTime;
}

puni::Timer::Timer() { startTime = armTicksToNs(armGetSystemTick()) / NANO_TO_SECONDS; }
puni::Timer::~Timer() {}