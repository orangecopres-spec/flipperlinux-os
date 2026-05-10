#pragma once

#include <storage/storage.h>
#include <stdint.h>

typedef struct TerminalApp TerminalApp;

// Theme types
typedef enum {
    ThemeCinnamon,
    ThemeKDE,
    ThemeDefault,
} ThemeType;

// Create/destroy
TerminalApp* terminal_app_alloc(void);
void terminal_app_free(TerminalApp* app);

// Commands
void terminal_app_process_command(TerminalApp* app, const char* command);
const char* terminal_app_get_output(TerminalApp* app);
void terminal_app_clear_output(TerminalApp* app);

// Theme
void terminal_app_set_theme(TerminalApp* app, ThemeType theme);
ThemeType terminal_app_get_active_theme(TerminalApp* app);
