#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "./Code/bird.cpp"
#include "./Code/bg.cpp"
#include "./Code/ground.cpp"
#include "./Code/pipe.cpp"
#include "./Code/score.cpp"
#include "./Code/startmessage.cpp"
#include "./Code/gameover.cpp"

using std::cout;

void restart(Bird &bird, std::vector<Pipe> &pipes, int &scoreNumber, Ground &ground, GameOverMessage &gameOver) {
    bird.restart();
    pipes = {};
    for (unsigned long i = 0; i < 3; i++) {
        Pipe pipe = Pipe();
        pipe.x = 700 + i * 280;
        pipes.push_back(pipe);
    }
    scoreNumber = 0;
    ground.restart();
    gameOver.restart();
}

int main() {
    int scoreNumber {0};
    Bird bird = Bird();
    bird.load();
    Background background = Background();
    background.load();
    Ground ground = Ground();
    ground.load();
    std::vector<Pipe> pipes;
    Score score = Score();
    score.load();
    sf::RenderWindow window(sf::VideoMode(432, 758), "Flappy Bird");
    StartMessage startMessage = StartMessage();
    startMessage.load();
    GameOverMessage gameOver = GameOverMessage();
    gameOver.load();
    window.setVerticalSyncEnabled(true);
    sf::Clock deltaClock;
    sf::Clock clock;
    sf::Clock birdAnimationClock;
    for (unsigned long i = 0; i < 3; i++) {
        Pipe pipe = Pipe();
        pipe.x = 700 + i * 280;
        pipes.push_back(pipe);
    }
    while (window.isOpen()) {
        sf::Time deltaTime = deltaClock.restart();
        float dtSeconds = deltaTime.asSeconds();
        sf::Event event;
        window.clear();
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::W) {
                bird.jump(clock);
            }
            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                bird.jump(clock);
            }
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space) {
                bird.jump(clock);
            }
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::W && !bird.start) {
                bird.startBird();
            }
            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left && !bird.start) {
                bird.startBird();
            }
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space && !bird.start) {
                bird.startBird();
            }
        }
        background.draw(window);

        bird.draw(window);
        if (!bird.start) {
            bird.idle(clock);
        } else {
            bird.animation(birdAnimationClock);
            bird.move(dtSeconds);
            bird.rotate(dtSeconds, clock);
            bird.die();
        }

        if (bird.start) {
            for (Pipe &pipe : pipes) {
                if (!pipe.loaded) {
                    pipe.load();
                    pipe.spawn();
                }
                pipe.draw(window);
                if (!bird.dead) {
                    pipe.move(dtSeconds, scoreNumber);
                }
                pipe.collision(bird.birdSprite, bird.dead);
                if (pipe.x <= -150) {
                    pipe.x = 700;
                    pipe.spawn();
                }
            }
        }
        ground.draw(window);
        if (!bird.dead) {
            ground.move(dtSeconds);
        }
        ground.collision(bird.birdSprite, bird.dead, bird.groundDead);
        score.draw(window, scoreNumber);

        if (!bird.start) {
            startMessage.draw(window);
        }

        if (bird.dead) {
            gameOver.draw(window);
            if (!gameOver.animated) {
                gameOver.animation(dtSeconds);
            } else {
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::R)) {
                    restart(bird, pipes, scoreNumber, ground, gameOver);
                }
            }
        }
        window.display();
    }
    return 0;
}
