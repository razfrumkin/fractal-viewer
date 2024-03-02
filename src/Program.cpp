#include "Program.hpp"

void Program::process_events(InputManager& input, UIManager& ui) {
    sf::Event event;
    while (window.pollEvent(event)) {
        ui.process_event(window, event);

        switch (event.type) {
            case sf::Event::Closed:
                window.close();
                break;
            case sf::Event::Resized:
                window_resized(event.size.width, event.size.height);
                break;
            case sf::Event::KeyPressed:
                input.key_pressed(event);
                break;
            case sf::Event::KeyReleased:
                input.key_released(event);
                break;
            case sf::Event::MouseButtonPressed:
                input.mouse_button_pressed(event);
                break;
            case sf::Event::MouseButtonReleased:
                input.mouse_button_released(event);
                break;
        }
    }
}

void Program::window_resized(const unsigned int width, const unsigned int height) {
    window.setSize(sf::Vector2u(width, height));
    window.setView(sf::View(sf::FloatRect(0.0f, 0.0f, width, height)));
    renderer.create(width, height);
    display.setTexture(renderer.getTexture(), true);
    
    fractal.resize(width, height);
}

void Program::start(const unsigned int width, const unsigned int height, const std::string& title, const unsigned int frames_per_second) {
    window.create(sf::VideoMode(width, height), title);
    window.setVerticalSyncEnabled(true);
    window.resetGLStates();
    window.setFramerateLimit(frames_per_second);

    InputManager input;

    UIManager ui;
    ui.initialize(window);

    renderer.create(width, height);
    display.setTexture(renderer.getTexture(), true);

    fractal.create(width, height);

    sf::Clock clock;
    while (window.isOpen()) {
        process_events(input, ui);

        const sf::Time delta_time = clock.restart();
        const float delta_time_seconds = delta_time.asSeconds();

        ui.update(window, delta_time);
        fractal.update(delta_time_seconds, input, ui);

        window.clear(sf::Color::Black);

        fractal.render(renderer, ui);

        window.draw(display);

        ui.show(window, fractal.get_pan(), display);

        window.display();
    }

    ui.shutdown();
}