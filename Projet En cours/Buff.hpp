#ifndef GAME_BUFF_HPP
#define GAME_BUFF_HPP

#include <SFML/System.hpp>

namespace game {

    class Joueur;

    enum class TypeBuff {
        Bouclier,
        Vitesse,
        CadenceTir,
        Degats
    };

    class Buff {
    public:
        Buff(TypeBuff type, float duree, float valeur);

        void appliquer(Joueur& joueur);
        void retirer(Joueur& joueur);
        void update(float deltaTime);
        bool estExpire() const noexcept;

    private:
        TypeBuff type_;
        float duree_;
        float tempsRestant_;
        float valeur_;
        bool actif_;
    };

}

#endif
