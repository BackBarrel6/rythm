#include <SFML/Graphics.hpp>
#include <vector>
#include <algorithm>  // For std::remove_if
#include "WindowEventCheck.hpp"
#include "Entitymovement.hpp"
#include "CheckCollisions.hpp"
#include "HealthBar.hpp"

// Main function
int main()
{
    // Creating the game window
    sf::RenderWindow window(sf::VideoMode(800, 600), "Dungeon Crawler");
    sf::View view = window.getDefaultView();

    // Player setup
    sf::RectangleShape player(sf::Vector2f(50, 50));
    player.setFillColor(sf::Color::Blue);
    player.setPosition(375, 275);  // Center of the initial window
    int playerHealth = 100;
    int maxPlayerHealth = 100;
    sf::RectangleShape playerHealthBar(sf::Vector2f(50, 5));
    playerHealthBar.setFillColor(sf::Color::Red);
    playerHealthBar.setPosition(player.getPosition().x, player.getPosition().y - 10);

    // Enemy setup
    sf::RectangleShape enemy(sf::Vector2f(50, 50));
    enemy.setFillColor(sf::Color::Green);
    enemy.setPosition(375, 100);  // Position at the top of the window
    int enemyHealth = 100;
    int maxEnemyHealth = 100;
    sf::RectangleShape enemyHealthBar(sf::Vector2f(50, 5));
    enemyHealthBar.setFillColor(sf::Color::Red);
    enemyHealthBar.setPosition(enemy.getPosition().x, enemy.getPosition().y - 10);

    // Projectiles container
    std::vector<sf::RectangleShape> projectiles;

    // Game loop
// Game loop
    while (window.isOpen())
    {
        // Handling window events
        sf::Event event;
        WindowEventCheck(view, window, event);

        // Handling player movement
        HandlePlayerMovement(player, window);

        // Handling shooting
        HandleShooting(projectiles, player);

        // Checking collisions between projectiles and enemy
        CheckCollisions(projectiles, enemy, enemyHealth);

        // Updating health bars
        UpdateHealthBar(playerHealthBar, playerHealth, maxPlayerHealth);
        UpdateHealthBar(enemyHealthBar, enemyHealth, maxEnemyHealth);
        playerHealthBar.setPosition(player.getPosition().x, player.getPosition().y - 10);
        enemyHealthBar.setPosition(enemy.getPosition().x, enemy.getPosition().y - 10);

        // Clearing the window
        window.clear();

        // Drawing the player, enemy, and their health bars
        window.draw(player);

        // Check if enemy is still alive
        if (enemyHealth > 0) {
            window.draw(enemy);
            window.draw(enemyHealthBar);
        }

        window.draw(playerHealthBar);

        // Drawing projectiles
        for (const auto& projectile : projectiles) {
            window.draw(projectile);
        }

        // Displaying the window
        window.display();
    }


    return 0;
}

