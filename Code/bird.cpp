#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

class Bird {
    public:
        double x {80.0f};
        double y {270.0f};
        double velocityY {0.0f};
        double scaleX {1.5f};
        double scaleY {1.5f};
        double dir {0.0f};
        double rotationSpeed {300.f};
        int frame {1};
        int jumpPower {5};
        int fallSpeed {15};
        bool canRotate {true};
        bool alreadyDead {false};
        bool dead {false};
        bool groundDead {false};
        bool start {false};
        sf::Texture birdTextureMiddle;
        sf::Texture birdTextureDown;
        sf::Texture birdTextureUp;
        sf::Sprite birdSprite;
        sf::SoundBuffer buffer;
        sf::Sound dieSound;
        sf::SoundBuffer jumpBuffer;
        sf::Sound jumpSound;
        float amplitude = 30.0f;
        float speed = 0.4f;
        float baseY = 270.0f;

    void load() {
        if (!birdTextureMiddle.loadFromFile("./Assets/Images/yellowbird-midflap.png")) {
            std::cerr << "Error Loading Image";
        }
        if (!birdTextureDown.loadFromFile("./Assets/Images/yellowbird-downflap.png")) {
            std::cerr << "Error Loading Image";
        }
        if (!birdTextureUp.loadFromFile("./Assets/Images/yellowbird-upflap.png")) {
            std::cerr << "Error Loading Image";
        }
        birdSprite.setTexture(birdTextureMiddle);
        birdSprite.setPosition(x, y);
        birdSprite.setScale(scaleX, scaleY);
        birdSprite.setRotation(dir);
        birdSprite.setOrigin(birdTextureMiddle.getSize().x / 2.f, birdTextureMiddle.getSize().y / 2.f);
        if (!buffer.loadFromFile("./Assets/Audio/hit.wav")) {
            std::cerr << "Error loading Sound";
        }
        dieSound.setBuffer(buffer);
        if (!jumpBuffer.loadFromFile("./Assets/Audio/wing.wav")) {
            std::cerr << "Error loading Sound";
        }
        jumpSound.setBuffer(jumpBuffer);
    }

    void idle(sf::Clock &clock) {
        float elapsed = clock.getElapsedTime().asSeconds();
        y = baseY + amplitude * std::sin(speed * elapsed * 2 * 3.14159f);
    }

    void startBird() {
        start = true;
    }

    void draw(sf::RenderWindow &window) {
        birdSprite.setPosition(x, y);
        birdSprite.setRotation(dir);
        window.draw(birdSprite);
    }

    void move(float dtSeconds) {
        if (!groundDead) {
            velocityY += fallSpeed * dtSeconds;
            y += velocityY;
        }
    }

    void animation(sf::Clock &animationClock) {
        float elapsed = animationClock.getElapsedTime().asSeconds();
        if (elapsed >= 0.25) {
            if (frame < 4) {
                frame += 1;
            } else {
                frame = 1;
            }
            animationClock.restart();
        }
        if (frame == 1) {
            birdSprite.setTexture(birdTextureMiddle);
        } else if (frame == 2) {
            birdSprite.setTexture(birdTextureUp);
        } else if (frame == 3) {
            birdSprite.setTexture(birdTextureDown);
        } else if (frame == 4) {
            birdSprite.setTexture(birdTextureMiddle);
        }
    }

    void jump(sf::Clock &clock) {
        if (!dead) {
            velocityY = -jumpPower;
            canRotate = false;
            dir = -40;
            clock.restart();
            jumpSound.play();
        }
    }

    void rotate(float dtSeconds, sf::Clock &clock) {
        if (!dead) {
            float elapsed = clock.getElapsedTime().asSeconds();
            if (!canRotate) {
                if (elapsed >= 0.35) {
                    canRotate = true;
                    clock.restart();
                }
            }
        } else {
            canRotate = true;
        }
        if (dir < 90 && canRotate) {
            dir += rotationSpeed * dtSeconds;
        }
    }

    void die() {
        if (dead && !alreadyDead) {
            alreadyDead = true;
            dieSound.play();
        }
    }

    void restart() {
        x = 80;
        y = 270;
        velocityY = 0;
        dir = 0;
        canRotate = true;
        alreadyDead = false;
        dead = false;
        groundDead = false;
        start = false;
        birdSprite.setTexture(birdTextureMiddle);
        frame = 1;
    }
};
