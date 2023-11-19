#include "../config.h"
#include "ui.h"

lv_obj_t *screen;
lv_disp_t *dispp;
lv_theme_t *theme;

// TODO: remove this
static void net_test_cb(lv_event_t *e) {
    void netdata_get_loads(double *);
    double buf[3];
    switch (lv_event_get_code(e)) {
    case LV_EVENT_CLICKED: netdata_get_loads(buf); break;
    default: return ;
    }
}

void ui_init() {
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

    // init alert window
    ui_alert_init();

    // TODO: remove these
    lv_obj_t *btn = lv_btn_create(screen);
    lv_obj_set_align(btn, LV_ALIGN_CENTER);
    lv_obj_set_width(btn, 100);
    lv_obj_set_height(btn, 100);
    lv_obj_add_event_cb(btn, net_test_cb, LV_EVENT_ALL, NULL);

    // tests
#ifdef DO_UI_ALERT_TEST
    ui_alert_send(UI_ALERT_INFO, "info test");
    ui_alert_send(UI_ALERT_WARN, "warn test");
    ui_alert_send(UI_ALERT_ERROR, "error test");
#endif
}
