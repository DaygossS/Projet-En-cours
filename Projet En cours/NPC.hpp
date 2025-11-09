#pragma once
#include "Personnage.hpp"

namespace game
{
    class NPC : public Personnage
    {
    public:
        explicit NPC(sf::Vector2f position);
        void update(float deltaTime) override;
        void draw(sf::RenderWindow& window) override;
        void move(const sf::Vector2f& offset) { sprite_.move(offset); }
        sf::Vector2f getPosition() const { return sprite_.getPosition(); }
    };
}
