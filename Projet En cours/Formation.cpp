#include "Formation.hpp"
#include <iostream>

using namespace sf;
using namespace std;

namespace game
{
    Formation::Formation(unsigned int cols, unsigned int rows, Vector2f startPos, float spacingX, float spacingY)
        : vitesse_(80.f), direction_(1.f), descente_(25.f)
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

        // 1. Déplacement horizontal
        for (auto& npc : npcs_)
        {
            npc->move(Vector2f(vitesse_ * direction_ * deltaTime, 0.f));

            // Vérification des bords (seulement pour le premier qui les touche)
            float x = npc->getPosition().x;
            float width = npc->getGlobalBounds().size.x;
            if (x < 0.f || x + width > 800.f)
            {
                changeDir = true;
            }
        }

        // 2. Descente collective si besoin (une seule fois)
        if (changeDir)
        {
            direction_ = -direction_;
            for (auto& npc : npcs_)
                npc->move(Vector2f(0.f, descente_));
        }

        // 3. Mise à jour logique des tirs / IA
        for (auto& npc : npcs_)
        {
            npc->updateControlled(deltaTime);
        }
    }

    void Formation::draw(RenderWindow& window)
    {
        for (auto& npc : npcs_)
            npc->draw(window);
    }
}
