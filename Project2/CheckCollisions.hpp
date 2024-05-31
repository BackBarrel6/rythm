#include<SFML/Graphics.hpp>
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