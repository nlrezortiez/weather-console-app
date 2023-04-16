add_executable(app main.cpp
                    content-provider/response-handler.cpp
                    content-provider/app.cpp
                    forecast/forecast.cpp
                    content-provider/config-parser.cpp
                    config/config-setup.cpp
                    terminal-renderer/terminal-renderer.cpp)

target_link_libraries(app PRIVATE cpr::cpr)

target_link_libraries(app
    PRIVATE ftxui::screen
    PRIVATE ftxui::dom)
