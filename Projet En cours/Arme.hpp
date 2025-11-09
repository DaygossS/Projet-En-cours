#ifndef GAME_ARME_HPP
#define GAME_ARME_HPP

#include <SFML/Graphics.hpp>
#include <vector>

namespace game {

    class Arme {
    public:
        Arme(float vitesseProjectile, float cadenceTir, sf::Color couleurProjectile);

        void tirer(const sf::Vector2f& position, const sf::Vector2f& direction);
        void update(float deltaTime);
        void draw(sf::RenderTarget& target) const;

    private:
        float vitesseProjectile_;
        float cadenceTir_;
        sf::Color couleurProjectile_;
        float tempsDepuisDernierTir_;

        sf::Clock horloge_; // pour gérer la cadence de tir

        // Liste des projectiles actifs
        std::vector<sf::CircleShape> projectiles_;
        std::vector<sf::Vector2f> directions_;
    };

} // namespace game

#endif
