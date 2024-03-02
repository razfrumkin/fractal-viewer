#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

#include <array>

class InputManager {
    private:
    std::array<bool, sf::Keyboard::KeyCount> keys_down;
    std::array<bool, sf::Mouse::ButtonCount> mouse_buttons_down;

    public:
    bool is_down(const sf::Keyboard::Key key) const;
    bool is_down(const sf::Mouse::Button mouse_button) const;

    void key_pressed(const sf::Event event);
    void key_released(const sf::Event event);
    void mouse_button_pressed(const sf::Event event);
    void mouse_button_released(const sf::Event event);

    InputManager();
};