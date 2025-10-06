#include <iostream>
#include <SFML/Graphics.hpp>

class StartMessage {
    public:
        int x {216}; // 216
        int y {379};
        double scaleX {1.1};
        double scaleY {1.1};
        int dir {0};
        sf::Texture messageTexture;
        sf::Sprite messageSprite;

    void load() {
        if (!messageTexture.loadFromFile("./Assets/Images/message.png")) {
            std::cerr << "Error Loading Image";
        }
        messageSprite.setTexture(messageTexture);
        messageSprite.setPosition(x, y);
        messageSprite.setScale(scaleX, scaleY);
        messageSprite.setRotation(dir);
        messageSprite.setOrigin(messageTexture.getSize().x / 2.f, messageTexture.getSize().y / 2.f);
    }

    void draw(sf::RenderWindow &window) {
        window.draw(messageSprite);
    }
};
