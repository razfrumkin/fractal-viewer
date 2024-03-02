#pragma once

#include <string>

#include <SFML/Graphics.hpp>

enum class SetType {
    MANDELBROT,
    TRICORN,
    BURNING_SHIP,
    JULIA,
    COUNT
};

enum class ColoringType {
    GRAYSCALE,
    MIX,
    RAINBOW,
    COUNT
};

std::string stringify(const SetType type);
std::string stringify(const ColoringType type);

struct FractalSettings {
    static constexpr ColoringType DEFAULT_COLORING = ColoringType::GRAYSCALE;
    static constexpr unsigned int MINIMUM_COLOR_REPEATINGS = 1;
    static constexpr unsigned int MAXIMUM_COLOR_REPEATINGS = 10;
    static constexpr unsigned int DEFAULT_COLOR_REPEATINGS = 1;
    static const sf::Color DEFAULT_FIRST_COLOR;
    static const sf::Color DEFAULT_SECOND_COLOR;
    static constexpr float DEFAULT_RAINBOW_SATURATION = 0.5f;
    static constexpr float DEFAULT_RAINBOW_BRIGHTNESS = 0.5f;
    static constexpr unsigned int MINIMUM_ITERATIONS = 0;
    static constexpr unsigned int MAXIMUM_ITERATIONS = 1000;
    static constexpr unsigned int DEFAULT_ITERATIONS = 100;
    static constexpr SetType DEFAULT_SET = SetType::MANDELBROT;
    static constexpr bool DEFAULT_USE_PHOENIX_COMPLEX = false;
    static constexpr float JULIA_COMPLEX_MINIMUM = -2.0f;
    static constexpr float JULIA_COMPLEX_MAXIMUM = 2.0f;
    static const sf::Vector2f DEFAULT_JULIA_COMPLEX;
    static constexpr float PHOENIX_COMPLEX_MINIMUM = -2.0f;
    static constexpr float PHOENIX_COMPLEX_MAXIMUM = 2.0f;
    static const sf::Vector2f DEFAULT_PHOENIX_COMPLEX;
    static constexpr float MINIMUM_ZOOM_SPEED = 0.5f;
    static constexpr float MAXIMUM_ZOOM_SPEED = 2.0f;
    static constexpr float DEFAULT_ZOOM_SPEED = 1.0f;
    static constexpr float MINIMUM_PAN_SPEED = 0.5f;
    static constexpr float MAXIMUM_PAN_SPEED = 2.0f;
    static constexpr float DEFAULT_PAN_SPEED = 1.0f;

    ColoringType coloring = DEFAULT_COLORING;
    unsigned int color_repeatings = DEFAULT_COLOR_REPEATINGS;
    sf::Color first_color = DEFAULT_FIRST_COLOR;
    sf::Color second_color = DEFAULT_SECOND_COLOR;
    float rainbow_saturation = DEFAULT_RAINBOW_SATURATION;
    float rainbow_brightness = DEFAULT_RAINBOW_BRIGHTNESS;
    unsigned int iterations = DEFAULT_ITERATIONS;
    SetType current_set = DEFAULT_SET;
    bool use_phoenix_complex = DEFAULT_USE_PHOENIX_COMPLEX;
    sf::Vector2f julia_complex = DEFAULT_JULIA_COMPLEX;
    sf::Vector2f phoenix_complex = DEFAULT_PHOENIX_COMPLEX;
    float zoom_speed = DEFAULT_ZOOM_SPEED;
    float pan_speed = DEFAULT_PAN_SPEED;

    FractalSettings() = default;
};