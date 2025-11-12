#pragma once
#include "Personnage.hpp"
#include "Arme.hpp"

namespace game
{
    class Joueur : public Personnage
    {
    public:
        Joueur();

        void update(float deltaTime) override;
        void draw(sf::RenderWindow& window) override;

        Arme& getArme() { return arme_; }

    private:
        void handleInput(float deltaTime);
        Arme arme_;
    };
}