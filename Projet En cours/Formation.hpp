#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>
#include "NPC.hpp"

using namespace sf;
using namespace std;

namespace game
{
    class Formation
    {
    public:
        Formation(unsigned int cols, unsigned int rows, Vector2f startPos, float spacingX, float spacingY);

        void update(float deltaTime);
        void draw(RenderWindow& window);

    private:
        vector<unique_ptr<NPC>> npcs_;
        float direction_ = 1.f; // 1 = droite, -1 = gauche
        float vitesse_ = 50.f;
        float descente_ = 20.f;
    };
}
