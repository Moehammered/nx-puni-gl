#include "Timer.h"
#ifdef __SWITCH__
#include <switch/arm/counter.h>
#elif __WINDOWS__
#include <chrono>
#endif

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
#ifdef __SWITCH__
    //get cpu tick info
    Instance().currentTick = armGetSystemTick();
    Instance().deltaTick = Instance().currentTick - Instance().lastTick;
    //workout frametime info
    Instance().currentFrameTime = armTicksToNs(Instance().currentTick) / NANO_TO_SECONDS;
    Instance().deltaTime = Instance().currentFrameTime - Instance().lastFrameTime;
    Instance().lastTick = Instance().currentTick;
    Instance().lastFrameTime = Instance().currentFrameTime;
#elif __WINDOWS__
    //get cpu tick info
    auto now = std::chrono::high_resolution_clock::now();
    auto now_ns = std::chrono::time_point_cast<std::chrono::nanoseconds>(now);
    auto currTime = std::chrono::duration_cast<std::chrono::nanoseconds>(now_ns.time_since_epoch()).count();
    //Instance().currentTick = armGetSystemTick(); //need to get tick info
    //Instance().deltaTick = Instance().currentTick - Instance().lastTick; //need to get tick info
    //workout frametime info
    Instance().currentFrameTime = currTime / NANO_TO_SECONDS;
    auto difference = Instance().currentFrameTime - Instance().lastFrameTime;
    Instance().deltaTime = difference;
    //Instance().lastTick = Instance().currentTick; //need to get tick info
    Instance().lastFrameTime = Instance().currentFrameTime;
#endif
}

puni::Timer::Timer() 
{ 
#ifdef __SWITCH__
    startTime = armTicksToNs(armGetSystemTick()) / NANO_TO_SECONDS; 
#elif __WINDOWS__
    auto now = std::chrono::high_resolution_clock::now();
    auto now_ns = std::chrono::time_point_cast<std::chrono::nanoseconds>(now);
    auto currTime = std::chrono::duration_cast<std::chrono::nanoseconds>(now_ns.time_since_epoch()).count() / NANO_TO_SECONDS;
    startTime = currTime;
#endif
}