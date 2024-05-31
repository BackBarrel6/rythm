#include <SFML/Graphics.hpp>
#include <vector>
#include <algorithm>  // For std::remove_if

// Function to handle window events
void WindowEventCheck(sf::View& view, sf::RenderWindow& window, sf::Event& event)
{
    // Polling for events
    while (window.pollEvent(event))
    {
        // Handling window close event
        if (event.type == sf::Event::Closed)
            window.close();

        // Handling window resize event
        if (event.type == sf::Event::Resized) {
            // Adjusting view size to match window size
            view.setSize({
                static_cast<float>(event.size.width),
                static_cast<float>(event.size.height)
                });
            window.setView(view);
        }
    }
}

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

// Function to check for projectile collisions with the enemy
void CheckCollisions(std::vector<sf::RectangleShape>& projectiles, sf::RectangleShape& enemy, int& enemyHealth)
{
    // Looping through projectiles
    for (auto& projectile : projectiles) {
        // Checking collision with enemy
        if (projectile.getGlobalBounds().intersects(enemy.getGlobalBounds())) {
            enemyHealth -= 10;  // Decrease enemy health
            projectile.setPosition(-10, -10);  // Move projectile off-screen for removal
        }
    }
}

// Function to update health bars
void UpdateHealthBar(sf::RectangleShape& healthBar, int health, int maxHealth)
{
    // Calculating health percentage
    float healthPercentage = static_cast<float>(health) / static_cast<float>(maxHealth);
    // Updating health bar size based on percentage
    healthBar.setSize(sf::Vector2f(50.0f * healthPercentage, 5.0f));
}

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

