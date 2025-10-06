#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <random>

class Pipe {
    public:
        double x {215.f};
        double topY {100.0f};
        double bottomY {512.8f};
        double scaleX {1.29f};
        double scaleY {1.29f};
        double dir {0.0f};
        int gap {170};
        int speed {150};
        bool loaded {false};
        float height {};
        bool soundPlayed {false};
        sf::Texture pipeTexture;
        sf::Sprite pipeSpriteTop;
        sf::Sprite pipeSpriteBottom;
        sf::SoundBuffer buffer;
        sf::Sound pointSound;

    void load() {
        loaded = true;
        if (!pipeTexture.loadFromFile("./Assets/Images/pipe.png")) {
            std::cerr << "Error Loading Image";
        }
        if (!buffer.loadFromFile("./Assets/Audio/point.wav")) {
            std::cerr << "Error loading Sound";
        }
        pointSound.setBuffer(buffer);

        pipeSpriteTop.setTexture(pipeTexture);
        pipeSpriteTop.setPosition(x, topY);
        pipeSpriteTop.setScale(scaleX, scaleY);
        pipeSpriteTop.setRotation(dir + 180);
        pipeSpriteTop.setOrigin(pipeTexture.getSize().x / 2.f, pipeTexture.getSize().y / 2.f);

        pipeSpriteBottom.setTexture(pipeTexture);
        pipeSpriteBottom.setPosition(x, bottomY);
        pipeSpriteBottom.setScale(scaleX, scaleY);
        pipeSpriteBottom.setRotation(dir);
        pipeSpriteBottom.setOrigin(pipeTexture.getSize().x / 2.f, pipeTexture.getSize().y / 2.f);

        height = pipeTexture.getSize().y * scaleY;
        bottomY = topY + height + gap;
    }

    void draw(sf::RenderWindow &window) {
        pipeSpriteTop.setPosition(x, topY);
        pipeSpriteTop.setRotation(dir + 180);

        pipeSpriteBottom.setPosition(x, bottomY);
        pipeSpriteBottom.setRotation(dir);

        window.draw(pipeSpriteTop);
        window.draw(pipeSpriteBottom);
    }

    void move(float dtSeconds, int &scoreNumber) {
        x -= speed * dtSeconds;
        if (x <= 80 && !soundPlayed) {
            pointSound.play();
            soundPlayed = true;
            scoreNumber += 1;
        }
    }

    void spawn() {
        soundPlayed = false;
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> distrib(-150, 130);
        topY = distrib(gen);;
        bottomY = topY + height + gap;
    }

    void collision(sf::Sprite birdSprite, bool &dead) {
        sf::FloatRect birdBounds = birdSprite.getGlobalBounds();
        birdBounds.left   += 20;
        birdBounds.top    += 20;
        birdBounds.width  -= 40;
        birdBounds.height -= 40;
        if (pipeSpriteTop.getGlobalBounds().intersects(birdBounds)) {
            dead = true;
        }
        if (pipeSpriteBottom.getGlobalBounds().intersects(birdBounds)) {
            dead = true;
        }
    }

    // void restart() {
    //     x = 215;
    //     topY = 100;
    //     bottomY = 512.8;
    //     dir = 0;
    //     loaded = false;
    //     height = 0;
    //     soundPlayed = false;
    // }
};
