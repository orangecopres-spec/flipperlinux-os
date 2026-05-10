#include <gui/gui.h>
#include <gui/view.h>
#include <furi.h>
#include <stdlib.h>
#include <string.h>
#include <input/input.h>
#include "terminal_app.h"

typedef struct {
    View* view;
    TerminalApp* terminal_app;
    char input_buffer[256];
    size_t input_pos;
} TerminalView;

static void terminal_view_draw_callback(Canvas* canvas, void* context) {
    TerminalView* view_ctx = context;
    ThemeType theme = terminal_app_get_active_theme(view_ctx->terminal_app);
    
    // Background
    canvas_set_color(canvas, ColorBlack);
    canvas_draw_box(canvas, 0, 0, 128, 64);
    
    // Border
    canvas_set_color(canvas, ColorWhite);
    canvas_draw_frame(canvas, 0, 0, 128, 64);
    
    // Header with theme indicator
    canvas_draw_line(canvas, 0, 10, 128, 10);
    canvas_set_font(canvas, FontPrimary);
    canvas_draw_str(canvas, 3, 8, "Terminal");
    
    // Theme indicator
    const char* theme_label = "STD";
    if (theme == ThemeCinnamon) theme_label = "CIN";
    else if (theme == ThemeKDE) theme_label = "KDE";
    
    canvas_draw_str(canvas, 110, 8, theme_label);
    
    // Output area (simulate scrolling)
    canvas_set_font(canvas, FontSecondary);
    const char* output = terminal_app_get_output(view_ctx->terminal_app);
    
    // Draw last few lines of output
    char output_copy[512] = {0};
    strncpy(output_copy, output, sizeof(output_copy) - 1);
    
    // Simple line wrapping for small display
    canvas_draw_str(canvas, 2, 22, ">");
    canvas_draw_str(canvas, 12, 22, output_copy);
    
    // Input line
    canvas_draw_line(canvas, 0, 50, 128, 50);
    canvas_set_font(canvas, FontSecondary);
    canvas_draw_str(canvas, 2, 58, "$ ");
    
    if (view_ctx->input_pos > 0) {
        char display_input[64] = {0};
        strncpy(display_input, view_ctx->input_buffer, 
                view_ctx->input_pos < 60 ? view_ctx->input_pos : 59);
        canvas_draw_str(canvas, 15, 58, display_input);
    }
    
    // Cursor
    canvas_draw_str(canvas, 15 + (view_ctx->input_pos * 4), 58, "_");
}

static bool terminal_view_input_callback(InputEvent* event, void* context) {
    TerminalView* view_ctx = context;
    
    if (event->type == InputTypePress || event->type == InputTypeRepeat) {
        if (event->key == InputKeyBack) {
            if (view_ctx->input_pos > 0) {
                view_ctx->input_pos--;
                view_ctx->input_buffer[view_ctx->input_pos] = '\0';
            }
        } else if (event->key == InputKeyOk) {
            if (view_ctx->input_pos > 0) {
                terminal_app_process_command(view_ctx->terminal_app, 
                                            view_ctx->input_buffer);
                memset(view_ctx->input_buffer, 0, sizeof(view_ctx->input_buffer));
                view_ctx->input_pos = 0;
            }
        }
    }
    
    return false;
}

TerminalView* terminal_view_alloc(TerminalApp* terminal_app) {
    TerminalView* view = malloc(sizeof(TerminalView));
    view->view = view_alloc();
    view->terminal_app = terminal_app;
    view->input_pos = 0;
    memset(view->input_buffer, 0, sizeof(view->input_buffer));
    
    view_set_draw_callback(view->view, terminal_view_draw_callback);
    view_set_input_callback(view->view, terminal_view_input_callback);
    view_set_context(view->view, view);
    
    return view;
}

void terminal_view_free(TerminalView* view) {
    if (view) {
        view_free(view->view);
        free(view);
    }
}

View* terminal_view_get_view(TerminalView* view) {
    return view->view;
}
