#include <SFML/Graphics.hpp>

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;
const float INITITAL_SPEED = 100.f;
const float PLAYER_SIZE = 20.f;
const float ACCELERATION = 20.f;
const int NUM_APPLES = 20;
const float APPLE_SIZE = 20.f;

struct Vector2D
{
    float x = 0;
    float y = 0;
};

enum class PlayerDirection {
    Right = 0,
    Up,
    Left,
    Down
};

typedef Vector2D Position2D;

Position2D playerPosition = {SCREEN_WIDTH / 2.f, SCREEN_HEIGHT / 2.f };
// Player Start Position
static float playerSpeed = INITITAL_SPEED;
PlayerDirection playerDirection = PlayerDirection::Right;
static sf::RectangleShape playerShape;

// Init Apples
Position2D applePosition[NUM_APPLES];
static bool isApppleEaten[NUM_APPLES];
static sf::CircleShape appleShape[NUM_APPLES];

bool isRunning = false;

sf::Clock gameClock;
float lastTime = gameClock.getElapsedTime().asSeconds();
// Calculate DeltaTime
float currentTime = gameClock.getElapsedTime().asSeconds();
float deltaTime = currentTime - lastTime;

void createPlayer()
{
    playerPosition.x = SCREEN_WIDTH / 2.f;
    playerPosition.y = SCREEN_HEIGHT / 2.f;
    playerSpeed = INITITAL_SPEED;

    // Player
    playerShape.setSize(sf::Vector2f(PLAYER_SIZE, PLAYER_SIZE));
    playerShape.setFillColor(sf::Color::Red);
    playerShape.setOrigin(PLAYER_SIZE / 2.f, PLAYER_SIZE / 2.f);
    playerShape.setPosition(playerPosition.x, playerPosition.y);
}

void addAppleShape(int i)
{
    isApppleEaten[i] = false;
    applePosition[i].x = rand() / (float)RAND_MAX * SCREEN_WIDTH;
    applePosition[i].y = rand() / (float)RAND_MAX * SCREEN_HEIGHT;

    appleShape[i].setRadius(APPLE_SIZE / 2.f);
    appleShape[i].setFillColor(sf::Color::Green);
    appleShape[i].setOrigin(APPLE_SIZE / 2.f, APPLE_SIZE / 2.f);
    appleShape[i].setPosition(applePosition[i].x, applePosition[i].y);
}

void createApples()
{
    for (int i = 0; i < NUM_APPLES; ++i)
    {
        addAppleShape(i);
    }
}


void keyBinding()
{
    // KeyBinding
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
    {
        playerDirection = PlayerDirection::Right;
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
    {
        playerDirection = PlayerDirection::Up;
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
    {
        playerDirection = PlayerDirection::Left;
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
    {
        playerDirection = PlayerDirection::Down;
    }
}

void playerMovement()
{


    currentTime = gameClock.getElapsedTime().asSeconds();
    deltaTime = currentTime - lastTime;
    lastTime = currentTime;

    switch (playerDirection)
    {
    case PlayerDirection::Right:
    {
        playerPosition.x += playerSpeed * deltaTime;
        break;
    }
    case PlayerDirection::Up:
    {
        playerPosition.y -= playerSpeed * deltaTime;
        break;
    }
    case PlayerDirection::Left:
    {
        playerPosition.x -= playerSpeed * deltaTime;
        break;
    }
    case PlayerDirection::Down:
    {
        playerPosition.y += playerSpeed * deltaTime;
        break;
    }
    }
}

int main()
{
    int seed = (int)time(nullptr);
    srand(seed);

    sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Apples Game!");


    int numEatenApples = 0;





    // Main Cicle
    while (window.isOpen())
    {
        isRunning = true;

        createPlayer();

        createApples();



        while (isRunning)
        {

            sf::Event event;
            while (window.pollEvent(event))
            {
                if (event.type == sf::Event::Closed)
                    window.close();
            }


            keyBinding();

            playerMovement();



            // Border Collision
            if (playerPosition.x - PLAYER_SIZE / 2.f < 0.f || playerPosition.x + PLAYER_SIZE / 2.f > SCREEN_WIDTH ||
                playerPosition.y - PLAYER_SIZE / 2.f < 0.f || playerPosition.y + PLAYER_SIZE / 2.f > SCREEN_HEIGHT)
            {

                sf::Time wait = sf::milliseconds(900);
                playerSpeed = 0;
                sf::sleep(wait);
                isRunning = false;
                break;
            }


            for (int i = 0; i < NUM_APPLES; ++i)
            {
                if (!isApppleEaten[i])
                {
                    /*
                    float dx = fabs(playerPosition.x - applePosition[i].x[i]);
                    float dy = fabs(playerPosition.y - applePosition[i].y[i]);
                    if (dx <= (APPLE_SIZE + PLAYER_SIZE) / 2.f &&
                        dy <= APPLE_SIZE + PLAYER_SIZE / 2.f)
                    {
                        isApppleEaten[i] = true;
                        ++numEatenApples;
                    }
                    */
                    float squareDistance = (playerPosition.x - applePosition[i].x) * (playerPosition.x - applePosition[i].x) +
                        (playerPosition.y - applePosition[i].y) * (playerPosition.y - applePosition[i].y);
                    float squareRadiusSum = (APPLE_SIZE + PLAYER_SIZE) * (APPLE_SIZE + PLAYER_SIZE) / 4;
                    if (squareDistance <= squareRadiusSum)
                    {
                        isApppleEaten[i] = true;
                        ++numEatenApples;

                        addAppleShape(i);
                        playerSpeed += ACCELERATION;

                    

                    }
                }
            }

            window.clear();
            playerShape.setPosition(playerPosition.x, playerPosition.y);
            for (int i = 0; i < NUM_APPLES; ++i)
            {
                if (!isApppleEaten[i])
                {
                    window.draw(appleShape[i]);
                }
            }
            window.draw(playerShape);
            window.display();
        }
    }

    return 0;
}
