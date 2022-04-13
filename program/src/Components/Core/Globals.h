#ifndef GLOBALS_HPP
#define GLOBALS_HPP 1

#include "Core/Timer.h"
#include <SFML/Graphics.hpp>

#include <iostream>
#include <random>
#include <time.h>

namespace eke
{
    class Timer;
    class Globals
    {
    public:
        static void Init();
        static void CleanUp();
        static void Update();
        static void PollEvents();

    public:
        // Helper to create dummy texture
        static sf::Texture CreateDummyTexture(const unsigned int &width, const unsigned int &height, const sf::Color &color);

    public:
        // Init state
        static sf::ContextSettings *CurrentContextSettings;
        static sf::RenderWindow *RenderWindow;
        static sf::Event *Event;
        static sf::Clock *Clock;
        static sf::Font GameFont;
        // Update state
        static float FPS;
        static float DeltaTime;
        static float GameTime;
        static sf::Vector2f MousePosition;
        // Debug
        static bool Debug;

    private:
        static eke::Timer *fpstimer;
        static void FpsTimerCallback();
        static void UpdateMousePos();

    public:
        Globals() = delete;
        Globals(const Globals &other) = delete;
        Globals(Globals &&other) = delete;
        ~Globals() = delete;
    };
}
#endif