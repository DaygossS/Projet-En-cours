#ifndef GAME_PERSONNAGE_HPP
#define GAME_PERSONNAGE_HPP

#include <SFML/Graphics.hpp>

namespace game {

    class Personnage {
    public:
        Personnage(int vie = 100, int degats = 10, float vitesse = 100.0f) noexcept;
        virtual ~Personnage() noexcept = default;

        virtual void update(float deltaTime) = 0;
        virtual void draw(sf::RenderTarget& target) const = 0;

        virtual void subirDegats(int degats) noexcept;
        virtual bool estVivant() const noexcept;

        int getVie() const noexcept;
        void setVie(int vie) noexcept;

        int getDegats() const noexcept;
        void setDegats(int degats) noexcept;

        float getVitesse() const noexcept;
        void setVitesse(float vitesse) noexcept;

    protected:
        int vie_;
        int degats_;
        float vitesse_;
    };

} // namespace game

#endif
