#pragma once
#include <SFML/Graphics.hpp>
#include "Math.h"
#include "Constants.h"

namespace AppleGames
{
    enum class PlayerDirection {
        Right = 0,
        Up,
        Left,
        Down
    };

    struct Player
    {
        // Player data
        Position2D position;
        float speed = INITIAL_SPEED;
        PlayerDirection direction = PlayerDirection::Right;
        sf::RectangleShape shape;
    };

    void InitPlayer(Player& player);
}

