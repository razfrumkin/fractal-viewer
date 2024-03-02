#pragma once

#include <iostream>
#include <string>

#include "ImGui/imgui.h"
#include "ImGui/imgui-SFML.h"

#include "FractalSettings.hpp"

class UIManager {
    private:
    bool is_focused;
    bool inputs_changed;

    FractalSettings settings;
    std::string image_file_name;

    void initialize_styles() const;

    bool show_fractal_configurations();
    bool show_coloring_configurations();
    bool show_view_configurations(const sf::Vector2f complex, const sf::Sprite& sprite);
    
    public:
    void initialize(sf::RenderWindow& window);
    void shutdown() const;

    void process_event(const sf::Window& window, const sf::Event& event) const;
    void update(sf::RenderWindow& window, const sf::Time time);
    void show(sf::RenderWindow& window, const sf::Vector2f complex, const sf::Sprite& sprite);

    bool get_is_focused() const;
    bool have_inputs_changed() const;

    const FractalSettings& get_settings() const;

    UIManager();
};