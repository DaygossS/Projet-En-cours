#include <SFML/Graphics.hpp>

inline bool checkCollision(const sf::FloatRect& a, const sf::FloatRect& b)
{
    sf::Vector2f aMin = a.position;
    sf::Vector2f aMax = a.position + a.size;

    sf::Vector2f bMin = b.position;
    sf::Vector2f bMax = b.position + b.size;

    return (aMin.x < bMax.x && aMax.x > bMin.x &&
        aMin.y < bMax.y && aMax.y > bMin.y);
}

