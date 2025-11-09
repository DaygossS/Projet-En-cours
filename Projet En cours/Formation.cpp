#include "Formation.hpp"
#include <iostream>

using namespace sf;
using namespace std;

namespace game
{
    Formation::Formation(unsigned int cols, unsigned int rows, Vector2f startPos, float spacingX, float spacingY)
    {
        for (unsigned int y = 0; y < rows; ++y)
        {
            for (unsigned int x = 0; x < cols; ++x)
            {
                Vector2f pos(
                    startPos.x + x * spacingX,
                    startPos.y + y * spacingY
                );
                npcs_.push_back(make_unique<NPC>(pos));
            }
        }
    }

    void Formation::update(float deltaTime)
    {
        bool changeDir = false;

        for (auto& npc : npcs_)
        {
            npc->move(Vector2f(vitesse_ * direction_ * deltaTime, 0.f));

            // rebond sur les bords
            float x = npc->getPosition().x;
            if (x < 0.f || x > 760.f)
                changeDir = true;
        }

        if (changeDir)
        {
            direction_ = -direction_;
            for (auto& npc : npcs_)
            {
                npc->move(Vector2f(0.f, descente_));
            }
        }
    }

    void Formation::draw(RenderWindow& window)
    {
        for (auto& npc : npcs_)
            npc->draw(window);
    }
}
