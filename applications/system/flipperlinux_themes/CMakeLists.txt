add_library(flipperlinux_themes INTERFACE)

target_sources(flipperlinux_themes INTERFACE
    theme_engine.c
)

target_include_directories(flipperlinux_themes INTERFACE 
    ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(flipperlinux_themes INTERFACE
    furi
    storage
)
