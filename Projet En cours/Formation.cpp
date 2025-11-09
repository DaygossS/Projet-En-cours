#include "Formation.hpp"
#include <algorithm>

using namespace sf;
using namespace std;

namespace game {

    Formation::Formation(float startX, float startY, float spacingX, float spacingY)
        : direction_(1.f, 0.f)
        , vitesse_(60.f)
        , descente_(20.f)
    {
        const int colonnes = 16;
        const int lignes = 4;

        for (int y = 0; y < lignes; ++y) {
            for (int x = 0; x < colonnes; ++x) {
                float posX = startX + x * spacingX;
                float posY = startY + y * spacingY;
                ennemis_.push_back(make_unique<NPC>(posX, posY));
            }
        }
    }

    void Formation::update(float deltaTime, const RenderWindow& window) {
        // Calcul des limites actuelles
        FloatRect bounds = formationBounds();
        bool rebond = false;

        if (bounds.left + bounds.width >= window.getSize().x - 10.f) {
            direction_.x = -1.f;
            rebond = true;
        }
        else if (bounds.left <= 10.f) {
            direction_.x = 1.f;
            rebond = true;
        }

        // Déplacement global de la formation
        Vector2f mouvement(direction_.x * vitesse_ * deltaTime, rebond ? descente_ : 0.f);

        for (auto& ennemi : ennemis_) {
            ennemi->deplacer(mouvement); // on ajoute cette méthode dans NPC
            ennemi->update(deltaTime);
        }
    }

    void Formation::draw(RenderTarget& target) const {
        for (const auto& ennemi : ennemis_) {
            ennemi->draw(target);
        }
    }

    FloatRect Formation::formationBounds() const {
        if (ennemis_.empty())
            return {};

        FloatRect rect = ennemis_.front()->getGlobalBounds();
        for (const auto& ennemi : ennemis_) {
            rect = rect.union_(ennemi->getGlobalBounds());
        }
        return rect;
    }

} // namespace game
