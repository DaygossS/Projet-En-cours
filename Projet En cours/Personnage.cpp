#include "Personnage.hpp"

using namespace sf;
using namespace std;

namespace game
{
    Personnage::Personnage(float vie, float degats, float vitesse)
        : vie_(vie),
        degats_(degats),
        vitesse_(vitesse),
        texture_(),
        sprite_(texture_) //  initialise explicitement le sprite avec la texture
    {
    }

    float Personnage::getVie() const { return vie_; }
    void Personnage::setVie(float vie) { vie_ = vie; }

    float Personnage::getDegats() const { return degats_; }
    void Personnage::setDegats(float degats) { degats_ = degats; }

    float Personnage::getVitesse() const { return vitesse_; }
    void Personnage::setVitesse(float vitesse) { vitesse_ = vitesse; }
}
