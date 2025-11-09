#include "NPC.hpp"
#include <stdexcept>

using namespace sf;
using namespace std;

namespace game {

    NPC::NPC(float x, float y)
        : Personnage(50, 10, 100.f)
        , texture_()
        , sprite_(texture_) // construction obligatoire avec texture
    {
        if (!texture_.loadFromFile("C:\\Users\\Tony\\source\\repos\\Projet En cours\\x64\\Debug\\assets\\enemy.png")) {
            throw runtime_error("Erreur : impossible de charger assets/enemy.png");
        }

        sprite_.setPosition({ x, y });
    }

    void NPC::update(float deltaTime) {
        Vector2f moveVec(0.f, vitesse_ * deltaTime);
        sprite_.move(moveVec);
    }

    void NPC::draw(RenderTarget& target) const {
        target.draw(sprite_);
    }
    void NPC::deplacer(const sf::Vector2f& offset) {
        sprite_.move(offset);
    }

    sf::FloatRect NPC::getGlobalBounds() const {
        return sprite_.getGlobalBounds();
    }


} // namespace game
