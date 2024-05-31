#include<SFML/Graphics.hpp>
// Function to update health bars
void UpdateHealthBar(sf::RectangleShape& healthBar, int health, int maxHealth)
{
    // Calculating health percentage
    float healthPercentage = static_cast<float>(health) / static_cast<float>(maxHealth);
    // Updating health bar size based on percentage
    healthBar.setSize(sf::Vector2f(50.0f * healthPercentage, 5.0f));
}
