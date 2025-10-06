#include <iostream>
#include <SFML/Graphics.hpp>

class Ground {
    public:
        double x {215.f};
        double x2 {648.f};
        double y {686.0f};
        double scaleX {1.3f};
        double scaleY {1.3f};
        double dir {0.0f};
        double speed {150};
        sf::Texture groundTexture;
        sf::Sprite groundSprite;
        sf::Sprite groundSprite2;
        float width {};

    void load() {
        if (!groundTexture.loadFromFile("./Assets/Images/base.png")) {
            std::cerr << "Error Loading Image";
        }
        groundSprite.setTexture(groundTexture);
        groundSprite.setPosition(x, y);
        groundSprite.setScale(scaleX, scaleY);
        groundSprite.setRotation(dir);
        groundSprite.setOrigin(groundTexture.getSize().x / 2.f, groundTexture.getSize().y / 2.f);
        groundSprite2.setTexture(groundTexture);
        groundSprite2.setPosition(x2, y);
        groundSprite2.setScale(scaleX, scaleY);
        groundSprite2.setRotation(dir);
        groundSprite2.setOrigin(groundTexture.getSize().x / 2.f, groundTexture.getSize().y / 2.f);
        width = groundTexture.getSize().x * scaleX;
    }

    void draw(sf::RenderWindow &window) {
        groundSprite.setPosition(x, y);
        groundSprite.setRotation(dir);
        window.draw(groundSprite);
        groundSprite2.setPosition(x2, y);
        groundSprite2.setRotation(dir);
        window.draw(groundSprite2);
    }

    void move(float dtSeconds) {
        x -= speed * dtSeconds;
        x2 -= speed * dtSeconds;
        if (x <= -width / 2.f) {
            x = 648;
        }
        if (x2 <= -width / 2.f) {
            x2 = 648;
        }
    }
    void collision(sf::Sprite birdSprite, bool &dead, bool &groundDead) {
        if (groundSprite.getGlobalBounds().intersects(birdSprite.getGlobalBounds())) {
            dead = true;
            groundDead = true;
        }
        if (groundSprite2.getGlobalBounds().intersects(birdSprite.getGlobalBounds())) {
            dead = true;
            groundDead = true;
        }
    }

    void restart() {
        x = 215;
        x2 = 648;
        dir = 0;
    }
};
