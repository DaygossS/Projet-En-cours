#pragma once
#include <SFML/Graphics.hpp>
#include <memory>
#include "Joueur.hpp"

using namespace sf;
using namespace std;

namespace game
{
    class World
    {
    public:
        World();
        void run();

    private:
        RenderWindow window_;
        unique_ptr<Joueur> joueur_;

        void processEvents();
        void update(float deltaTime);
        void render();
    };
}
