#include "../config.h"
#include "../utils/utils.h"
#include "ui.h"

#include <stdio.h>

static lv_obj_t *alert_window;
static int alert_num;
static queue_t alert_queue;

static void alert_window_cb(lv_event_t *e) {
    switch (lv_event_get_code(e)) {
    case LV_EVENT_CLICKED: ui_alert_clear(); break;
    default: return ;
    }
}

void ui_alert_init() {
    /* init lvgl label */
    alert_window = lv_label_create(screen);
    // text style
    lv_obj_set_width(alert_window, LV_SIZE_CONTENT);
    lv_obj_set_height(alert_window, LV_SIZE_CONTENT);
    lv_obj_set_align(alert_window, LV_ALIGN_CENTER);
    // allow click and register callback fn
    lv_obj_add_flag(alert_window, LV_OBJ_FLAG_CLICKABLE);
    lv_obj_add_event_cb(alert_window, alert_window_cb, LV_EVENT_ALL, NULL);
    // background style
    lv_obj_set_style_radius(alert_window, 4, LV_PART_MAIN| LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(alert_window, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT );
    lv_obj_set_style_bg_opa(alert_window, 192, LV_PART_MAIN| LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(alert_window, 8, LV_PART_MAIN| LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(alert_window, 8, LV_PART_MAIN| LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(alert_window, 4, LV_PART_MAIN| LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(alert_window, 4, LV_PART_MAIN| LV_STATE_DEFAULT);
    // hide by default
    ui_alert_hide();

    /* init internal info */
    alert_num = 0;
    queue_init(&alert_queue);
}

void ui_alert_display(ui_alert_level_t level, char *msg) {
    const uint32_t color_table[] = {
        [UI_ALERT_INFO]  = 0x00ff00,
        [UI_ALERT_WARN]  = 0xffff00,
        [UI_ALERT_ERROR] = 0xff0000,
    };
    lv_obj_set_style_text_color(alert_window, lv_color_hex(color_table[level]), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_label_set_text(alert_window, msg);
    lv_obj_clear_flag(alert_window, LV_OBJ_FLAG_HIDDEN);
    lv_obj_move_foreground(alert_window);
}

void ui_alert_hide() {
    lv_obj_add_flag(alert_window, LV_OBJ_FLAG_HIDDEN);
}

void ui_alert_send(ui_alert_level_t level, char *msg) {
    if (alert_num++ == 0) {
        ui_alert_display(level, msg);
    } else {
        ui_alert_t *alert = lv_mem_alloc(sizeof(ui_alert_t));
        alert->level = level;
        alert->msg = lv_mem_alloc(strlen(msg));
        strcpy(alert->msg, msg);
        queue_enqueue(&alert_queue, alert);
    }
}

void ui_alert_clear() {
    if (--alert_num == 0) {
        ui_alert_hide();
    } else {
        ui_alert_t *alert = (ui_alert_t *) queue_dequeue(&alert_queue);
        LV_ASSERT(alert != NULL);
        ui_alert_display(alert->level, alert->msg);
        lv_mem_free(alert);
    }
}
