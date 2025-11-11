#include "Boss.hpp"
#include <stdexcept>

using namespace sf;

namespace game
{
    Boss::Boss(Vector2f position)
        : NPC(position)
    {
        vie_ = 2000.f;
        degats_ = 50.f;
        vitesse_ = 100.f;

        if (!texture_.loadFromFile("assets/boss.png"))
        {
            throw std::runtime_error("Impossible de charger assets/boss.png");
        }

        sprite_.setTexture(texture_);
        sprite_.setScale(Vector2f(1.0f, 1.0f));
        sprite_.setPosition(position);
    }
}
