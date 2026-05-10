#include "applications.h"
#include <assets_icons.h>
const char* FLIPPER_AUTORUN_APP_NAME = "";
extern int32_t cli_vcp_srv(void* p);
extern int32_t bt_srv(void* p);
extern int32_t dialogs_srv(void* p);
extern int32_t dolphin_srv(void* p);
extern int32_t desktop_srv(void* p);
extern int32_t gui_srv(void* p);
extern int32_t input_srv(void* p);
extern int32_t loader_srv(void* p);
extern int32_t notification_srv(void* p);
extern int32_t power_srv(void* p);
extern int32_t storage_srv(void* p);
const FlipperInternalApplication FLIPPER_SERVICES[] = {

    {.app = cli_vcp_srv,
     .name = "CliVcpSrv",
     .appid = "cli_vcp", 
     .stack_size = 1024,
     .icon = NULL,
     .flags = FlipperInternalApplicationFlagDefault },

    {.app = bt_srv,
     .name = "BtSrv",
     .appid = "bt", 
     .stack_size = 1024,
     .icon = NULL,
     .flags = FlipperInternalApplicationFlagDefault },

    {.app = dialogs_srv,
     .name = "DialogsSrv",
     .appid = "dialogs", 
     .stack_size = 1024,
     .icon = NULL,
     .flags = FlipperInternalApplicationFlagDefault },

    {.app = dolphin_srv,
     .name = "DolphinSrv",
     .appid = "dolphin", 
     .stack_size = 1024,
     .icon = NULL,
     .flags = FlipperInternalApplicationFlagDefault },

    {.app = desktop_srv,
     .name = "DesktopSrv",
     .appid = "desktop", 
     .stack_size = 2048,
     .icon = NULL,
     .flags = FlipperInternalApplicationFlagDefault },

    {.app = gui_srv,
     .name = "GuiSrv",
     .appid = "gui", 
     .stack_size = 2048,
     .icon = NULL,
     .flags = FlipperInternalApplicationFlagDefault },

    {.app = input_srv,
     .name = "InputSrv",
     .appid = "input", 
     .stack_size = 1024,
     .icon = NULL,
     .flags = FlipperInternalApplicationFlagDefault },

    {.app = loader_srv,
     .name = "LoaderSrv",
     .appid = "loader", 
     .stack_size = 2048,
     .icon = NULL,
     .flags = FlipperInternalApplicationFlagDefault },

    {.app = notification_srv,
     .name = "NotificationSrv",
     .appid = "notification", 
     .stack_size = 1536,
     .icon = NULL,
     .flags = FlipperInternalApplicationFlagDefault },

    {.app = power_srv,
     .name = "PowerSrv",
     .appid = "power", 
     .stack_size = 1024,
     .icon = NULL,
     .flags = FlipperInternalApplicationFlagDefault },

    {.app = storage_srv,
     .name = "StorageSrv",
     .appid = "storage", 
     .stack_size = 3072,
     .icon = NULL,
     .flags = FlipperInternalApplicationFlagDefault }
};
const size_t FLIPPER_SERVICES_COUNT = COUNT_OF(FLIPPER_SERVICES);
extern int32_t js_app(void* p);
extern int32_t updater_srv(void* p);
const FlipperInternalApplication FLIPPER_SYSTEM_APPS[] = {

    {.app = js_app,
     .name = "JS Runner",
     .appid = "js_app", 
     .stack_size = 2048,
     .icon = NULL,
     .flags = FlipperInternalApplicationFlagDefault },

    {.app = updater_srv,
     .name = "UpdaterApp",
     .appid = "updater_app", 
     .stack_size = 2048,
     .icon = NULL,
     .flags = FlipperInternalApplicationFlagDefault }
};
const size_t FLIPPER_SYSTEM_APPS_COUNT = COUNT_OF(FLIPPER_SYSTEM_APPS);
const FlipperInternalApplication FLIPPER_APPS[] = {

};
const size_t FLIPPER_APPS_COUNT = COUNT_OF(FLIPPER_APPS);
const FlipperInternalApplication FLIPPER_DEBUG_APPS[] = {

};
const size_t FLIPPER_DEBUG_APPS_COUNT = COUNT_OF(FLIPPER_DEBUG_APPS);
extern int32_t bt_settings_app(void* p);
extern int32_t notification_settings_app(void* p);
extern int32_t storage_settings_app(void* p);
extern int32_t power_settings_app(void* p);
extern int32_t desktop_settings_app(void* p);
extern int32_t passport_app(void* p);
extern int32_t system_settings_app(void* p);
extern int32_t expansion_settings_app(void* p);
extern int32_t clock_settings(void* p);
extern int32_t about_settings_app(void* p);
const FlipperInternalApplication FLIPPER_SETTINGS_APPS[] = {

    {.app = bt_settings_app,
     .name = "Bluetooth",
     .appid = "bt_settings", 
     .stack_size = 1024,
     .icon = NULL,
     .flags = FlipperInternalApplicationFlagDefault },

    {.app = notification_settings_app,
     .name = "LCD and Notifications",
     .appid = "notification_settings", 
     .stack_size = 1024,
     .icon = NULL,
     .flags = FlipperInternalApplicationFlagDefault },

    {.app = storage_settings_app,
     .name = "Storage",
     .appid = "storage_settings", 
     .stack_size = 2048,
     .icon = NULL,
     .flags = FlipperInternalApplicationFlagDefault },

    {.app = power_settings_app,
     .name = "Power",
     .appid = "power_settings", 
     .stack_size = 1024,
     .icon = NULL,
     .flags = FlipperInternalApplicationFlagInsomniaSafe },

    {.app = desktop_settings_app,
     .name = "Desktop",
     .appid = "desktop_settings", 
     .stack_size = 1024,
     .icon = NULL,
     .flags = FlipperInternalApplicationFlagDefault },

    {.app = passport_app,
     .name = "Passport",
     .appid = "passport", 
     .stack_size = 1024,
     .icon = NULL,
     .flags = FlipperInternalApplicationFlagDefault },

    {.app = system_settings_app,
     .name = "System",
     .appid = "system_settings", 
     .stack_size = 1024,
     .icon = NULL,
     .flags = FlipperInternalApplicationFlagDefault },

    {.app = expansion_settings_app,
     .name = "Expansion Modules",
     .appid = "expansion_settings", 
     .stack_size = 1024,
     .icon = NULL,
     .flags = FlipperInternalApplicationFlagDefault },

    {.app = clock_settings,
     .name = "Clock & Alarm",
     .appid = "clock_settings", 
     .stack_size = 1024,
     .icon = NULL,
     .flags = FlipperInternalApplicationFlagDefault },

    {.app = about_settings_app,
     .name = "About",
     .appid = "about", 
     .stack_size = 1024,
     .icon = NULL,
     .flags = FlipperInternalApplicationFlagDefault }
};
const size_t FLIPPER_SETTINGS_APPS_COUNT = COUNT_OF(FLIPPER_SETTINGS_APPS);
extern void cli_on_system_start(void);
extern void rpc_on_system_start(void);
extern void crypto_on_system_start(void);
extern void bt_on_system_start(void);
extern void power_on_system_start(void);
extern void storage_on_system_start(void);
extern void locale_on_system_start(void);
extern void loader_on_system_start(void);
extern void updater_on_system_start(void);
extern void expansion_on_system_start(void);
extern void js_app_on_system_start(void);
extern void region_on_system_start(void);
extern void clock_settings_start(void);
const FlipperInternalOnStartHook FLIPPER_ON_SYSTEM_START[] = {
cli_on_system_start,
rpc_on_system_start,
crypto_on_system_start,
bt_on_system_start,
power_on_system_start,
storage_on_system_start,
locale_on_system_start,
loader_on_system_start,
updater_on_system_start,
expansion_on_system_start,
js_app_on_system_start,
region_on_system_start,
clock_settings_start
};
const size_t FLIPPER_ON_SYSTEM_START_COUNT = COUNT_OF(FLIPPER_ON_SYSTEM_START);
extern int32_t archive_app(void* p);
const FlipperInternalApplication FLIPPER_ARCHIVE = 
    {.app = archive_app,
     .name = "Archive",
     .appid = "archive", 
     .stack_size = 4096,
     .icon = &A_FileManager_14,
     .flags = FlipperInternalApplicationFlagDefault };
const FlipperExternalApplication FLIPPER_EXTERNAL_APPS[] = {

    {
     .name = "Sub-GHz",
     .icon = &A_Sub1ghz_14,
     .path = "/ext/apps/Sub-GHz/subghz.fap" },

    {
     .name = "125 kHz RFID",
     .icon = &A_125khz_14,
     .path = "/ext/apps/RFID/lfrfid.fap" },

    {
     .name = "NFC",
     .icon = &A_NFC_14,
     .path = "/ext/apps/NFC/nfc.fap" },

    {
     .name = "Infrared",
     .icon = &A_Infrared_14,
     .path = "/ext/apps/Infrared/infrared.fap" },

    {
     .name = "GPIO",
     .icon = &A_GPIO_14,
     .path = "/ext/apps/GPIO/gpio.fap" },

    {
     .name = "iButton",
     .icon = &A_iButton_14,
     .path = "/ext/apps/iButton/ibutton.fap" },

    {
     .name = "Bad USB",
     .icon = &A_BadUsb_14,
     .path = "/ext/apps/USB/bad_usb.fap" },

    {
     .name = "U2F",
     .icon = &A_U2F_14,
     .path = "/ext/apps/USB/u2f.fap" }
};
const size_t FLIPPER_EXTERNAL_APPS_COUNT = COUNT_OF(FLIPPER_EXTERNAL_APPS);