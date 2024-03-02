#include "InputManager.hpp"

bool InputManager::is_down(const sf::Keyboard::Key key) const {
    return keys_down[key];
}

bool InputManager::is_down(const sf::Mouse::Button mouse_button) const {
    return mouse_buttons_down[mouse_button];
}

void InputManager::key_pressed(const sf::Event event) {
    if (!keys_down[event.key.code]) keys_down[event.key.code] = true;
}

void InputManager::key_released(const sf::Event event) {
    if (keys_down[event.key.code]) keys_down[event.key.code] = false;
}

void InputManager::mouse_button_pressed(const sf::Event event) {
    if (!mouse_buttons_down[event.mouseButton.button]) mouse_buttons_down[event.mouseButton.button] = true;
}

void InputManager::mouse_button_released(const sf::Event event) {
    if (mouse_buttons_down[event.mouseButton.button]) mouse_buttons_down[event.mouseButton.button] = false;
}

InputManager::InputManager() {
    keys_down.fill(false);
    mouse_buttons_down.fill(false);
}