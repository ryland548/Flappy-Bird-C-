#include <iostream>
#include <SFML/Graphics.hpp>

class GameOverMessage {
    public:
        int x {216}; // 216
        int y {279 + 600};
        int targetPosY {279};
        int speed = 350;
        double scaleX {1.1};
        double scaleY {1.1};
        bool animated {false};
        int dir {0};
        sf::Texture messageTexture;
        sf::Sprite messageSprite;
        sf::Font font;
        sf::Text text;

    void load() {
        if (!messageTexture.loadFromFile("./Assets/Images/gameover.png")) {
            std::cerr << "Error Loading Image";
        }
        messageSprite.setTexture(messageTexture);
        messageSprite.setPosition(x, y);
        messageSprite.setScale(scaleX, scaleY);
        messageSprite.setRotation(dir);
        messageSprite.setOrigin(messageTexture.getSize().x / 2.f, messageTexture.getSize().y / 2.f);

        if (!font.loadFromFile("./Assets/Fonts/FlappyBird.ttf")) {
            std::cerr << "Error loading Font";
        }
        text.setFont(font);
        text.setString("Press R to Restart");
        text.setCharacterSize(40);
        text.setFillColor(sf::Color::White);
        text.setPosition(x - 120, y + 50);
    }

    void draw(sf::RenderWindow &window) {
        messageSprite.setPosition(x, y);
        text.setPosition(x - 120, y + 50);
        window.draw(messageSprite);
        window.draw(text);
    }

    void animation(float dtSeconds) {
        y -= speed * dtSeconds;
        if (y <= targetPosY) {
            animated = true;
        }
    }

    void restart() {
        x = 216;
        y = 279 + 600;
        targetPosY = 279;
        animated = false;
    }
};
