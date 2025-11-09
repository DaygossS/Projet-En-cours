#ifndef GAME_JOUEUR_HPP
#define GAME_JOUEUR_HPP

#include "Personnage.hpp"
#include "Arme.hpp"
#include "Buff.hpp"
#include <SFML/Graphics.hpp>
#include <memory>
#include <vector>

namespace game {

    class Joueur : public Personnage {
    public:
        Joueur();
        void update(float deltaTime) override;
        void draw(sf::RenderTarget& target) const override;
        void appliquerBuff(const Buff& buff);

    private:
        void handleInput();
        void chargerTexture();           // charge la texture du joueur

        sf::Texture texture_;
        std::unique_ptr<sf::Sprite> sprite_; // pointeur pour éviter la construction par défaut
        std::unique_ptr<Arme> arme_;
        std::vector<Buff> buffsActifs_;
    };

} // namespace game

#endif
