#pragma once
#include "Arme.hpp"

namespace game
{
    class ArmeNPC : public Arme
    {
    public:
        ArmeNPC(float vitesse = 400.f);

        // On surcharge proprement la méthode tirer
        void tirer(const sf::Vector2f& position, float scale = 1.0f) override;
    };
}
