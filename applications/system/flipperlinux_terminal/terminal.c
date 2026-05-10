#include <furi.h>
#include <furi_hal.h>
#include <gui/gui.h>
#include <gui/view_dispatcher.h>
#include <input/input.h>
#include "terminal_app.h"

// Forward declarations
typedef struct TerminalView TerminalView;
TerminalView* terminal_view_alloc(TerminalApp* terminal_app);
void terminal_view_free(TerminalView* view);
View* terminal_view_get_view(TerminalView* view);

typedef struct {
    Gui* gui;
    ViewDispatcher* view_dispatcher;
    TerminalApp* terminal_app;
    TerminalView* terminal_view;
} TerminalMainApp;

static uint32_t terminal_exit_callback(void* context) {
    UNUSED(context);
    return VIEW_NONE;
}

static TerminalMainApp* app_alloc(void) {
    TerminalMainApp* app = malloc(sizeof(TerminalMainApp));
    
    app->gui = furi_record_open(RECORD_GUI);
    app->view_dispatcher = view_dispatcher_alloc();
    app->terminal_app = terminal_app_alloc();
    app->terminal_view = terminal_view_alloc(app->terminal_app);
    
    view_dispatcher_attach_to_gui(app->view_dispatcher, app->gui, ViewDispatcherTypeFullscreen);
    view_dispatcher_add_view(app->view_dispatcher, 0, terminal_view_get_view(app->terminal_view));
    
    view_set_previous_callback(terminal_view_get_view(app->terminal_view), terminal_exit_callback);
    view_dispatcher_switch_to_view(app->view_dispatcher, 0);
    
    return app;
}

static void app_free(TerminalMainApp* app) {
    view_dispatcher_remove_view(app->view_dispatcher, 0);
    terminal_view_free(app->terminal_view);
    view_dispatcher_free(app->view_dispatcher);
    terminal_app_free(app->terminal_app);
    furi_record_close(RECORD_GUI);
    free(app);
}

int32_t flipperlinux_terminal_app(void* p) {
    UNUSED(p);
    TerminalMainApp* app = app_alloc();
    view_dispatcher_run(app->view_dispatcher);
    app_free(app);
    return 0;
}
