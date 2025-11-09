#pragma once
#include <SFML/Graphics.hpp>
#include <string>

using namespace sf;
using namespace std;

namespace game
{
    class Personnage
    {
    public:
        Personnage(float vie, float degats, float vitesse);
        virtual ~Personnage() = default;

        virtual void update(float deltaTime) = 0;
        virtual void draw(RenderWindow& window) = 0;

        float getVie() const;
        void setVie(float vie);

        float getDegats() const;
        void setDegats(float degats);

        float getVitesse() const;
        void setVitesse(float vitesse);

    protected:
        float vie_;
        float degats_;
        float vitesse_;
        Texture texture_;
        Sprite sprite_;
    };
}
