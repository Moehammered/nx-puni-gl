#ifndef SWITCH__TIMER__H_
#define SWITCH__TIMER__H_

namespace puni
{
    class Timer
    {
        public:
            static float DeltaTime();
            static float ElapsedTime();
            static void Tick();

        private:
            Timer();

            static Timer& Instance();
            // static Timer* _instance;

            double lastTick, currentTick, deltaTick;
            double lastFrameTime, currentFrameTime, deltaTime;
            double startTime;
            static const double NANO_TO_SECONDS;
    };
}

#endif