#ifndef MAINSCENE_HPP
#define MAINSCENE_HPP 1

#include "Controller.h"
#include "Core.h"
#include <functional>
#include <iostream>
#include <string>
#include <vector>

namespace eke
{
    class Level;
    class Label;
    class Button;
    class MainScene : public Scene
    {
    public:
        // Inherited from class Scene
        MainScene();
        ~MainScene();
        eke::SceneId GetSceneId() const;
        void PollEvents();
        void Update();
        void Draw();
        void Restart() override;
        void Resume();

    private:
        bool ispaused;
        // Level
        eke::Level *level;
        eke::Label *label;
        float survivaltime;
        // PauseMenu
        sf::RectangleShape *pmBackground;
        std::vector<eke::Button *> pmButtons;
        eke::Label *pmLabel;

    private:
        void InitComponents();
        void InitPauseMenu();

    private:
        void PollEventsPauseMenu();

    private:
        void UpdatePauseMenu();

    private:
        void DrawPauseMenu();

    private:
        static eke::MainScene *Instance;

    public:
        MainScene(const MainScene &other) = delete;
        MainScene(MainScene &&other) = delete;
        MainScene &operator=(const MainScene &other) = delete;
        MainScene &operator=(MainScene &&other) = delete;
    };
}

#endif