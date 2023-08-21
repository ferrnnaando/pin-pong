#include <iostream>
#include <SFML/Graphics.hpp>


int contador_blue = 0;
int contador_red = 0;
std::string WindowTitle = "Pin pong | @ferrnnaando";

int main() {
    sf::RenderWindow window(sf::VideoMode(250, 500), WindowTitle, sf::Style::Titlebar | sf::Style::Close);
    window.setFramerateLimit(60);

    sf::Vertex line_wirefence[] = {
        sf::Vertex(sf::Vector2f(0, (float)window.getSize().y / 2)),
        sf::Vertex(sf::Vector2f(0, (float)window.getSize().y / 2))
    };

    sf::RectangleShape own_space;
    sf::RectangleShape opponent_space;
    own_space.setSize(sf::Vector2f((float)window.getSize().x, (float)window.getSize().y / 2));
    own_space.setPosition(sf::Vector2f(0, 0));
    own_space.setFillColor(sf::Color::Blue);
    opponent_space.setSize(sf::Vector2f((float)window.getSize().x, (float)window.getSize().y / 2));
    opponent_space.setPosition(sf::Vector2f(0, (float)window.getSize().y / 2));
    opponent_space.setFillColor(sf::Color::Red);

    sf::Texture paddle;
    if(!paddle.loadFromFile("required/images/paddle.png")) {
        return -1;
    }

    sf::Sprite paddle_sprite(paddle);
    paddle_sprite.setPosition(sf::Vector2f((float)window.getSize().x / 2, 80/*<3*/));
    paddle_sprite.setOrigin(
        (float)paddle.getSize().x/2, 
        (float)paddle.getSize().y/2
    );
    paddle_sprite.setScale(
        60.0f / paddle.getSize().x,
        60.0f / paddle.getSize().y
    );
    paddle_sprite.setRotation(-90);

    sf::Sprite paddle2_sprite(paddle);
    paddle2_sprite.setPosition(sf::Vector2f((float)window.getSize().x / 2, (float)window.getSize().y - 80));
    paddle2_sprite.setScale(
        60.0f / paddle.getSize().x,
        60.0f / paddle.getSize().y
    );
    paddle2_sprite.setOrigin(
        (float)paddle.getSize().x/2,
        (float)paddle.getSize().y
    );
    paddle2_sprite.setRotation(70);

    sf::Texture ball_texture;
    if(!ball_texture.loadFromFile("required/images/ball.png")) {
        return -1;
    }

    float paddle2_fastX = -1;
    float paddle2_fastY = -1;
    float ball_fastX = -1;
    float ball_fastY = -7.0;

    sf::Sprite ball_sprite(ball_texture);
    ball_sprite.setScale(
        20.0f / ball_texture.getSize().x,
        20.0f / ball_texture.getSize().y
    );

    ball_sprite.setOrigin((float)ball_texture.getSize().x / 2, (float)ball_texture.getSize().y / 2);
    ball_sprite.setPosition(80, 300);

    while(window.isOpen()) {
        sf::Event event;
        while(window.pollEvent(event)) {
            if(event.type == sf::Event::Closed) {
                window.close();
            }
        }
        /*//Colisiones
        if((paddle_sprite.getGlobalBounds().contains((float)ball_sprite.getPosition().x, (float)ball_sprite.getPosition().y))
        || (paddle2_sprite.getGlobalBounds().contains((float)ball_sprite.getPosition().x, (float)ball_sprite.getPosition().y))) {
            ball_fastY *= -1;
        } 
        else if(ball_sprite.getPosition().y > window.getSize().y - 50) {
            contador_red++;
            ball_fastY *= -1;
        }
        else if(ball_sprite.getPosition().y < 0) {
            contador_blue++;
            ball_fastY *= -1;
        }
*/
        ball_sprite.move(ball_fastX, ball_fastY);
        //Cambia la dirección de la pelota cuando se acerca a uno de los topes del programa, evitando que desaparezca y haciendo un efecto de falso rebote
        if(ball_sprite.getPosition().x >= window.getSize().x || ball_sprite.getPosition().x <= 5) {
            ball_fastX *= -1;
        }
        if(ball_sprite.getPosition().y >= window.getSize().y || ball_sprite.getPosition().y <= -5) {
            ball_fastY *= -1;
            ball_sprite.setPosition(sf::Vector2f(rand() % 250, window.getSize().y / 2));
        }

        //Manejo de palas para el jugador local
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && paddle_sprite.getPosition().x > 25) {
            paddle_sprite.move(-4, 0);
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && paddle_sprite.getPosition().x < 230) {
            paddle_sprite.move(4, 0);
        }

        //Manejo de palas para el jugador regional
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::A) && paddle2_sprite.getPosition().x >= -15) {
            paddle2_sprite.move(-4, 0);
        }

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::D) && paddle2_sprite.getPosition().x < 190) {
            paddle2_sprite.move(4, 0);
        }
 
        window.clear();

        window.draw(own_space);
        window.draw(opponent_space);
        window.draw(line_wirefence, 2, sf::Lines);
        window.draw(ball_sprite);

        window.draw(paddle_sprite);
        window.draw(paddle2_sprite);

        window.display();
    }
}