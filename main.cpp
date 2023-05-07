#include <iostream>
#include <SFML/Graphics.hpp>

const int ROWS = 50;
const int COLUMS = 50;

void initGrid(sf::RenderWindow& window, sf::RectangleShape grid[][COLUMS]);
void drawGrid(sf::RenderWindow& window, sf::RectangleShape grid[][COLUMS]);
void drawTiles(sf::RenderWindow& window, sf::RectangleShape tile);

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 800), "Algo");
    sf::RectangleShape grid[ROWS][COLUMS];

    initGrid(window, grid);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {

            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape){
                window.close();
            }
            if (event.type == sf::Event::MouseButtonPressed){
                if ( event.mouseButton.button == sf::Mouse::Right){
                    sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
                    grid[mousePosition.x/16][mousePosition.y/16].setFillColor(sf::Color::Black);
                    std::cout << mousePosition.x/15 << "\t" << mousePosition.y/15 << "\n";

                }
            }
        }

        window.clear();
        drawGrid(window, grid);
        window.display();
    }

    return 0;
}

void drawGrid(sf::RenderWindow& window, sf::RectangleShape grid[][COLUMS]){
    for (int i = 0; i < ROWS; i++)
    {
        for (int j = 0; j < COLUMS; j++)
        {
            window.draw(grid[i][j]);
        }
    }
}

void initGrid(sf::RenderWindow& window, sf::RectangleShape grid[][COLUMS]){

    for (int i = 0; i < ROWS; i++)
    {
        for (int j = 0; j < COLUMS; j++)
        {
            grid[i][j].setPosition(sf::Vector2f(16.0f * i, 16.0f * j));
            grid[i][j].setSize(sf::Vector2f(15.0f, 15.0f));
            grid[i][j].setFillColor(sf::Color::White);
        }
    }
}

void drawTiles(sf::RenderWindow& window, sf::RectangleShape tile){
    tile.setFillColor(sf::Color::Black);
}

