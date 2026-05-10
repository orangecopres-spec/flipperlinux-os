#include "terminal_app.h"
#include <furi.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

typedef struct {
    const char* name;
    const char* description;
    const char* version;
} Package;

static const Package PACKAGE_REGISTRY[] = {
    {"cinnamon", "Cinnamon", "1.0.0"},
    {"kde", "KDE", "1.0.0"},
    {"yaru", "Yaru", "1.0.0"},
    {"music", "Music", "1.0.0"},
    {NULL, NULL, NULL},
};

struct TerminalApp {
    char output[8192];
    char current_input[256];
    char current_file[256];
    char file_content[4096];
    Storage* storage;
    ThemeType active_theme;
    int edit_mode;
};

TerminalApp* terminal_app_alloc(void) {
    TerminalApp* app = malloc(sizeof(struct TerminalApp));
    memset(app->output, 0, sizeof(app->output));
    memset(app->current_input, 0, sizeof(app->current_input));
    memset(app->current_file, 0, sizeof(app->current_file));
    memset(app->file_content, 0, sizeof(app->file_content));
    app->storage = furi_record_open(RECORD_STORAGE);
    app->active_theme = ThemeDefault;
    app->edit_mode = 0;
    strcat(app->output, "FlipperLinux Terminal\n");
    return app;
}

void terminal_app_free(TerminalApp* app) {
    if (app) {
        if (app->storage) furi_record_close(RECORD_STORAGE);
        free(app);
    }
}

const char* terminal_app_get_output(TerminalApp* app) {
    return app->output;
}

void terminal_app_clear_output(TerminalApp* app) {
    memset(app->output, 0, sizeof(app->output));
}

void terminal_app_set_theme(TerminalApp* app, ThemeType theme) {
    app->active_theme = theme;
}

ThemeType terminal_app_get_active_theme(TerminalApp* app) {
    return app->active_theme;
}

static void cat_file(TerminalApp* app, const char* filename) {
    File* file = storage_file_alloc(app->storage);
    
    if (!storage_file_open(file, filename, FSAM_READ, FSOM_OPEN_EXISTING)) {
        strcat(app->output, "ERR: File not found\n");
        storage_file_free(file);
        return;
    }
    
    char buffer[512] = {0};
    storage_file_read(file, (uint8_t*)buffer, sizeof(buffer) - 1);
    
    strcat(app->output, "--- FILE ---\n");
    strcat(app->output, buffer);
    strcat(app->output, "\n--- END ---\n");
    
    storage_file_close(file);
    storage_file_free(file);
}

static void nano_file(TerminalApp* app, const char* filename) {
    File* file = storage_file_alloc(app->storage);
    
    if (!storage_file_open(file, filename, FSAM_READ, FSOM_OPEN_EXISTING)) {
        strcat(app->output, "New: ");
        strcat(app->output, filename);
        strcat(app->output, "\n");
    } else {
        char buffer[512] = {0};
        storage_file_read(file, (uint8_t*)buffer, sizeof(buffer) - 1);
        snprintf(app->file_content, sizeof(app->file_content), "%s", buffer);
        storage_file_close(file);
    }
    
    strncpy(app->current_file, filename, sizeof(app->current_file) - 1);
    app->edit_mode = 1;
    
    strcat(app->output, "Edit: ");
    strcat(app->output, filename);
    strcat(app->output, "\n");
    strcat(app->output, app->file_content);
    strcat(app->output, "\n");
    
    storage_file_free(file);
}

static void save_nano_file(TerminalApp* app) {
    File* file = storage_file_alloc(app->storage);
    
    if (!storage_file_open(file, app->current_file, FSAM_WRITE, FSOM_CREATE_ALWAYS)) {
        strcat(app->output, "ERR: Cannot save\n");
        storage_file_free(file);
        return;
    }
    
    storage_file_write(file, (uint8_t*)app->file_content, strlen(app->file_content));
    storage_file_close(file);
    storage_file_free(file);
    
    strcat(app->output, "Saved\n");
    app->edit_mode = 0;
}

static void fbt_install(TerminalApp* app, const char* pkg) {
    for (int i = 0; PACKAGE_REGISTRY[i].name; i++) {
        if (strcmp(PACKAGE_REGISTRY[i].name, pkg) == 0) {
            strcat(app->output, "OK\n");
            if (strcmp(pkg, "cinnamon") == 0) terminal_app_set_theme(app, ThemeCinnamon);
            if (strcmp(pkg, "kde") == 0) terminal_app_set_theme(app, ThemeKDE);
            return;
        }
    }
    strcat(app->output, "ERR\n");
}

void terminal_app_process_command(TerminalApp* app, const char* command) {
    strcat(app->output, "$ ");
    strcat(app->output, command);
    strcat(app->output, "\n");
    
    if (strstr(command, "cat ")) {
        const char* filename = command + 4;
        while (*filename == ' ') filename++;
        cat_file(app, filename);
    }
    else if (strstr(command, "nano ")) {
        const char* filename = command + 5;
        while (*filename == ' ') filename++;
        nano_file(app, filename);
    }
    else if (strstr(command, "help")) {
        strcat(app->output, "cat FILE\n");
        strcat(app->output, "nano FILE\n");
        strcat(app->output, "sudo fbt-install\n");
        strcat(app->output, "clear\n");
    }
    else if (strstr(command, "fbt-install")) {
        char* pkg = strstr(command, "install");
        if (pkg) {
            pkg += 8;
            while (*pkg == ' ') pkg++;
            char pkgname[32] = {0};
            sscanf(pkg, "%31s", pkgname);
            fbt_install(app, pkgname);
        }
    }
    else if (strstr(command, "clear")) {
        terminal_app_clear_output(app);
    }
    else if (strstr(command, "save") && app->edit_mode) {
        save_nano_file(app);
    }
}
