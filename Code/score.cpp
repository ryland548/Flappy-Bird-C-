#include <iostream>
#include <SFML/Graphics.hpp>

class Score {
    public:
        int x {195};
        int y {-20};
        int fontSize {140};
        sf::Font font;
        sf::Text text;

    void load() {
        if (!font.loadFromFile("./Assets/Fonts/FlappyBird.ttf")) {
            std::cerr << "Error loading Font";
        }
        text.setFont(font);
        text.setString("0");
        text.setCharacterSize(fontSize);
        text.setFillColor(sf::Color::White);
        text.setPosition(x, y);
    }

    void draw(sf::RenderWindow &window, int scoreNumber) {
        if (scoreNumber >= 10) {
            x = 165;
            text.setPosition(x, y);
        } else {
            x = 195;
        }
        text.setString(std::to_string(scoreNumber));
        window.draw(text);
    }
};
