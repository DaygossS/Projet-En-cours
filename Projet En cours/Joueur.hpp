#pragma once
#include "Personnage.hpp"

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

    private:
        void handleInput(float deltaTime);
    };
}