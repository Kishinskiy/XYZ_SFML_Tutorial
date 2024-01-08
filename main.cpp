#include <SFML/Graphics.hpp>
#include <iostream>

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;
const float INITITAL_SPEED = 100.f;
const float PLAYER_SIZE = 20.f;
const float ACCELERATION = 20.f;
const int NUM_APPLES = 20;
const float APPLE_SIZE = 20.f;


// Player Start Position
static float playerX = SCREEN_WIDTH / 2.f;
static float playerY = SCREEN_HEIGHT / 2.f;
static float playerSpeed = INITITAL_SPEED;
static int playerDirection = 0; //0 -right, 1 - up, 2 - left, 3 - down
static sf::RectangleShape playerShape;

// Init Apples
static float appleX[NUM_APPLES];
static float appleY[NUM_APPLES];
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
    playerX = SCREEN_WIDTH / 2.f;
    playerY = SCREEN_HEIGHT / 2.f;
    playerSpeed = INITITAL_SPEED;

    // Player
    playerShape.setSize(sf::Vector2f(PLAYER_SIZE, PLAYER_SIZE));
    playerShape.setFillColor(sf::Color::Red);
    playerShape.setOrigin(PLAYER_SIZE / 2.f, PLAYER_SIZE / 2.f);
    playerShape.setPosition(playerX, playerY);
}

void addAppleShape(int i)
{
    isApppleEaten[i] = false;
    appleX[i] = rand() / (float)RAND_MAX * SCREEN_WIDTH;
    appleY[i] = rand() / (float)RAND_MAX * SCREEN_HEIGHT;

    appleShape[i].setRadius(APPLE_SIZE / 2.f);
    appleShape[i].setFillColor(sf::Color::Green);
    appleShape[i].setOrigin(APPLE_SIZE / 2.f, APPLE_SIZE / 2.f);
    appleShape[i].setPosition(appleX[i], appleY[i]);
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
        playerDirection = 0;
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
    {
        playerDirection = 1;
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
    {
        playerDirection = 2;
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
    {
        playerDirection = 3;
    }
}

void playerMovement()
{


    currentTime = gameClock.getElapsedTime().asSeconds();
    deltaTime = currentTime - lastTime;
    lastTime = currentTime;

    // Player Movement
    if (playerDirection == 0)
    {
        playerX += playerSpeed * deltaTime;
    }
    else if (playerDirection == 1)
    {
        playerY -= playerSpeed * deltaTime;
    }
    else if (playerDirection == 2)
    {
        playerX -= playerSpeed * deltaTime;
    }
    else if (playerDirection == 3)
    {
        playerY += playerSpeed * deltaTime;
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
            if (playerX - PLAYER_SIZE / 2.f < 0.f || playerX + PLAYER_SIZE / 2.f > SCREEN_WIDTH ||
                playerY - PLAYER_SIZE / 2.f < 0.f || playerY + PLAYER_SIZE / 2.f > SCREEN_HEIGHT)
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
                    float dx = fabs(playerX - appleX[i]);
                    float dy = fabs(playerY - appleY[i]);
                    if (dx <= (APPLE_SIZE + PLAYER_SIZE) / 2.f &&
                        dy <= APPLE_SIZE + PLAYER_SIZE / 2.f)
                    {
                        isApppleEaten[i] = true;
                        ++numEatenApples;
                    }
                    */
                    float squareDistance = (playerX - appleX[i]) * (playerX - appleX[i]) +
                        (playerY - appleY[i]) * (playerY - appleY[i]);
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
            playerShape.setPosition(playerX, playerY);
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
