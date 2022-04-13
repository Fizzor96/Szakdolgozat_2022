#ifndef TIMER_HPP
#define TIMER_HPP 1

#include "Views/MainScene.h"
#include <SFML/Graphics.hpp>
#include <functional>

namespace eke
{
    class MainScene;
    class Timer
    {
    public:
        // One arg ctor, requires interval in seconds (e.g. "1.f" is one second).
        // Update loop must have contain timer update fn in order to work!
        Timer(const float &timer);
        // Two args ctor, requires interval in seconds (e.g. "1.f" is one second) and a boolean to make it repeat.
        // Update loop must have contain timer update fn in order to work!
        Timer(const float &timer, const bool &repeatonexpire);
        // Default destructor
        ~Timer();
        // Include this in the update loop!
        void Update(const float &delta);
        // Starts the timer if it is not started yet.
        void Start();
        // Stop the timer.
        void Stop();
        // Stop the timer then starting it.
        void Restart();
        // Reset timer without starting it.
        void Reset();
        // Set interval of the timer and reset it without starting it
        void SetInterval(const float &interval);
        // Set startcallback (requires fn obj in order to captur objs outside of lambda)!
        void SetStartCallback(std::function<void()> *callbackstart);
        // Set expiredcallback (requires fn obj in order to captur objs outside of lambda)!
        void SetExpiredCallback(std::function<void()> *callbackexpired);
        // Returning remaining time.
        float GetRemainingTime() const;
        // Returning elapsed time.
        float GetElapsedTime() const;
        // Return timer state, 1 if started 0 if expired or not yet started.
        bool GetState() const;

    private:
        float originaltimer;
        float timer;
        bool expired;
        bool started;
        bool repeatonexpire;
        std::function<void()> *startcallback;
        std::function<void()> *expiredcallback;

    private:
        void InitCallbackPtrs();

        // Deleted copy and move ctors cuz we don't want to copy or move any timers (especially move can lead to undefined behaviour or maybe the program will crash)
    public:
        Timer(const eke::Timer &other) = delete;
        Timer(eke::Timer &&other) = delete;
        Timer &operator=(const eke::Timer &other) = delete;
        Timer &operator=(eke::Timer &&other) = delete;
    };
}

#endif