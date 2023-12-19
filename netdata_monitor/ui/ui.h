#ifndef __UI_H__
#define __UI_H__

#include <lvgl.h>
#include <lv_port_disp.h>
#include <lv_port_indev.h>

/* ui */
extern lv_obj_t *screen;
void ui_init();
void ui_task();

/* alert */
typedef enum {
    UI_ALERT_INFO,
    UI_ALERT_WARN,
    UI_ALERT_ERROR,
} ui_alert_level_t;

typedef struct {
    ui_alert_level_t level;
    char *msg;
} ui_alert_t;

void ui_alert_init();
void ui_alert_display(ui_alert_level_t level, char *msg);
void ui_alert_hide();
void ui_alert_send(ui_alert_level_t level, char *msg);
void ui_alert_clear();

#endif
