#pragma once

#include <iostream>

#include "InputManager.hpp"
#include "UIManager.hpp"

class Fractal {
    private:
    sf::Sprite sprite;
    sf::Texture texture;
    sf::Image image;

    bool should_rerender;

    float zoom;
    void set_zoom(const float zoom);

    sf::Vector2f pan;
    void set_pan(const sf::Vector2f pan);

    sf::Shader shader;

    sf::Vector2f normalize(const sf::Vector2u pixel, const sf::Vector2u resolution) const;

    public:
    sf::Vector2f get_pan() const;

    void create(const unsigned int width, const unsigned int height);

    void resize(const unsigned int width, const unsigned int height);

    void update(const float delta_time, const InputManager& input, const UIManager& ui);
    void render(sf::RenderTexture& renderer, const UIManager& ui);

    Fractal() = default;
};