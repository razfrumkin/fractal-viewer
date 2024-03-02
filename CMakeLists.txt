project(fractal)

set(SOURCE_FILES
    src/Main.cpp
    src/Program.cpp
    src/InputManager.cpp
    src/FractalSettings.cpp
    src/UIManager.cpp
    src/Fractal.cpp

    src/ImGui/imgui_demo.cpp
    src/ImGui/imgui_draw.cpp
    src/ImGui/imgui_tables.cpp
    src/ImGui/imgui_widgets.cpp
    src/ImGui/imgui.cpp

    src/ImGui/imgui-SFML.cpp
)

add_executable(main ${SOURCE_FILES})

target_include_directories(main PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/include")

target_link_directories(main PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/lib")
target_link_libraries(
    main PRIVATE sfml-system sfml-window sfml-graphics sfml-audio sfml-network "-framework OpenGL"
)

set_target_properties(main PROPERTIES
    CXX_STANDARD 20
    CXX_EXTENSIONS OFF
)