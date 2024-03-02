#include "FractalSettings.hpp"

std::string stringify(const SetType type) {
    switch (type) {
        case SetType::MANDELBROT: return "Mandelbrot Set";
        case SetType::TRICORN: return "Tricorn";
        case SetType::BURNING_SHIP: return "Burning Ship";
        case SetType::JULIA: return "Julia Set";
        default: return "Error";
    }
}

std::string stringify(const ColoringType type) {
    switch (type) {
        case ColoringType::GRAYSCALE: return "Grayscale";
        case ColoringType::MIX: return "Mix";
        case ColoringType::RAINBOW: return "Rainbow";
        default: return "Error";
    }
}

const sf::Color FractalSettings::DEFAULT_FIRST_COLOR = sf::Color::Black;
const sf::Color FractalSettings::DEFAULT_SECOND_COLOR = sf::Color::White;
const sf::Vector2f FractalSettings::DEFAULT_JULIA_COMPLEX = sf::Vector2f(0.0f, 0.0f);
const sf::Vector2f FractalSettings::DEFAULT_PHOENIX_COMPLEX = sf::Vector2f(0.0f, 0.0f);