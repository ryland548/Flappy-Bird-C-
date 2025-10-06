#include <iostream>
#include <SFML/Graphics.hpp>

class Background {
    public:
        double x {216.f};
        double y {379.0f};
        double scaleX {1.5f};
        double scaleY {1.5f};
        double dir {0.0f};
        sf::Texture backgroundTexture;
        sf::Sprite backgroundSprite;

    void load() {
        if (!backgroundTexture.loadFromFile("./Assets/Images/background-day.png")) {
            std::cerr << "Error Loading Image";
        }
        backgroundSprite.setTexture(backgroundTexture);
        backgroundSprite.setPosition(x, y);
        backgroundSprite.setScale(scaleX, scaleY);
        backgroundSprite.setRotation(dir);
        backgroundSprite.setOrigin(backgroundTexture.getSize().x / 2.f, backgroundTexture.getSize().y / 2.f);
    }

    void draw(sf::RenderWindow &window) {
        backgroundSprite.setPosition(x, y);
        backgroundSprite.setRotation(dir);
        window.draw(backgroundSprite);
    }
};
