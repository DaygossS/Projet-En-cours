#pragma once
#include "Personnage.hpp"
#include "Arme.hpp"
#include <SFML/System/Clock.hpp>

namespace game
{
    class NPC : public Personnage
    {
    public:
        NPC(sf::Vector2f position);
        void update(float deltaTime) override;
        void draw(sf::RenderWindow& window) override;

        sf::Vector2f getPosition() const { return sprite_.getPosition(); }
        sf::FloatRect getGlobalBounds() const { return sprite_.getGlobalBounds(); }
        void setPosition(const sf::Vector2f& pos) { sprite_.setPosition(pos); }
        void move(const sf::Vector2f& offset) { sprite_.move(offset); }
        void updateControlled(float deltaTime);


    private:
        float direction_ = 1.f;
        float cadenceTir_ = 1.5f;   // base, modifiable
        float fireTimer_ = 0.f;     // accumule le temps entre tir
        Arme arme_{ false };        // false => tirs vers le bas (verts)
    };
}
