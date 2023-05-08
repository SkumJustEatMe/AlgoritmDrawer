#include <cstdlib>
#include <queue>
#include <SFML/Graphics.hpp>
#include <thread>
#include <stack>
#include <algorithm>

const int ROWS = 50;
const int COLUMNS = 50;
sf::Vector2i mousePosition;
int startTileX = 0;
int startTileY = 0;
int endTileX = 0;
int endTileY = 0;

struct Node {
    int x, y;
    bool visited = false;
    std::vector<Node*> neighbors;
    Node* parent;

    Node() : x(0), y(0), visited(false), parent(nullptr) {}
    Node(int x, int y) : x(x), y(y), visited(false), parent(nullptr) {}
};

Node nodeGrid[ROWS][COLUMNS];

void createGraph();
void bfs(Node* start, Node* end, sf::RenderWindow& window, sf::RectangleShape grid[][COLUMNS]);
void initGrid(sf::RectangleShape grid[][COLUMNS]);
void drawGrid(sf::RenderWindow& window, sf::RectangleShape grid[][COLUMNS]);
void randomMaze(sf::RenderWindow& window, sf::RectangleShape grid[][COLUMNS]);

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 800), "Algorithm Drawer");
    sf::RectangleShape grid[ROWS][COLUMNS];

    initGrid(grid);

    while (window.isOpen())
    {
        sf::Event event = sf::Event();
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
                        initGrid(grid);
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
                    case sf::Keyboard::F2:
                        randomMaze(window, grid);
                        break;
                    case sf::Keyboard::F1:
                        Node* start = &nodeGrid[startTileX][startTileY];
                        Node* end = &nodeGrid[endTileX][endTileY];
                        bfs(start, end, window, grid);
                }
            }

           if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Right){
                mousePosition = sf::Mouse::getPosition(window);
                int tileX = mousePosition.x/16;
                int tileY = mousePosition.y/16;
                grid[tileX][tileY].setFillColor(sf::Color::Black);
           }
           else if (event.type == sf::Event::MouseMoved && sf::Mouse::isButtonPressed(sf::Mouse::Right)){
                mousePosition = sf::Mouse::getPosition(window);
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

void drawGrid(sf::RenderWindow& window, sf::RectangleShape grid[][COLUMNS]){
    for (int i = 0; i < ROWS; i++)
    {
        for (int j = 0; j < COLUMNS; j++)
        {
            window.draw(grid[i][j]);
        }
    }
}

void initGrid(sf::RectangleShape grid[][COLUMNS]){

    for (int i = 0; i < ROWS; i++)
    {
        for (int j = 0; j < COLUMNS; j++)
        {
            grid[i][j].setPosition(sf::Vector2f(16.0f * i, 16.0f * j));
            grid[i][j].setSize(sf::Vector2f(15.0f, 15.0f));
            if (i == 0 || j == 0 || i == ROWS - 1 || j == COLUMNS - 1){
                grid[i][j].setFillColor(sf::Color::Black);
            } else{
                grid[i][j].setFillColor(sf::Color::White);
            }
        }
    }
}

void createGraph() {
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLUMNS; j++) {
            nodeGrid[i][j] = Node(i, j);

            if (i > 0) {
                nodeGrid[i][j].neighbors.push_back(&nodeGrid[i - 1][j]);
            }
            if (j > 0) {
                nodeGrid[i][j].neighbors.push_back(&nodeGrid[i][j - 1]);
            }
            if (i < ROWS - 1) {
                nodeGrid[i][j].neighbors.push_back(&nodeGrid[i + 1][j]);
            }
            if (j < COLUMNS - 1) {
                nodeGrid[i][j].neighbors.push_back(&nodeGrid[i][j + 1]);
            }
        }
    }
}

void bfs(Node* start, Node* end, sf::RenderWindow& window, sf::RectangleShape grid[][COLUMNS]) {
    createGraph();
    std::queue<Node*> q;
    q.push(start);

    while (!q.empty()) {
        Node* current = q.front();
        q.pop();

        if(grid[current->x][current->y].getFillColor() != sf::Color::Black){
            if (current == end) {
                std::vector<Node*> path;
                for (Node* node = end; node != nullptr; node = node->parent) {
                    path.push_back(node);
                }
                std::reverse(path.begin(), path.end());

                for (Node* node : path) {
                    grid[node->x][node->y].setFillColor(sf::Color::Yellow);
                    window.draw(grid[node->x][node->y]);
                }
                window.display();

                return;
            }

            if (current->visited) {
                continue;
            }
            current->visited = true;

            if(current != start){
                grid[current->x][current->y].setFillColor(sf::Color::Blue);
                window.draw(grid[current->x][current->y]);
                window.display();
            }

            for (Node* neighbor : current->neighbors) {
                if (!neighbor->visited) {
                    neighbor->parent = current;
                    q.push(neighbor);
                }
            }
        }
    }
}

void randomMaze(sf::RenderWindow& window, sf::RectangleShape grid[][COLUMNS]){
    createGraph();
    std::stack<Node*> s;
    int randomX = rand() % COLUMNS;
    int randomY = rand() % ROWS;
    Node* startNode = &nodeGrid[randomX][randomY];
    startNode->visited = true;
    s.push(startNode);

    while (!s.empty()){
        Node* current = s.top();
        s.pop();

        if(grid[current->x][current->y].getFillColor() != sf::Color::Black){
            grid[current->x][current->y].setFillColor(sf::Color::Black);
            window.draw(grid[current->x][current->y]);
            window.display();
        }

        std::vector<Node*> unvisitedNeighbors;
        for (Node* neighbor : current->neighbors) {
            if (!neighbor->visited) {
                // Check if neighbor is two steps away and in the same direction as the parent
                if (current->parent && neighbor->x == current->parent->x + (current->x - current->parent->x) * 2 &&
                    neighbor->y == current->parent->y + (current->y - current->parent->y) * 2)
                {
                    // Skip coloring this neighbor to create a wider path
                    continue;
                }
                unvisitedNeighbors.push_back(neighbor);
            }
        }

        if (!unvisitedNeighbors.empty()) {
            int randomIndex = std::rand() % unvisitedNeighbors.size();
            Node* randomNeighbor = unvisitedNeighbors[randomIndex];

            randomNeighbor->visited = true;
            randomNeighbor->parent = current;

            s.push(current);
            s.push(randomNeighbor);
        }
    }
}