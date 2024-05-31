#include<SFML/Graphics.hpp>
#include <SFML/Graphics.hpp>
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