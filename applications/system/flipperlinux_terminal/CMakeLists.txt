add_library(flipperlinux_terminal_app INTERFACE)

target_sources(flipperlinux_terminal_app INTERFACE
    terminal.c
    terminal_app.c
    terminal_view.c
)

target_include_directories(flipperlinux_terminal_app INTERFACE 
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/..
)

target_link_libraries(flipperlinux_terminal_app INTERFACE
    furi
    furi_hal
    gui
    storage
)
