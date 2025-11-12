#include "Formation.hpp"
#include "Enemy2.hpp"
#include "Boss.hpp"
#include <iostream>

using namespace sf;
using namespace std;

namespace game
{
    Formation::Formation(unsigned int cols, unsigned int rows, Vector2f startPos, float spacingX, float spacingY)
        : vitesse_(40.f), direction_(1.f), descente_(25.f)
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
        static bool descenteEffectuee = false;
        const float windowWidth = 800.f;

        // --- Mouvement horizontal ---
        for (auto& npc : npcs_)
        {
            npc->move(Vector2f(vitesse_ * direction_ * speedMultiplier_ * deltaTime, 0.f));

            auto bounds = npc->getGlobalBounds();
            float left = bounds.position.x;
            float right = bounds.position.x + bounds.size.x;

            // marges personnalisées selon le type
            float margeGauche = 0.f;
            float margeDroite = 0.f;

            if (dynamic_cast<Enemy2*>(npc.get()))
            {
                margeGauche = 55.f;  // plus de marge à gauche
                margeDroite = 0.f;  // légère marge à droite
            }
            else if (dynamic_cast<Boss*>(npc.get()))
            {
                margeGauche = 80.f;
                margeDroite = 30.f;
            }
            else // NPC standard
            {
                margeGauche = 0.f;
                margeDroite = 0.f;
            }

            // détection des bords
            if ((direction_ < 0.f && left <= 0.f - margeGauche) ||
                (direction_ > 0.f && right >= windowWidth + margeDroite))
            {
                changeDir = true;
            }
        }

        // --- Descente lors du changement de direction ---
        if (changeDir && !descenteEffectuee)
        {
            direction_ = -direction_;
            for (auto& npc : npcs_)
                npc->move(Vector2f(0.f, descente_));
            descenteEffectuee = true;
        }
        else if (!changeDir)
        {
            descenteEffectuee = false; // on réarme la descente quand la direction est stable
        }

        // --- Timer de début de vague ---
        if (!vagueActive_)
        {
            debutVagueTimer_ += deltaTime;
            if (debutVagueTimer_ < 6.f) // délai avant activation des tirs
                return;
            vagueActive_ = true;
        }

        // --- Mise à jour IA et tirs ---
        for (auto& npc : npcs_)
            npc->updateControlled(deltaTime);
    }

    void Formation::resetVagueTimer()
    {
        debutVagueTimer_ = 0.f;
        vagueActive_ = false;
    }

    void Formation::draw(RenderWindow& window)
    {
        for (auto& npc : npcs_)
            npc->draw(window);
    }
}
