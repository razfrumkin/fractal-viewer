#pragma once

#include <string>

#include "Fractal.hpp"

class Program {
    private:
    sf::RenderWindow window;

    sf::RenderTexture renderer;
    sf::Sprite display;

    Fractal fractal;

    void process_events(InputManager& input, UIManager& ui);

    void window_resized(const unsigned int width, const unsigned int height);

    public:
    void start(const unsigned int width, const unsigned int height, const std::string& title, const unsigned int frames_per_second);
};