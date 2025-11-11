#include "Enemy2.hpp"
#include <stdexcept>

using namespace sf;

namespace game
{
    Enemy2::Enemy2(Vector2f position)
        : NPC(position)
    {
        vie_ = 80.f;
        degats_ = 25.f;
        vitesse_ = 100.f;

        if (!texture_.loadFromFile("assets/enemy2.png"))
        {
            throw std::runtime_error("Impossible de charger assets/enemy2.png");
        }

        sprite_.setTexture(texture_);
        sprite_.setScale(Vector2f(0.45f, 0.45f));
        sprite_.setPosition(position);
    }
}
