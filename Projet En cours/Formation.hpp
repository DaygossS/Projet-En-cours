#ifndef GAME_FORMATION_HPP
#define GAME_FORMATION_HPP

#include "NPC.hpp"
#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>

namespace game {

    class Formation {
    public:
        Formation(float startX, float startY, float spacingX, float spacingY);
        void update(float deltaTime, const sf::RenderWindow& window);
        void draw(sf::RenderTarget& target) const;

    private:
        std::vector<std::unique_ptr<NPC>> ennemis_;
        sf::Vector2f direction_;     // direction du mouvement (1 ou -1 en X)
        float vitesse_;              // vitesse horizontale
        float descente_;             // descente verticale lors d’un rebond
        sf::FloatRect formationBounds() const; // calcule les limites de la formation
    };

} // namespace game

#endif
