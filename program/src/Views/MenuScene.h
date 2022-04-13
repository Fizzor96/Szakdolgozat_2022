#ifndef MENUSCENE_HPP
#define MENUSCENE_HPP 1

#include "Controller.h"
#include "Core.h"
#include "UI/Button.h"
#include <functional>
#include <vector>

namespace eke
{
    enum class SceneId;
    class Fire;
    class Button;
    class Timer;
    class Label;
    class Entity;

    class MenuScene : public Scene
    {
    public:
        MenuScene();
        ~MenuScene();

        eke::MenuScene *GetInstance() const;
        eke::SceneId GetSceneId() const;
        void PollEvents();
        void Update();
        void Draw();

    public:
        std::vector<eke::Button *> buttons;
        std::vector<eke::Fire *> fires;
        eke::Label *info_lbl;
        bool helpisvisible;

    private:
        static eke::MenuScene *Instance;

    private:
        void InitComponents();

    public:
        MenuScene(const MenuScene &other) = delete;
        MenuScene(MenuScene &&other) = delete;
        MenuScene &operator=(const MenuScene &other) = delete;
        MenuScene &operator=(MenuScene &&other) = delete;
    };
}

#endif