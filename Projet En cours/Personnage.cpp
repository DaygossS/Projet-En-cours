#include "Personnage.hpp"
#include <algorithm>

using namespace sf;
using namespace std;

namespace game {

    Personnage::Personnage(int vie, int degats, float vitesse) noexcept
        : vie_(vie), degats_(degats), vitesse_(vitesse) {
    }

    void Personnage::subirDegats(int degats) noexcept {
        if (degats <= 0) return;
        vie_ = max(0, vie_ - degats);
    }

    bool Personnage::estVivant() const noexcept { return vie_ > 0; }

    int Personnage::getVie() const noexcept { return vie_; }
    void Personnage::setVie(int vie) noexcept { vie_ = max(0, vie); }

    int Personnage::getDegats() const noexcept { return degats_; }
    void Personnage::setDegats(int degats) noexcept { degats_ = degats; }

    float Personnage::getVitesse() const noexcept { return vitesse_; }
    void Personnage::setVitesse(float vitesse) noexcept { vitesse_ = vitesse; }

}
