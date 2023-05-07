#include <iostream>
#include <SFML/Graphics.hpp>

const int ROWS = 50;
const int COLUMS = 50;
sf::Vector2i mousePosition;
int startTileX = 0;
int startTileY = 0;
int endTileX = 0;
int endTileY = 0;

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
            else if (event.type == sf::Event::KeyPressed){
                switch (event.key.code) {
                    case sf::Keyboard::Escape:
                        window.close();
                        break;
                    case sf::Keyboard::Space:
                        initGrid(window, grid);
                        break;
                    case sf::Keyboard::Num1:
                        mousePosition = sf::Mouse::getPosition(window);
                        startTileX = mousePosition.x/16;
                        startTileY = mousePosition.y/16;
                        grid[startTileX][startTileY].setFillColor(sf::Color::Green);
                        break;
                    case sf::Keyboard::Num2:
                        mousePosition = sf::Mouse::getPosition(window);
                        endTileX = mousePosition.x/16;
                        endTileY = mousePosition.y/16;
                        grid[endTileX][endTileY].setFillColor(sf::Color::Red);
                        break;
                }
            }

           else if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Right){
                sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
                int tileX = mousePosition.x/16;
                int tileY = mousePosition.y/16;
                grid[tileX][tileY].setFillColor(sf::Color::Black);
           }
           else if (event.type == sf::Event::MouseMoved && sf::Mouse::isButtonPressed(sf::Mouse::Right)){
                sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
                int tileX = mousePosition.x/16;
                int tileY = mousePosition.y/16;
                grid[tileX][tileY].setFillColor(sf::Color::Black);
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

//std::cout << mousePosition.x/15 << "\t" << mousePosition.y/15 << "\n";