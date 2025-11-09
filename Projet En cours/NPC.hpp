#ifndef GAME_NPC_HPP
#define GAME_NPC_HPP

#include "Personnage.hpp"
#include <SFML/Graphics.hpp>

namespace game {

    class NPC : public Personnage {
    public:
        void deplacer(const sf::Vector2f& offset);
        sf::FloatRect getGlobalBounds() const;
        NPC(float x, float y);
        void update(float deltaTime) override;
        void draw(sf::RenderTarget& target) const override;

    private:
        sf::Texture texture_;
        sf::Sprite sprite_; // on le construit dans la liste d’initialisation
    };

} // namespace game

#endif
