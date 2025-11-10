#include "Formation.hpp"
#include <memory>
#include <iostream>

using namespace sf;
using namespace std;

namespace game
{
    Formation::Formation()
    {
        const unsigned int cols = 10;       // moins large pour mieux voir
        const unsigned int rows = 4;       // nombre de lignes
        const Vector2f startPos(100.f, 50.f);
        const float spacingX = 60.f;       // espacement horizontal
        const float spacingY = 50.f;       // espacement vertical

        for (unsigned int i = 0; i < rows; ++i)
        {
            for (unsigned int j = 0; j < cols; ++j)
            {
                float x = startPos.x + j * spacingX;
                float y = startPos.y + i * spacingY;
                npcs_.push_back(make_unique<NPC>(Vector2f(x, y)));
            }
        }

        cout << "Formation creee avec " << npcs_.size() << " NPCs." << endl;
    }

    void Formation::update(float deltaTime)
    {
        bool changeDir = false;

        for (auto& npc : npcs_)
        {
            // déplacement horizontal individuel (comme avant)
            npc->move(sf::Vector2f(vitesse_ * direction_ * deltaTime, 0.f));

            npc->updateControlled(deltaTime);
            // rebond sur les bords : vérifier la position x du sprite
            float x = npc->getPosition().x;
            // si tu veux utiliser la largeur du sprite pour un test plus précis :
            // float spriteRight = x + npc->getGlobalBounds().size.x;
            if (x < 0.f || x > 760.f) // garde la valeur historique si elle marchait pour toi
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
        {
            npc->draw(window);
        }
    }
}
