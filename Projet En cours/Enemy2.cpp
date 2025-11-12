#include "Enemy2.hpp"
#include <cstdlib>
#include <iostream>

using namespace sf;
using namespace std;

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
        sprite_.setScale(Vector2f(0.2f, 0.2f));
        sprite_.setRotation(sf::degrees(180.f));
        sprite_.setPosition(position);

        // si tu veux une cadence spécifique : cadenceTir_ = 2.0f; etc.
    }

    void Enemy2::update(float deltaTime)
    {
        // Si tu veux conserver le mouvement de NPC
        NPC::update(deltaTime);

        // Tir spécifique d'Enemy2 : projectiles 2x plus gros
        fireTimer_ += deltaTime;
        if (fireTimer_ >= 0.5f) // test toutes les 0.5s
        {
            const int chancePercent = 5;
            if ((std::rand() % 100) < chancePercent)
            {
                auto pos = sprite_.getPosition();
                auto bounds = sprite_.getGlobalBounds();
                Vector2f spawn(pos.x + bounds.size.x / 2.f - 2.f, pos.y + bounds.size.y + 6.f);
                arme_->tirer(spawn, 2.f);
            }
            fireTimer_ = 0.f;
        }

        arme_->update(deltaTime);
    }

    void Enemy2::draw(RenderWindow& window)
    {
        window.draw(sprite_);
        arme_->draw(window);
    }
}
