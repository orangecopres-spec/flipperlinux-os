#include <gui/gui.h>
#include <gui/view.h>
#include <gui/view_dispatcher.h>
#include <gui/modules/text_box.h>

void flipperlinux_about_view_alloc(View* view) {
    const char* credits_text =
        "─────────────────────────────────────\n"
        "        FlipperLinux-OS v1.0.0\n"
        "─────────────────────────────────────\n"
        "\n"
        "Based on Official Flipper Zero Firmware\n"
        "© 2023 Flipper Devices Inc.\n"
        "\n"
        "Modifications by FlipperLinux Team:\n"
        "  • Cinnamon Theme Integration\n"
        "  • KDE Plasma Theme Support\n"
        "  • Terminal Application\n"
        "  • fbt-install Package Manager\n"
        "\n"
        "Themes Inspired By:\n"
        "  • Linux Mint Cinnamon Desktop\n"
        "  • KDE Plasma Desktop Environment\n"
        "  • Ubuntu Yaru Design System\n"
        "\n"
        "Licensed under GPL v3.0\n"
        "https://github.com/flipperlinux/firmware\n"
        "─────────────────────────────────────";
    
    // Display this in a text box view
    // Implementation follows standard Flipper GUI patterns
}
