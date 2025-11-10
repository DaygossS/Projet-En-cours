// Formation.cpp
#include "Formation.hpp"
#include <memory>
#include <iostream>

using namespace sf;
using namespace std;

namespace game
{
    // Constructeur par défaut (facultatif)
    Formation::Formation()
        : vitesse_(50.f),
        descente_(20.f),
        direction_(1.f)
    {
        const unsigned int cols = 8;
        const unsigned int rows = 4;
        const Vector2f startPos(100.f, 50.f);
        const float spacingX = 70.f;
        const float spacingY = 60.f;

        for (unsigned int i = 0; i < rows; ++i)
        {
            for (unsigned int j = 0; j < cols; ++j)
            {
                float x = startPos.x + j * spacingX;
                float y = startPos.y + i * spacingY;
                npcs_.push_back(make_unique<NPC>(Vector2f(x, y)));
            }
        }

        cout << "Formation par défaut créée : " << npcs_.size() << " NPCs" << endl;
    }

    // --- Constructeur PARAMETRÉ requis par ton World::make_unique(...)
    Formation::Formation(unsigned int cols, unsigned int rows, Vector2f startPos, float spacingX, float spacingY)
        : vitesse_(50.f),
        descente_(20.f),
        direction_(1.f)
    {
        for (unsigned int i = 0; i < rows; ++i)
        {
            for (unsigned int j = 0; j < cols; ++j)
            {
                float x = startPos.x + j * spacingX;
                float y = startPos.y + i * spacingY;
                npcs_.push_back(make_unique<NPC>(Vector2f(x, y)));
            }
        }

        cout << "Formation personnalisée : " << cols << "x" << rows << " => " << npcs_.size() << " NPCs" << endl;
    }

    void Formation::update(float deltaTime)
    {
        bool changeDir = false;

        for (auto& npc : npcs_)
        {
            // Deplacement horizontal géré par la formation
            npc->move(sf::Vector2f(vitesse_ * direction_ * deltaTime, 0.f));

            // Conserver la logique interne (tir etc.) sans conflit positionnel :
            npc->updateControlled(deltaTime);

            float x = npc->getPosition().x;
            // test simple : si un ennemi dépasse la limite droite/ gauche
            if (x < 0.f || x > 760.f)
                changeDir = true;
        }

        if (changeDir)
        {
            direction_ = -direction_;
            for (auto& npc : npcs_)
            {
                npc->move(sf::Vector2f(0.f, descente_));
            }
        }
    }

    void Formation::draw(RenderWindow& window)
    {
        for (auto& npc : npcs_)
            npc->draw(window);
    }
}
