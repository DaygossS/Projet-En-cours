#pragma once
#include <SFML/Graphics.hpp>

namespace game
{
    class Personnage
    {
    public:
        Personnage(float vie, float degats, float vitesse);
        virtual ~Personnage() = default;

        virtual void update(float deltaTime) = 0;
        virtual void draw(sf::RenderWindow& window) = 0;

        float getVie() const;
        void setVie(float vie);

        float getDegats() const;
        void setDegats(float degats);

        float getVitesse() const;
        void setVitesse(float vitesse);

        bool isAlive() const { return vie_ > 0; }
        void setAlive(bool alive) { vie_ = alive ? vie_ : 0.f; }
        sf::FloatRect getGlobalBounds() const { return sprite_.getGlobalBounds(); }


    protected:
        float vie_;
        float degats_;
        float vitesse_;
        sf::Texture texture_;
        sf::Sprite sprite_;  // plus de pointeur ici 
    };
}
