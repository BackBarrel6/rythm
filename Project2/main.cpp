#include <SFML/Graphics.hpp>

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "My window");
    sf::View view = window.getDefaultView();
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::Resized) {
                view.setSize({
                        static_cast<float>(event.size.width),
                        static_cast<float>(event.size.height)
                    });
                window.setView(view);
            }
    }

    return 0;
}