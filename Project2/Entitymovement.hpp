#include <SFML/Graphics.hpp>
// Function to handle player movement with border collision detection
void HandlePlayerMovement(sf::RectangleShape& player, const sf::RenderWindow& window)
{
    // Getting player position and movement speed
    sf::Vector2f playerPosition = player.getPosition();
    float playerSpeed = 0.1f;

    // Handling player movement based on keyboard input
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
        if (playerPosition.y - playerSpeed > 0) {
            player.move(0, -playerSpeed);  // Moving up
        }
        else {
            player.setPosition(playerPosition.x, 0);  // Setting position to top border
        }
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
        if (playerPosition.y + playerSpeed + player.getSize().y < window.getSize().y) {
            player.move(0, playerSpeed);  // Moving down
        }
        else {
            player.setPosition(playerPosition.x, window.getSize().y - player.getSize().y);  // Setting position to bottom border
        }
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
        if (playerPosition.x - playerSpeed > 0) {
            player.move(-playerSpeed, 0);  // Moving left
        }
        else {
            player.setPosition(0, playerPosition.y);  // Setting position to left border
        }
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
        if (playerPosition.x + playerSpeed + player.getSize().x < window.getSize().x) {
            player.move(playerSpeed, 0);  // Moving right
        }
        else {
            player.setPosition(window.getSize().x - player.getSize().x, playerPosition.y);  // Setting position to right border
        }
    }
}

// Function to handle shooting mechanics
void HandleShooting(std::vector<sf::RectangleShape>& projectiles, const sf::RectangleShape& player)
{
    // Static clock for controlling shooting rate
    static sf::Clock clock;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && clock.getElapsedTime().asSeconds() > 0.2f) {
        // Creating a projectile
        sf::RectangleShape projectile(sf::Vector2f(5, 10));
        projectile.setFillColor(sf::Color::Yellow);
        projectile.setPosition(player.getPosition().x + player.getSize().x / 2 - projectile.getSize().x / 2,
            player.getPosition().y);
        projectiles.push_back(projectile);  // Adding projectile to vector
        clock.restart();  // Restarting clock for next shot
    }

    // Moving projectiles upwards
    for (auto& projectile : projectiles) {
        projectile.move(0, -0.2f);
    }

    // Removing off-screen projectiles
    projectiles.erase(std::remove_if(projectiles.begin(), projectiles.end(),
        [](const sf::RectangleShape& projectile) {
            return projectile.getPosition().y + projectile.getSize().y < 0;
        }),
        projectiles.end());
}