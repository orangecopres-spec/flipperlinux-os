#pragma once

#include <stdint.h>
#include <stdlib.h>

typedef enum {
    ThemeCinnamon,
    ThemeKDE,
    ThemeDefault,
} ThemeType;

typedef struct {
    uint8_t primary_r;
    uint8_t primary_g;
    uint8_t primary_b;
    uint8_t secondary_r;
    uint8_t secondary_g;
    uint8_t secondary_b;
    uint8_t accent_r;
    uint8_t accent_g;
    uint8_t accent_b;
    const char* name;
    const char* description;
} ThemePalette;

typedef struct {
    ThemeType type;
    ThemePalette palette;
    const char* font_style;
    const char* icon_set;
    uint8_t corner_radius;
    uint8_t padding;
} ThemeConfig;

typedef struct ThemeEngine ThemeEngine;

ThemeEngine* theme_engine_alloc(void);
void theme_engine_free(ThemeEngine* engine);
void theme_engine_set_active_theme(ThemeEngine* engine, ThemeType type);
ThemeConfig* theme_engine_get_config(ThemeEngine* engine);
void theme_engine_save_to_storage(ThemeEngine* engine);
void theme_engine_load_from_storage(ThemeEngine* engine);
