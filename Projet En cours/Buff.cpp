#include "Buff.hpp"
#include "Joueur.hpp"

using namespace sf;
using namespace std;

namespace game {

    Buff::Buff(TypeBuff type, float duree, float valeur)
        : type_(type), duree_(duree), tempsRestant_(duree), valeur_(valeur), actif_(false) {
    }

    void Buff::appliquer(Joueur& joueur) {
        if (actif_) return;
        actif_ = true;
        // Effet initial selon le type
        switch (type_) {
        case TypeBuff::Bouclier: joueur.setVie(joueur.getVie() + static_cast<int>(valeur_)); break;
        case TypeBuff::Vitesse: joueur.setVitesse(joueur.getVitesse() + valeur_); break;
        default: break;
        }
    }

    void Buff::retirer(Joueur& joueur) {
        if (!actif_) return;
        actif_ = false;
        switch (type_) {
        case TypeBuff::Vitesse: joueur.setVitesse(joueur.getVitesse() - valeur_); break;
        default: break;
        }
    }

    void Buff::update(float deltaTime) {
        tempsRestant_ -= deltaTime;
    }

    bool Buff::estExpire() const noexcept {
        return tempsRestant_ <= 0.f;
    }

}
