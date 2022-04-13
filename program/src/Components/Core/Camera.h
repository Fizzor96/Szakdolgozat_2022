#ifndef __CAMERA_H__
#define __CAMERA_H__

#include "Core/Globals.h"

#include <SFML/Graphics.hpp>

namespace eke
{
    // Basic camera implementation
    class Camera
    {
    private:
        sf::View view;

    public:
        Camera();
        ~Camera();
        void Update(sf::Vector2f pos);
        sf::View *GetView();
    };
}

#endif // __CAMERA_H__