#include "theme_engine.h"
#include <storage/storage.h>
#include <furi.h>
#include <string.h>

// Cinnamon Theme: Orange/warm colors inspired by Linux Mint Cinnamon
static const ThemePalette CINNAMON_PALETTE = {
    .primary_r = 241,
    .primary_g = 121,
    .primary_b = 15,
    .secondary_r = 255,
    .secondary_g = 255,
    .secondary_b = 255,
    .accent_r = 76,
    .accent_g = 175,
    .accent_b = 80,
    .name = "Cinnamon",
    .description = "Linux Mint Cinnamon inspired theme with warm tones",
};

// KDE Theme: Blue/modern colors inspired by KDE Plasma
static const ThemePalette KDE_PALETTE = {
    .primary_r = 31,
    .primary_g = 135,
    .primary_b = 234,
    .secondary_r = 255,
    .secondary_g = 255,
    .secondary_b = 255,
    .accent_r = 61,
    .accent_g = 174,
    .accent_b = 233,
    .name = "KDE Plasma",
    .description = "KDE Plasma inspired theme with modern blue",
};

// Default theme: Standard Flipper
static const ThemePalette DEFAULT_PALETTE = {
    .primary_r = 0,
    .primary_g = 0,
    .primary_b = 0,
    .secondary_r = 255,
    .secondary_g = 255,
    .secondary_b = 255,
    .accent_r = 128,
    .accent_g = 128,
    .accent_b = 128,
    .name = "Default",
    .description = "Standard Flipper Zero theme",
};

struct ThemeEngine {
    ThemeConfig current_theme;
    Storage* storage;
};

ThemeEngine* theme_engine_alloc(void) {
    ThemeEngine* engine = malloc(sizeof(ThemeEngine));
    engine->storage = furi_record_open(RECORD_STORAGE);
    
    // Load default theme
    engine->current_theme.type = ThemeDefault;
    engine->current_theme.palette = DEFAULT_PALETTE;
    engine->current_theme.font_style = "default";
    engine->current_theme.icon_set = "default";
    engine->current_theme.corner_radius = 4;
    engine->current_theme.padding = 2;
    
    return engine;
}

void theme_engine_free(ThemeEngine* engine) {
    if (engine) {
        furi_record_close(RECORD_STORAGE);
        free(engine);
    }
}

void theme_engine_set_active_theme(ThemeEngine* engine, ThemeType type) {
    furi_assert(engine);
    
    engine->current_theme.type = type;
    
    switch (type) {
        case ThemeCinnamon:
            engine->current_theme.palette = CINNAMON_PALETTE;
            engine->current_theme.font_style = "cinnamon";
            engine->current_theme.icon_set = "cinnamon-icons";
            engine->current_theme.corner_radius = 6;
            engine->current_theme.padding = 3;
            break;
        case ThemeKDE:
            engine->current_theme.palette = KDE_PALETTE;
            engine->current_theme.font_style = "kde";
            engine->current_theme.icon_set = "kde-breeze";
            engine->current_theme.corner_radius = 5;
            engine->current_theme.padding = 3;
            break;
        case ThemeDefault:
        default:
            engine->current_theme.palette = DEFAULT_PALETTE;
            engine->current_theme.font_style = "default";
            engine->current_theme.icon_set = "default";
            engine->current_theme.corner_radius = 4;
            engine->current_theme.padding = 2;
            break;
    }
}

ThemeConfig* theme_engine_get_config(ThemeEngine* engine) {
    return &engine->current_theme;
}

void theme_engine_save_to_storage(ThemeEngine* engine) {
    furi_assert(engine);
    
    File* file = storage_file_alloc(engine->storage);
    if (!storage_file_open(file, "/int/theme_config.txt", FSAM_WRITE, FSOM_CREATE_ALWAYS)) {
        storage_file_free(file);
        return;
    }
    
    char buffer[256];
    snprintf(buffer, sizeof(buffer), "THEME=%d\nPALETTE=%d,%d,%d,%d,%d,%d,%d,%d,%d\n",
             engine->current_theme.type,
             engine->current_theme.palette.primary_r,
             engine->current_theme.palette.primary_g,
             engine->current_theme.palette.primary_b,
             engine->current_theme.palette.secondary_r,
             engine->current_theme.palette.secondary_g,
             engine->current_theme.palette.secondary_b,
             engine->current_theme.palette.accent_r,
             engine->current_theme.palette.accent_g,
             engine->current_theme.palette.accent_b);
    
    storage_file_write(file, (uint8_t*)buffer, strlen(buffer));
    storage_file_close(file);
    storage_file_free(file);
}

void theme_engine_load_from_storage(ThemeEngine* engine) {
    furi_assert(engine);
    
    File* file = storage_file_alloc(engine->storage);
    if (!storage_file_open(file, "/int/theme_config.txt", FSAM_READ, FSOM_OPEN_EXISTING)) {
        storage_file_free(file);
        return;
    }
    
    char buffer[256] = {0};
    storage_file_read(file, (uint8_t*)buffer, sizeof(buffer) - 1);
    storage_file_close(file);
    storage_file_free(file);
    
    int theme_type = 0;
    if (sscanf(buffer, "THEME=%d", &theme_type) == 1) {
        theme_engine_set_active_theme(engine, (ThemeType)theme_type);
    }
}
