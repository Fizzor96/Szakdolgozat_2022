#include "Camera.h"

namespace eke
{
    Camera::Camera()
    {
        this->view.setSize(sf::Vector2f(eke::Globals::RenderWindow->getSize().x * 0.6f, eke::Globals::RenderWindow->getSize().y * 0.6f));
    }

    Camera::~Camera()
    {
    }

    void Camera::Update(sf::Vector2f pos)
    {
        this->view.setCenter(pos);
        eke::Globals::RenderWindow->setView(this->view);
    }

    sf::View *Camera::GetView()
    {
        return &this->view;
    }
}