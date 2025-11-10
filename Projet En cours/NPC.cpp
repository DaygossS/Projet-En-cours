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
        : Personnage(50.f, 10.f, 100.f),
        direction_(1.f),
        cadenceTir_(1.5f),
        fireTimer_(0.f),
        arme_(false) // arme pour tirs vers le bas (verts)
    {
        static bool seeded = false;
        if (!seeded) { std::srand(static_cast<unsigned>(std::time(nullptr))); seeded = true; }

        if (!texture_.loadFromFile("assets/enemy.png"))
        {
            throw runtime_error("Impossible de charger assets/enemy.png");
        }

        sprite_.setTexture(texture_, true); // lie et recalcule
        sprite_.setScale(Vector2f(0.07f, 0.07f)); // adapte selon ton asset
        sprite_.setPosition(position);

        // debug
        auto b = sprite_.getGlobalBounds();
        cout << "NPC créé pos=(" << position.x << "," << position.y << ") size=("
            << b.size.x << "x" << b.size.y << ")\n";
    }

    void NPC::update(float deltaTime)
    {
        // mouvement horizontal basique (tu peux centraliser via Formation si tu veux)
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

        // logique de tir : timer + probabilité
        fireTimer_ += deltaTime;
        if (fireTimer_ >= 0.3f) // on teste la probabilité toutes les 0.3s
        {
            // faible probabilité pour éviter tirs simultanés (ex: 4%)
            const int chancePercent = 4;
            if ((std::rand() % 100) < chancePercent)
            {
                // spawn centré sous le sprite (en tenant compte de l'échelle)
                auto bounds = sprite_.getGlobalBounds();
                Vector2f spawn(
                    pos.x + bounds.size.x / 2.f - 1.5f,
                    pos.y + bounds.size.y + 4.f
                );

                arme_.tirer(spawn);
            }
            fireTimer_ = 0.f; // reset test timer
        }

        // mise à jour de l'arme (déplacement des projectiles)
        arme_.update(deltaTime);
    }
    void NPC::updateControlled(float deltaTime)
    {
        // On ne fait PAS de déplacement horizontal ici : Formation s'en charge.
        // On ne traite pas non plus les rebonds / descente ici pour éviter les duplications.

        // Mise à jour du timer de tir
        fireTimer_ += deltaTime;

        // Test probabiliste toutes les 0.3s
        if (fireTimer_ >= 0.3f)
        {
            const int chancePercent = 4; // ~4% de chance par test
            if ((std::rand() % 100) < chancePercent)
            {
                auto pos = sprite_.getPosition();
                auto bounds = sprite_.getGlobalBounds();
                Vector2f spawn(
                    pos.x + bounds.size.x / 2.f - 1.5f,
                    pos.y + bounds.size.y + 4.f
                );

                arme_.tirer(spawn);
            }
            fireTimer_ = 0.f;
        }

        // Mise à jour de l'arme (déplace les projectiles)
        arme_.update(deltaTime);
    }


    void NPC::draw(RenderWindow& window)
    {
        window.draw(sprite_);
        arme_.draw(window);
    }
}
