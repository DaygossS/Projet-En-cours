#include "NPC.hpp"
#include <stdexcept>
#include <cstdlib>
#include <ctime>
#include <iostream>

using namespace sf;
using namespace std;

namespace game
{
    NPC::NPC(Vector2f position)
        : Personnage(20.f, 10.f, 100.f),
        direction_(1.f),
        cadenceTir_(1.5f),
        fireTimer_(0.f)
    {
        arme_ = std::make_unique<ArmeNPC>(400.f);

        static bool seeded = false;
        if (!seeded) { std::srand(static_cast<unsigned>(std::time(nullptr))); seeded = true; }

        if (!texture_.loadFromFile("assets/enemy.png"))
        {
            throw runtime_error("Impossible de charger assets/enemy.png");
        }

        sprite_.setTexture(texture_, true);
        sprite_.setScale(Vector2f(0.07f, 0.07f));
        sprite_.setPosition(position);
    }

    void NPC::update(float deltaTime)
    {
        Vector2f pos = sprite_.getPosition();
        pos.x += direction_ * vitesse_ * deltaTime;
        float width = sprite_.getGlobalBounds().size.x;

        if (pos.x < 0.f)
        {
            pos.x = 0.f;
            direction_ = 1.f;
            pos.y += 12.f;
        }
        else if (pos.x + width > 800.f)
        {
            pos.x = 800.f - width;
            direction_ = -1.f;
            pos.y += 12.f;
        }
        sprite_.setPosition(pos);

        fireTimer_ += deltaTime;
        if (fireTimer_ >= cadenceTir_)
        {
            const int chancePercent = 4;
            if ((std::rand() % 100) < chancePercent)
            {
                auto bounds = sprite_.getGlobalBounds();
                Vector2f spawn(
                    pos.x + bounds.size.x / 2.f - 1.5f,
                    pos.y + bounds.size.y + 4.f
                );
                arme_->tirer(spawn);
            }
            fireTimer_ = 0.f;
        }

        arme_->update(deltaTime);
    }

    void NPC::updateControlled(float deltaTime)
    {
        fireTimer_ += deltaTime;

        if (fireTimer_ >= 0.3f)
        {
            const int chancePercent = 8;
            if ((std::rand() % 100) < chancePercent)
            {
                auto pos = sprite_.getPosition();
                auto bounds = sprite_.getGlobalBounds();
                Vector2f spawn(
                    pos.x + bounds.size.x / 2.f - 1.5f,
                    pos.y + bounds.size.y + 4.f
                );

                arme_->tirer(spawn);
            }
            fireTimer_ = 0.f;
        }

        arme_->update(deltaTime);
    }

    void NPC::draw(RenderWindow& window)
    {
        window.draw(sprite_);
        arme_->draw(window);
    }
}
