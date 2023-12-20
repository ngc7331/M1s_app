#include <stdio.h>

/* FreeRTOS */
#include <FreeRTOS.h>
#include <task.h>

#include "../config.h"
#include "net/net.h"
#include "ui.h"

lv_obj_t *screen;
lv_disp_t *dispp;
lv_theme_t *theme;
static lv_obj_t *ip_label;
static char ip_buf[20];

void ui_init() {
    // init lvgl
    lv_init();
    lv_port_disp_init();
    lv_port_indev_init();
    // init display
    dispp = lv_disp_get_default();
    theme = lv_theme_default_init(
        dispp,
        lv_palette_main(LV_PALETTE_BLUE),
        lv_palette_main(LV_PALETTE_RED),
        false,
        LV_FONT_DEFAULT
    );
    lv_disp_set_theme(dispp, theme);

    // init screen
    screen = lv_obj_create(NULL);
    lv_disp_load_scr(screen);

    // init ip label
    ip_label = lv_label_create(screen);
    lv_obj_set_width(ip_label, LV_SIZE_CONTENT);
    lv_obj_set_height(ip_label, LV_SIZE_CONTENT);
    lv_obj_set_x(ip_label, 10);
    lv_obj_set_y(ip_label, 5);
    strncpy(ip_buf, "IP: 0.0.0.0", sizeof(ip_buf));
    lv_label_set_text_static(ip_label, ip_buf);

    // init alert window
    ui_alert_init();

    // tests
#ifdef DO_UI_ALERT_TEST
    ui_alert_send(UI_ALERT_INFO, "info test");
    ui_alert_send(UI_ALERT_WARN, "warn test");
    ui_alert_send(UI_ALERT_ERROR, "error test");
    ui_alert_send(UI_ALERT_INFO, "very loooooooooooooooooong info test");
#endif

    // init panels
    ui_panel1_init();
}

static void ui_data_update() {
    // update ip label
    snprintf(ip_buf+4, sizeof(ip_buf)-4, "%d.%d.%d.%d", ip & 0xff, (ip >> 8) & 0xff, (ip >> 16) & 0xff, (ip >> 24) & 0xff);
    lv_label_set_text_static(ip_label, NULL);
    // update panels
    ui_panel1_data_update();
}

void ui_task() {
    while (1) {
        ui_data_update();
        lv_task_handler();
        vTaskDelay(1);
    }
    vTaskDelete(NULL);
}
