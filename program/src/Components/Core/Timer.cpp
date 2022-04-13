#include "Core/Timer.h"

namespace eke
{
    void Timer::InitCallbackPtrs()
    {
        this->startcallback = nullptr;
        this->expiredcallback = nullptr;
    }

    eke::Timer::Timer(const float &timer)
    {
        this->originaltimer = timer;
        this->timer = timer;
        this->expired = false;
        this->started = false;
        this->repeatonexpire = false;
        InitCallbackPtrs();
    }

    eke::Timer::Timer(const float &timer, const bool &repeatonexpire)
    {
        this->originaltimer = timer;
        this->timer = timer;
        this->expired = false;
        this->started = false;
        this->repeatonexpire = repeatonexpire;
        InitCallbackPtrs();
        // this->Start();
    }

    void Timer::SetInterval(const float &interval)
    {
        this->timer = interval;
        this->originaltimer = interval;
        this->Reset();
    }

    void Timer::SetStartCallback(std::function<void()> *cllbkstart)
    {
        this->startcallback = cllbkstart;
    }
    void Timer::SetExpiredCallback(std::function<void()> *cllbkexpired)
    {
        this->expiredcallback = cllbkexpired;
    }

    void Timer::Start()
    {
        if (!this->started)
        {
            this->started = true;
            if (this->startcallback != nullptr && this->timer == this->originaltimer)
            {
                (*this->startcallback)();
            }
        }
    }

    void Timer::Stop()
    {
        this->timer = this->originaltimer;
        this->expired = false;
        this->started = false;
    }

    void Timer::Restart()
    {
        this->timer = this->originaltimer;
        this->expired = false;
        eke::Timer::Start();
    }

    void Timer::Reset()
    {
        this->timer = this->originaltimer;
        this->expired = false;
        this->started = false;
    }

    void Timer::Update(const float &delta)
    {
        if (this->started == true)
        {
            timer -= delta;
            // On expiration
            if (this->timer <= 0)
            {
                this->started = false;
                this->expired = true;
                if (this->expiredcallback != nullptr && this->timer != this->originaltimer)
                {
                    (*this->expiredcallback)();
                    this->timer = this->originaltimer;
                }
                if (this->repeatonexpire)
                {
                    this->Restart();
                }
            }
        }
    }

    float Timer::GetRemainingTime() const
    {
        return this->timer;
    }

    float Timer::GetElapsedTime() const
    {
        return this->originaltimer - this->timer;
    }

    bool Timer::GetState() const
    {
        if (this->started == true)
        {
            return 1;
        }
        return 0;
    }

    Timer::~Timer()
    {
        if (this->startcallback != nullptr)
        {
            delete this->startcallback;
        }

        if (this->expiredcallback != nullptr)
        {
            delete this->expiredcallback;
        }
    }
}