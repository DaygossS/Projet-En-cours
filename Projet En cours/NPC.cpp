#include "NPC.hpp"
#include <stdexcept>

using namespace sf;
using namespace std;

namespace game
{
    NPC::NPC(Vector2f position)
        : Personnage(10.f, 25.f, 50.f)
    {
        if (!texture_.loadFromFile("assets/enemy.png"))
        {
            throw runtime_error("Impossible de charger assets/enemy.png");
        }

        // Même logique que Joueur
        sprite_ = Sprite(texture_);
        sprite_.setScale(Vector2f(0.07f, 0.07f)); // adapte si besoin
        sprite_.setPosition(position);
    }

    void NPC::update(float deltaTime)
    {
        sprite_.move(Vector2f(vitesse_ * deltaTime, 0.f));

        const float windowWidth = 800.f;

        auto rect = sprite_.getTextureRect();
        float spriteWidth = static_cast<float>(rect.size.x) * sprite_.getScale().x;

        auto pos = sprite_.getPosition();

        if (pos.x < 0.f || pos.x + spriteWidth > windowWidth)
        {
            vitesse_ = -vitesse_;           // inverse la direction
            pos.y += 20.f;                  // descend un peu, comme dans Space Invaders
        }

        sprite_.setPosition(pos);
    }


    void NPC::draw(RenderWindow& window)
    {
        window.draw(sprite_);
    }
}
