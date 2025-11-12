#include "Boss.hpp"
#include <stdexcept>

using namespace sf;

namespace game
{
    Boss::Boss(Vector2f position)
        : NPC(position)
    {
        vie_ = 750.f;
        degats_ = 50.f;
        vitesse_ = 100.f;

        if (!texture_.loadFromFile("assets/boss.png"))
        {
            throw std::runtime_error("Impossible de charger assets/boss.png");
        }

        sprite_.setTexture(texture_);

        //  SFML 3.0.2 : plus de IntRect, on utilise Rect<int> avec position et size
        Vector2u texSize = texture_.getSize();
        sprite_.setTextureRect(sf::Rect<int>{
            {0, 0},  // position du rectangle
            { static_cast<int>(texSize.x), static_cast<int>(texSize.y) } // taille du rectangle
        });

        sprite_.setOrigin(Vector2f(texSize.x / 2.f, texSize.y / 2.f));
        sprite_.setScale(Vector2f(0.08f, 0.08f));
        sprite_.setRotation(degrees(180.f));
        sprite_.setPosition(position);
    }
}
