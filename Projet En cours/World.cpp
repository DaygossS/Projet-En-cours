#include "World.hpp"
#include <iostream>
#include <algorithm>
#include "Enemy2.hpp"
#include "Boss.hpp"

using namespace sf;
using namespace std;

namespace game
{
    World::World()
        : window_(VideoMode({ 800u, 600u }), "Stars Invaders - SFML 3.0.2"),
        joueur_(make_unique<Joueur>())
    {
        window_.setFramerateLimit(60);

        if (!font_.openFromFile("assets/fonts/Arial.ttf"))
            cerr << "Erreur : Impossible de charger Arial.ttf\n";

        if (!titleFont_.openFromFile("assets/fonts/Starjedi.otf"))
            cerr << "Erreur : Impossible de charger Starjedi.otf\n";

        // --- HUD Vie ---
        vieText_ = make_unique<Text>(font_);
        vieText_->setString("Vie : 100");
        vieText_->setCharacterSize(24);
        vieText_->setFillColor(Color::White);
        vieText_->setPosition({ 620.f, 10.f });

        // --- HUD Vague ---
        waveText_ = make_unique<Text>(font_);
        waveText_->setString("Vague : 1");
        waveText_->setCharacterSize(24);
        waveText_->setFillColor(Color::White);
        waveText_->setPosition({ 20.f, 10.f });

        // --- Barre de vie ---
        vieBarBackground_.setSize({ 150.f, 20.f });
        vieBarBackground_.setFillColor(Color(50, 50, 50));
        vieBarBackground_.setPosition({ 620.f, 40.f });

        vieBar_.setSize({ 150.f, 20.f });
        vieBar_.setFillColor(Color::Green);
        vieBar_.setPosition({ 620.f, 40.f });

        // --- Texte Game Over ---
        gameOverText_ = make_unique<Text>(font_);
        gameOverText_->setString("GAME OVER\n\nAppuyez sur R pour rejouer");
        gameOverText_->setCharacterSize(36);
        gameOverText_->setFillColor(Color::Red);
        gameOverText_->setStyle(Text::Bold);
        {
            FloatRect gb = gameOverText_->getLocalBounds();
            gameOverText_->setOrigin({ gb.size.x / 2.f, gb.size.y / 2.f });
            gameOverText_->setPosition({ window_.getSize().x / 2.f, window_.getSize().y / 2.f });
        }

        // --- Intro - Title ---
        titleText_ = make_unique<Text>(titleFont_);
        titleText_->setString("STARS INVADERS");
        titleText_->setCharacterSize(60);
        titleText_->setFillColor(Color::Yellow);
        {
            FloatRect tb = titleText_->getLocalBounds();
            titleText_->setOrigin({ tb.size.x / 2.f, tb.size.y / 2.f });
            titleText_->setPosition({ window_.getSize().x / 2.f, window_.getSize().y / 2.f + 100.f });
        }

        // --- Intro - Crawl ---
        crawlText_ = make_unique<Text>(font_);
        crawlText_->setString(
            "Il y a bien longtemps, dans une galaxie lointaine, très loingtaine...\n\n"
            "Un joueur avait été recruté spécialement par le résistance,\n"
            "Dans le but d'arrêter l'expension incéssante de l'Empire.\n"
            "La mission qui lui avait été confiée :\n\n"
            "A bord de son vaisseau x-wing, il devait\n"
            "Repousser l'envahisseur et ainsi libérer la galaxie.\n"
            "S'il échouait cette mission, c'était la fin de la liberté \n"
            "à travers la galaxie. Tout débuta lorsque ce valeureux résistant\n"
            "pris sont x-wing et alla combattre les troupe de Dark Vador.....");
        crawlText_->setCharacterSize(22);
        crawlText_->setFillColor(Color::White);
        {
            FloatRect cb = crawlText_->getLocalBounds();
            crawlText_->setOrigin({ cb.size.x / 2.f, cb.size.y / 2.f });
            crawlText_->setPosition({ window_.getSize().x / 2.f, window_.getSize().y + 100.f });
        }
    }

    void World::showIntro()
    {
        introActive_ = true;
        Clock clock;

        auto pressKey = make_unique<Text>(font_);
        pressKey->setString("Appuyez sur ESPACE pour commencer");
        pressKey->setCharacterSize(24);
        pressKey->setFillColor(Color::Cyan);
        {
            FloatRect pb = pressKey->getLocalBounds();
            pressKey->setOrigin({ pb.size.x / 2.f, pb.size.y / 2.f });
            pressKey->setPosition({ window_.getSize().x / 2.f, 500.f });
        }

        while (window_.isOpen() && introActive_)
        {
            float deltaTime = clock.restart().asSeconds();
            window_.clear(Color::Black);

            if (titleText_->getPosition().y > 150.f)
                titleText_->move({ 0.f, -20.f * deltaTime });

            if (titleText_->getPosition().y < 200.f)
            {
                Color c = titleText_->getFillColor();
                if (c.a > 3)
                    c.a -= 3;
                titleText_->setFillColor(c);
            }

            crawlText_->move({ 0.f, -40.f * deltaTime });
            float y = crawlText_->getPosition().y;
            float scale = max(0.4f, 1.0f - (700.f - y) / 1200.f);
            crawlText_->setScale({ scale, scale });

            window_.draw(*titleText_);
            window_.draw(*crawlText_);

            if (crawlText_->getPosition().y < 200.f)
                window_.draw(*pressKey);

            window_.display();

            while (auto eventOpt = window_.pollEvent())
            {
                const Event& event = *eventOpt;
                if (event.is<Event::Closed>())
                    window_.close();
            }

            if (Keyboard::isKeyPressed(Keyboard::Key::Space))
            {
                introActive_ = false;
                gameStarted_ = true;
                loadWave(1);
            }
        }
    }

    // ------------------ NOUVEAU : Texte entre les vagues ------------------
    void World::showWaveMessage(const std::string& message)
    {
        Text msg(font_);
        msg.setString(message);
        msg.setCharacterSize(36);
        msg.setFillColor(Color::Yellow);
        msg.setStyle(Text::Bold);

        auto centerText = [&](Text& t)
            {
                FloatRect bounds = t.getLocalBounds();
                t.setOrigin({ bounds.size.x / 2.f, bounds.size.y / 2.f });
                t.setPosition({ window_.getView().getCenter().x, window_.getView().getCenter().y });
            };

        centerText(msg);

        const float fadeIn = 0.7f;
        const float visible = 1.5f;
        const float fadeOut = 0.7f;

        Clock timer;
        while (window_.isOpen())
        {
            float t = timer.getElapsedTime().asSeconds();
            if (t > fadeIn + visible + fadeOut)
                break;

            while (auto eventOpt = window_.pollEvent())
            {
                const Event& ev = *eventOpt;
                if (ev.is<Event::Closed>())
                {
                    window_.close();
                    return;
                }
            }

            float alpha = 255.f;
            if (t < fadeIn)
                alpha = (t / fadeIn) * 255.f;
            else if (t > fadeIn + visible)
                alpha = 255.f - ((t - fadeIn - visible) / fadeOut) * 255.f;

            Color c = msg.getFillColor();
            c.a = static_cast<unsigned char>(std::clamp(alpha, 0.f, 255.f));
            msg.setFillColor(c);

            centerText(msg);

            window_.clear(Color::Black);
            window_.draw(msg);
            window_.display();
        }
    }
    // ---------------------------------------------------------------------

    void World::run()
    {
        showIntro();
        Clock clock;
        while (window_.isOpen())
        {
            processEvents();
            float deltaTime = clock.restart().asSeconds();
            update(deltaTime);
            render();
        }
    }

    

    void World::processEvents()
    {
        while (auto eventOpt = window_.pollEvent())
        {
            const Event& event = *eventOpt;
            if (event.is<Event::Closed>())
                window_.close();

            if (gameOver_ && Keyboard::isKeyPressed(Keyboard::Key::R))
                resetGame();
        }
    }

    void World::update(float deltaTime)
    {
        if (gameOver_ || !gameStarted_)
            return;

        joueur_->update(deltaTime);
        if (formation_)
            formation_->update(deltaTime);

        // Ajustement de vitesse selon la vague
        if (currentWave_ == 1) speedMultiplier_ = 1.f;
        else if (currentWave_ == 2) speedMultiplier_ = 1.1f;
        else if (currentWave_ == 3) speedMultiplier_ = 1.2f;
        else if (currentWave_ == 4) speedMultiplier_ = 1.1f;
        else speedMultiplier_ = 0.9f;

        if (formation_)
            formation_->setSpeedMultiplier(speedMultiplier_);

        handleCollisions();

        // Si un ennemi touche le bas de l’écran → Game Over
        if (formation_)
        {
            auto& npcs = formation_->getNPCs();
            for (auto& npc : npcs)
            {
                float bottom = npc->getGlobalBounds().position.y + npc->getGlobalBounds().size.y;
                if (bottom >= window_.getSize().y - 50.f)
                {
                    gameOver_ = true;
                    break;
                }
            }
        }

        // Mise à jour de la vie du joueur
        int vie = static_cast<int>(joueur_->getVie());
        vieText_->setString("Vie : " + to_string(vie));
        float ratio = vie / 100.f;
        vieBar_.setSize({ 150.f * ratio, 20.f });
        vieBar_.setFillColor(ratio > 0.3f ? Color::Green : Color::Red);

        if (joueur_->getVie() <= 0.f)
            gameOver_ = true;

        // --- Transition de vague ---
        if (formation_ && formation_->getNPCs().empty() && !gameOver_)
        {
            currentWave_++;

            if (currentWave_ == 2) showWaveMessage("Attention ! votre combats à attiré une \n flotte ennemi");
            else if (currentWave_ == 3) showWaveMessage("Un des vaisseaux s'est échappé et \n est allé chercher des renforts");
            else if (currentWave_ == 4) showWaveMessage("Les troupes d'élite ont rejoint le combat");
            else if (currentWave_ == 5) showWaveMessage("Le seigneur Vador en personne s'est déplacé \n courage, Vous avez presque réussi votre mission \n que la force soit avec vous !");
            else if (currentWave_ > 5)
            {
                gameOver_ = true;
                gameOverText_->setString("VICTOIRE ! \n Vous l'avez fait !!! La galaxie est fière de vous ! \n\nAppuyez sur R pour rejouer");
            }

            if (!gameOver_)
                loadWave(currentWave_);

            waveText_->setString("Vague : " + to_string(currentWave_));
        }
    }

    void World::loadWave(int wave)
    {
        formation_.reset();

        switch (wave)
        {
        case 1:
            formation_ = make_unique<Formation>(8, 3, Vector2f(100.f, 50.f), 80.f, 60.f);
            break;
        case 2:
            formation_ = make_unique<Formation>(7, 2, Vector2f(80.f, 50.f), 70.f, 60.f);
            formation_->getNPCs().push_back(make_unique<Enemy2>(Vector2f(400.f, 50.f)));
            break;
        case 3:
        {
            // --- Création de la formation principale ---
            formation_ = make_unique<Formation>(6, 2, Vector2f(100.f, 80.f), 80.f, 55.f);

            // --- Calcule les bornes horizontales de la formation ---
            auto& npcs = formation_->getNPCs();
            float minX = FLT_MAX, maxX = -FLT_MAX;

            for (auto& npc : npcs)
            {
                FloatRect bounds = npc->getGlobalBounds();
                minX = std::min(minX, bounds.position.x);
                maxX = std::max(maxX, bounds.position.x + bounds.size.x);
            }

            float formationCenterX = (minX + maxX) / 2.f;

            // --- Ajoute 3 Enemy2 centrés par rapport à la formation ---
            const int enemyCount = 3;
            const float spacing = 200.f;
            float totalWidth = (enemyCount - 1) * spacing;
            float startX = formationCenterX - totalWidth / 2.2f;
            float yPos = 40.f; // hauteur ajustée au-dessus des NPC

            for (int i = 0; i < enemyCount; ++i)
                npcs.push_back(make_unique<Enemy2>(Vector2f(startX + i * spacing, yPos)));

            break;
        }



        case 4:
            formation_ = make_unique<Formation>(8, 1, Vector2f(100.f, 80.f), 80.f, 55.f);
            formation_->getNPCs().clear();
            for (int i = 0; i < 8; ++i)
                formation_->getNPCs().push_back(make_unique<Enemy2>(Vector2f(100.f + i * 80.f, 100.f)));
            break;
        case 5:
        {
            // --- Création de la formation principale (Enemy2) ---
            // 4 colonnes, 1 ligne, espacés horizontalement
            const int cols = 4;
            const int rows = 1;
            const float spacingX = 200.f;
            const float spacingY = 55.f;

            // position de départ : légèrement plus bas qu’avant
            formation_ = make_unique<Formation>(cols, rows, sf::Vector2f(100.f, 180.f), spacingX, spacingY);
            auto& npcs = formation_->getNPCs();

            // --- Calcule les bornes horizontales pour centrer le boss ---
            float minX = std::numeric_limits<float>::infinity();
            float maxX = -std::numeric_limits<float>::infinity();
            float minY = std::numeric_limits<float>::infinity();

            for (auto& npc : npcs)
            {
                sf::FloatRect b = npc->getGlobalBounds();
                minX = std::min(minX, b.position.x);
                maxX = std::max(maxX, b.position.x + b.size.x);
                minY = std::min(minY, b.position.y);
            }

            float formationCenterX = (minX + maxX) * 0.5f;

            // --- Placement du boss ---
            const float bossVerticalOffset = 140.f; // hauteur ajustée : plus bas que ta version précédente
            float bossY = minY - bossVerticalOffset;

            npcs.push_back(std::make_unique<Enemy2>(sf::Vector2f(minX, minY)));
            npcs.push_back(std::make_unique<Enemy2>(sf::Vector2f(minX + spacingX, minY)));
            npcs.push_back(std::make_unique<Enemy2>(sf::Vector2f(minX + 2 * spacingX, minY)));
            npcs.push_back(std::make_unique<Enemy2>(sf::Vector2f(minX + 3 * spacingX, minY)));

            // boss centré sur la formation
            npcs.push_back(std::make_unique<Boss>(sf::Vector2f(formationCenterX, bossY)));

            break;
        }

        default:
            formation_ = make_unique<Formation>(8, 3, Vector2f(100.f, 50.f), 80.f, 60.f);
            break;
        }
    }

    void World::resetGame()
    {
        joueur_ = make_unique<Joueur>();
        formation_.reset();
        currentWave_ = 1;
        gameOver_ = false;
        introActive_ = true;
        gameStarted_ = false;

        if (waveText_)
            waveText_->setString("Vague : 1");
        if (vieText_)
            vieText_->setString("Vie : 100");

        showIntro();
    }

    void World::render()
    {
        window_.clear(Color::Black);

        if (formation_)
            formation_->draw(window_);
        joueur_->draw(window_);

        window_.draw(vieBarBackground_);
        window_.draw(vieBar_);
        window_.draw(*vieText_);
        window_.draw(*waveText_);

        if (gameOver_)
            window_.draw(*gameOverText_);

        window_.display();
    }

    void World::handleCollisions()
    {
        if (!formation_) return;

        auto& tirsJoueur = joueur_->getArme().getProjectiles();
        auto& npcs = formation_->getNPCs();

        for (auto it = tirsJoueur.begin(); it != tirsJoueur.end();)
        {
            bool hit = false;
            for (auto& npc : npcs)
            {
                if (checkCollision(it->getGlobalBounds(), npc->getGlobalBounds()))
                {
                    npc->setVie(npc->getVie() - joueur_->getDegats());
                    it = tirsJoueur.erase(it);
                    hit = true;
                    break;
                }
            }
            if (!hit) ++it;
        }

        npcs.erase(remove_if(npcs.begin(), npcs.end(),
            [](const unique_ptr<NPC>& n) { return n->getVie() <= 0.f; }),
            npcs.end());

        for (auto& npc : npcs)
        {
            auto& tirsNPC = npc->getArme().getProjectiles();
            for (auto it = tirsNPC.begin(); it != tirsNPC.end();)
            {
                if (checkCollision(it->getGlobalBounds(), joueur_->getGlobalBounds()))
                {
                    joueur_->setVie(joueur_->getVie() - npc->getDegats());
                    it = tirsNPC.erase(it);
                }
                else
                    ++it;
            }
        }

        for (auto& npc : npcs)
        {
            if (checkCollision(joueur_->getGlobalBounds(), npc->getGlobalBounds()))
            {
                joueur_->setVie(0.f);
                gameOver_ = true;
                return;
            }
        }
    }

    bool World::checkCollision(const FloatRect& a, const FloatRect& b)
    {
        Vector2f aMin = a.position;
        Vector2f aMax = a.position + a.size;
        Vector2f bMin = b.position;
        Vector2f bMax = b.position + b.size;

        return (aMin.x < bMax.x && aMax.x > bMin.x &&
            aMin.y < bMax.y && aMax.y > bMin.y);
    }
}

