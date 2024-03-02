#include "Fractal.hpp"

void Fractal::set_zoom(const float zoom) {
    this->zoom = zoom;
    should_rerender = true;
}

void Fractal::set_pan(const sf::Vector2f pan) {
    this->pan = pan;
    should_rerender = true;
}

sf::Vector2f Fractal::normalize(const sf::Vector2u pixel, const sf::Vector2u resolution) const {
    const unsigned int smaller_axis = resolution.x < resolution.y ? resolution.x : resolution.y;

    const float x = (pixel.x - resolution.x / 2.0f) / zoom / smaller_axis + pan.x;
    const float y = (pixel.y - resolution.y / 2.0f) / zoom / smaller_axis + pan.y;

    return sf::Vector2f(x, y);
}

sf::Vector2f Fractal::get_pan() const {
    return pan;
}

void Fractal::create(const unsigned int width, unsigned int height) {
    shader.loadFromFile("res/shaders/fractal.glsl", sf::Shader::Fragment);

    sprite = sf::Sprite();

    resize(width, height);

    set_zoom(0.35f);
    set_pan(sf::Vector2f(-0.5f, 0.0f));
}

void Fractal::resize(const unsigned int width, const unsigned int height) {
    image.create(width, height, sf::Color::Transparent);
    texture.create(width, height);
    sprite.setTexture(texture, true);
    should_rerender = true;
}

void Fractal::update(const float delta_time, const InputManager& input, const UIManager& ui) {
    if (ui.get_is_focused()) return;

    const FractalSettings& settings = ui.get_settings();

    if (input.is_down(sf::Keyboard::Up)) set_zoom(zoom * (1.0 + settings.zoom_speed * delta_time));
    if (input.is_down(sf::Keyboard::Down)) set_zoom(zoom / (1.0 + settings.zoom_speed * delta_time));

    if (input.is_down(sf::Keyboard::D)) set_pan(sf::Vector2f(pan.x + settings.pan_speed * delta_time / zoom, pan.y));
    if (input.is_down(sf::Keyboard::A)) set_pan(sf::Vector2f(pan.x - settings.pan_speed * delta_time / zoom, pan.y));
    if (input.is_down(sf::Keyboard::W)) set_pan(sf::Vector2f(pan.x, pan.y + settings.pan_speed * delta_time / zoom));
    if (input.is_down(sf::Keyboard::S)) set_pan(sf::Vector2f(pan.x, pan.y - settings.pan_speed * delta_time / zoom));
}

void Fractal::render(sf::RenderTexture& renderer, const UIManager& ui) {
    if (ui.have_inputs_changed()) should_rerender = true;

    if (!should_rerender) {
        renderer.draw(sprite, &shader);
        return;
    }

    should_rerender = false;

    const FractalSettings& settings = ui.get_settings();

    texture.update(image);

    renderer.clear(sf::Color::Black);

    const sf::Vector2f bottom_left = normalize(sf::Vector2u(0, 0), renderer.getSize());
    const sf::Vector2f top_right = normalize(renderer.getSize(), renderer.getSize());

    shader.setUniform("resolution", sf::Vector2i(renderer.getSize()));
    shader.setUniform("bottom_left", bottom_left);
    shader.setUniform("top_right", top_right);
    shader.setUniform("iterations", static_cast<int>(settings.iterations));
    shader.setUniform("current_set", static_cast<int>(settings.current_set));

    if (settings.current_set == SetType::JULIA) {
        shader.setUniform("julia_complex", settings.julia_complex);
        shader.setUniform("phoenix_complex", settings.use_phoenix_complex ? settings.phoenix_complex : sf::Vector2f(0.0f, 0.0f));
    }

    shader.setUniform("color_repeatings", static_cast<int>(settings.color_repeatings));
    switch (settings.coloring) {
        case ColoringType::GRAYSCALE:
            shader.setUniform("draw_rainbow", false);
            shader.setUniform("first_color", sf::Glsl::Vec4(sf::Color::Black));
            shader.setUniform("second_color", sf::Glsl::Vec4(sf::Color::White));
            break;
        case ColoringType::MIX:
            shader.setUniform("draw_rainbow", false);
            shader.setUniform("first_color", sf::Glsl::Vec4(settings.first_color));
            shader.setUniform("second_color", sf::Glsl::Vec4(settings.second_color));
            break;
        case ColoringType::RAINBOW:
            shader.setUniform("draw_rainbow", true);
            shader.setUniform("saturation", settings.rainbow_saturation);
            shader.setUniform("brightness", settings.rainbow_brightness);
            break;
    }

    renderer.draw(sprite, &shader);

    renderer.display();
}