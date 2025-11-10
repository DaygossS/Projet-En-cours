#pragma once
#include "Personnage.hpp"
#include "Arme.hpp"

using namespace sf;
using namespace std;

namespace game
{
    class Joueur : public Personnage
    {
    public:
        Joueur();
        void update(float deltaTime) override;
        void draw(RenderWindow& window) override;
        Arme& getArme() { return arme_; }
        const Arme& getArme() const { return arme_; }

        float getDegats() const { return degats_; }
        float getVie() const { return vie_; }
        void setVie(float v) { vie_ = v; }

        sf::FloatRect getGlobalBounds() const { return sprite_.getGlobalBounds(); }

    private:

        void handleInput(float deltaTime);
        Arme arme_{ true }; // tirs rouges vers le haut


    };
}