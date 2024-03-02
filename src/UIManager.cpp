#include "UIManager.hpp"

void UIManager::initialize_styles() const {
    ImGuiStyle& style = ImGui::GetStyle();
    ImVec4* colors = style.Colors;

    colors[ImGuiCol_Text] = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
    colors[ImGuiCol_WindowBg] = ImVec4(0.10f, 0.10f, 0.10f, 1.00f);
    colors[ImGuiCol_Border] = ImVec4(0.19f, 0.19f, 0.19f, 0.29f);
    colors[ImGuiCol_BorderShadow] = ImVec4(0.00f, 0.00f, 0.00f, 0.24f);
    colors[ImGuiCol_FrameBg] = ImVec4(0.05f, 0.05f, 0.05f, 0.54f);
    colors[ImGuiCol_FrameBgHovered] = ImVec4(0.19f, 0.19f, 0.19f, 0.54f);
    colors[ImGuiCol_FrameBgActive] = ImVec4(0.20f, 0.22f, 0.23f, 1.00f);
    colors[ImGuiCol_TitleBg] = ImVec4(0.00f, 0.00f, 0.00f, 1.00f);
    colors[ImGuiCol_TitleBgActive] = ImVec4(0.06f, 0.06f, 0.06f, 1.00f);
    colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.00f, 0.00f, 0.00f, 1.00f);
    colors[ImGuiCol_MenuBarBg] = ImVec4(0.14f, 0.14f, 0.14f, 1.00f);
    colors[ImGuiCol_ScrollbarBg] = ImVec4(0.05f, 0.05f, 0.05f, 0.54f);
    colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.34f, 0.34f, 0.34f, 0.54f);
    colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.40f, 0.40f, 0.40f, 0.54f);
    colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.56f, 0.56f, 0.56f, 0.54f);
    colors[ImGuiCol_CheckMark] = ImVec4(0.33f, 0.67f, 0.86f, 1.00f);
    colors[ImGuiCol_SliderGrab] = ImVec4(0.34f, 0.34f, 0.34f, 0.54f);
    colors[ImGuiCol_SliderGrabActive] = ImVec4(0.56f, 0.56f, 0.56f, 0.54f);
    colors[ImGuiCol_Button] = ImVec4(0.05f, 0.05f, 0.05f, 0.54f);
    colors[ImGuiCol_ButtonHovered] = ImVec4(0.19f, 0.19f, 0.19f, 0.54f);
    colors[ImGuiCol_ButtonActive] = ImVec4(0.20f, 0.22f, 0.23f, 1.00f);
    colors[ImGuiCol_Header] = ImVec4(0.00f, 0.00f, 0.00f, 0.52f);
    colors[ImGuiCol_HeaderHovered] = ImVec4(0.00f, 0.00f, 0.00f, 0.36f);
    colors[ImGuiCol_HeaderActive] = ImVec4(0.20f, 0.22f, 0.23f, 0.33f);
    colors[ImGuiCol_ResizeGrip] = ImVec4(0.28f, 0.28f, 0.28f, 0.29f);
    colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.44f, 0.44f, 0.44f, 0.29f);
    colors[ImGuiCol_ResizeGripActive] = ImVec4(0.40f, 0.44f, 0.47f, 1.00f);

    style.WindowPadding = ImVec2(8.00f, 8.00f);
    style.FramePadding = ImVec2(5.00f, 2.00f);
    style.CellPadding = ImVec2(6.00f, 6.00f);
    style.ItemSpacing = ImVec2(6.00f, 6.00f);
    style.ItemInnerSpacing = ImVec2(6.00f, 6.00f);
    style.ScrollbarSize = 15;
    style.WindowBorderSize = 1;
    style.FrameBorderSize = 1;
    style.WindowRounding = 7;
    style.FrameRounding = 3;
    style.ScrollbarRounding = 9;
}

bool UIManager::show_fractal_configurations() {
    if (ImGui::CollapsingHeader("Fractal Configurations", ImGuiTreeNodeFlags_DefaultOpen)) {
        ImGui::Text("Iterations");
        ImGui::SameLine();
        int signed_iterations = static_cast<int>(settings.iterations);
        const bool iterations_changed = ImGui::SliderInt("##iterations", &signed_iterations, FractalSettings::MINIMUM_ITERATIONS, FractalSettings::MAXIMUM_ITERATIONS);
        if (iterations_changed) settings.iterations = static_cast<unsigned int>(signed_iterations);

        bool current_set_changed = false;
        if (ImGui::BeginCombo("##set_type", stringify(settings.current_set).c_str())) {
            SetType previous = settings.current_set;
            for (std::size_t index = 0; index < static_cast<std::size_t>(SetType::COUNT); index += 1) {
                SetType type = static_cast<SetType>(index);
                const bool is_selected = type == settings.current_set;
                if (ImGui::Selectable(stringify(type).c_str(), is_selected)) {
                    settings.current_set = type;
                }

                if (is_selected) ImGui::SetItemDefaultFocus();
            }

            ImGui::EndCombo();
            current_set_changed = previous != settings.current_set;
        }

        bool input_changed_based_on_julia = false;
        if (settings.current_set == SetType::JULIA) {
            ImGui::Text("Use Phoenix Complex");
            ImGui::SameLine();
            const bool use_phoenix_complex_changed = ImGui::Checkbox("##use_phoenix_complex", &settings.use_phoenix_complex);

            ImGui::Text("Julia Complex");
            ImGui::SameLine();
            float julia_complex_floats[2] = { settings.julia_complex.x, settings.julia_complex.y }; 
            const bool julia_complex_changed = ImGui::SliderFloat2("##julia_complex", julia_complex_floats, FractalSettings::JULIA_COMPLEX_MINIMUM, FractalSettings::JULIA_COMPLEX_MAXIMUM);
            if (julia_complex_changed) settings.julia_complex = sf::Vector2f(julia_complex_floats[0], julia_complex_floats[1]);

            bool phoenix_complex_changed = false;
            if (settings.use_phoenix_complex) {
                ImGui::Text("Phoenix Complex");
                ImGui::SameLine();
                float phoenix_complex_floats[2] = { settings.phoenix_complex.x, settings.phoenix_complex.y }; 
                phoenix_complex_changed = ImGui::SliderFloat2("##phoenix_complex", phoenix_complex_floats, FractalSettings::PHOENIX_COMPLEX_MINIMUM, FractalSettings::PHOENIX_COMPLEX_MAXIMUM);
                if (phoenix_complex_changed) settings.phoenix_complex = sf::Vector2f(phoenix_complex_floats[0], phoenix_complex_floats[1]);
            }

            if (use_phoenix_complex_changed || julia_complex_changed || phoenix_complex_changed) input_changed_based_on_julia = true;
        }

        return iterations_changed || current_set_changed || input_changed_based_on_julia;
    }

    return false;
}

bool UIManager::show_coloring_configurations() {
    if (ImGui::CollapsingHeader("Coloring")) {
        bool coloring_changed = false;
        if (ImGui::BeginCombo("##coloring_type", stringify(settings.coloring).c_str())) {
            ColoringType previous = settings.coloring;
            for (std::size_t index = 0; index < static_cast<std::size_t>(ColoringType::COUNT); index += 1) {
                ColoringType type = static_cast<ColoringType>(index);
                const bool is_selected = type == settings.coloring;
                if (ImGui::Selectable(stringify(type).c_str(), is_selected)) {
                    settings.coloring = type;
                }

                if (is_selected) ImGui::SetItemDefaultFocus();
            }

            ImGui::EndCombo();
            coloring_changed = previous != settings.coloring;
        }

        ImGui::Text("Color Repeatings");
        ImGui::SameLine();
        int signed_color_repeatings = static_cast<int>(settings.color_repeatings);
        const bool color_repeatings_changed = ImGui::SliderInt("##color_repeatings", &signed_color_repeatings, FractalSettings::MINIMUM_COLOR_REPEATINGS, FractalSettings::MAXIMUM_COLOR_REPEATINGS);
        if (color_repeatings_changed) settings.color_repeatings = static_cast<unsigned int>(signed_color_repeatings);

        bool inputs_changed_based_on_coloring = false;
        switch (settings.coloring) {
            case ColoringType::MIX: {
                ImGui::Text("First Color");
                ImGui::SameLine();
                float first_color_floats[3] = { settings.first_color.r / 255.0f, settings.first_color.g / 255.0f, settings.first_color.b / 255.0f };
                const bool first_color_changed = ImGui::ColorEdit3("##first_color", first_color_floats, ImGuiColorEditFlags_NoSidePreview | ImGuiColorEditFlags_PickerHueWheel);
                if (first_color_changed) settings.first_color = sf::Color(static_cast<sf::Uint8>(first_color_floats[0] * 255), static_cast<sf::Uint8>(first_color_floats[1] * 255), static_cast<sf::Uint8>(first_color_floats[2] * 255));

                ImGui::Text("Second Color");
                ImGui::SameLine();
                float second_color_floats[3] = { settings.second_color.r / 255.0f, settings.second_color.g / 255.0f, settings.second_color.b / 255.0f };
                const bool second_color_changed = ImGui::ColorEdit3("##second_color", second_color_floats, ImGuiColorEditFlags_NoSidePreview | ImGuiColorEditFlags_PickerHueWheel);
                if (second_color_changed) settings.second_color = sf::Color(static_cast<sf::Uint8>(second_color_floats[0] * 255), static_cast<sf::Uint8>(second_color_floats[1] * 255), static_cast<sf::Uint8>(second_color_floats[2] * 255));

                if (first_color_changed || second_color_changed) inputs_changed_based_on_coloring = true;
                break;
            }
            case ColoringType::RAINBOW: {
                ImGui::Text("Saturation");
                ImGui::SameLine();
                const bool saturation_changed = ImGui::SliderFloat("##saturation", &settings.rainbow_saturation, 0.0f, 1.0f);

                ImGui::Text("Brightness");
                ImGui::SameLine();
                const bool brightness_changed = ImGui::SliderFloat("##brightness", &settings.rainbow_brightness, 0.0f, 1.0f);

                if (saturation_changed || brightness_changed) inputs_changed_based_on_coloring = true;
                break;
            }
        }

        return coloring_changed || color_repeatings_changed || inputs_changed_based_on_coloring;
    }

    return false;
}

bool UIManager::show_view_configurations(const sf::Vector2f complex, const sf::Sprite& sprite) {
    if (ImGui::CollapsingHeader("View")) {
        ImGui::Text("Center: %g + %gi", complex.x, complex.y);

        ImGui::Text("Zoom Speed");
        ImGui::SameLine();
        const bool zoom_speed_changed = ImGui::SliderFloat("##zoom_speed", &settings.zoom_speed, FractalSettings::MINIMUM_ZOOM_SPEED, FractalSettings::MAXIMUM_ZOOM_SPEED);

        ImGui::Text("Pan Speed");
        ImGui::SameLine();            
        const bool pan_speed_changed = ImGui::SliderFloat("##pan_speed", &settings.pan_speed, FractalSettings::MINIMUM_PAN_SPEED, FractalSettings::MAXIMUM_PAN_SPEED);

        if (ImGui::Button("Save Image")) sprite.getTexture()->copyToImage().saveToFile(image_file_name);
        ImGui::SameLine();

        std::array<char, 256> raw_image_file_name;
        std::strcpy(raw_image_file_name.data(), image_file_name.c_str());
        const bool image_file_name_changed = ImGui::InputText("##image_file_name", raw_image_file_name.data(), raw_image_file_name.size());
        if (image_file_name_changed) image_file_name = raw_image_file_name.data();

        return zoom_speed_changed || pan_speed_changed;
    }

    return false;
}

void UIManager::initialize(sf::RenderWindow& window) {
    ImGui::SFML::Init(window);

    is_focused = false;

    ImGuiIO& io = ImGui::GetIO();

    io.IniFilename = nullptr;
    io.Fonts->Clear();
    io.Fonts->AddFontFromFileTTF("res/fonts/Roboto-Medium.ttf", 16.0f);
    ImGui::SFML::UpdateFontTexture();

    initialize_styles();

    image_file_name = "Fractal.png";
}

void UIManager::shutdown() const {
    ImGui::SFML::Shutdown();
}

void UIManager::process_event(const sf::Window& window, const sf::Event& event) const {
    ImGui::SFML::ProcessEvent(window, event);
}

void UIManager::update(sf::RenderWindow& window, const sf::Time time) {
    ImGui::SFML::Update(window, time);
}

void UIManager::show(sf::RenderWindow& window, const sf::Vector2f complex, const sf::Sprite& sprite) {
    inputs_changed = false;

    if (ImGui::Begin("Settings")) {
        is_focused = ImGui::IsWindowFocused();

        const bool fractal_configurations_changed = show_fractal_configurations();
        const bool coloring_configurations_changed = show_coloring_configurations();
        const bool view_configurations_changed = show_view_configurations(complex, sprite);

        if (fractal_configurations_changed || view_configurations_changed || coloring_configurations_changed) inputs_changed = true;
    }

    ImGui::End();
    ImGui::SFML::Render(window);
}

bool UIManager::get_is_focused() const {
    return is_focused;
}

bool UIManager::have_inputs_changed() const {
    return inputs_changed;
}

const FractalSettings& UIManager::get_settings() const {
    return settings;
}

UIManager::UIManager() {
    inputs_changed = true;
}