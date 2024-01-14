#include "Player.h"
#include "Game.h"

namespace AppleGames
{
    void InitPlayer(Player& player, const Game& game)
    {
        //Init player state
        player.position = { SCREEN_WIDTH / 2.f, SCREEN_HEIGHT / 2.f };
        player.speed = INITIAL_SPEED;
        player.direction = PlayerDirection::Right;

        // Init Player Texture
        player.sprite.setTexture(game.playerTexture);
    }

    void DrawPlayer(Player& player, sf::RenderWindow& window)
    {
        player.sprite.setPosition(player.position.x, player.position.y);
        window.draw(player.sprite);
    }
}

