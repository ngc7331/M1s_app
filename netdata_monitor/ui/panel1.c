#include <stdio.h>

#include "../config.h"
#include "../netdata/netdata.h"
#include "ui.h"

static lv_obj_t *panel1;
static lv_obj_t *arc_outer;
static lv_obj_t *label_outer;
static lv_obj_t *arc_inner;
static lv_obj_t *label_inner;

static double cpu = 0;
static double ram = 0;
static char cpu_buf[16];
static char ram_buf[16];

void ui_panel1_init() {
    /* ui */
    panel1 = lv_obj_create(screen);
    lv_obj_set_width(panel1, 115);
    lv_obj_set_height(panel1, 115);
    lv_obj_set_x(panel1, 5);
    lv_obj_set_y(panel1, 25);
    lv_obj_clear_flag(panel1, LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_set_style_pad_left(panel1, 5, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(panel1, 5, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(panel1, 5, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(panel1, 5, LV_PART_MAIN | LV_STATE_DEFAULT);

    arc_outer = lv_arc_create(panel1);
    lv_obj_set_width(arc_outer, 100);
    lv_obj_set_height(arc_outer, 100);
    lv_obj_clear_flag(arc_outer, LV_OBJ_FLAG_CLICKABLE);
    lv_arc_set_bg_angles(arc_outer,0,230);
    lv_arc_set_mode(arc_outer, LV_ARC_MODE_REVERSE);
    lv_obj_set_style_arc_color(arc_outer, lv_color_hex(0xFF88FF), LV_PART_INDICATOR | LV_STATE_DEFAULT);
    lv_obj_set_style_arc_opa(arc_outer, 255, LV_PART_INDICATOR| LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(arc_outer, lv_color_hex(0xFFFFFF), LV_PART_KNOB | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(arc_outer, 0, LV_PART_KNOB| LV_STATE_DEFAULT);

    label_outer = lv_label_create(panel1);
    lv_obj_set_width(label_outer, LV_SIZE_CONTENT);
    lv_obj_set_height(label_outer, LV_SIZE_CONTENT);
    lv_obj_set_x(label_outer, 30);
    lv_obj_set_y(label_outer, 2);
    strncpy(cpu_buf, "C: 0.00%%", sizeof(cpu_buf));
    lv_label_set_text_static(label_outer, cpu_buf);

    arc_inner = lv_arc_create(panel1);
    lv_obj_set_width(arc_inner, 70);
    lv_obj_set_height(arc_inner, 70);
    lv_obj_set_x(arc_inner, 15);
    lv_obj_set_y(arc_inner, 15);
    lv_obj_clear_flag(arc_inner, LV_OBJ_FLAG_CLICKABLE);
    lv_arc_set_bg_angles(arc_inner,0,230);
    lv_arc_set_mode(arc_inner, LV_ARC_MODE_REVERSE);
    lv_obj_set_style_arc_color(arc_inner, lv_color_hex(0x8888FF), LV_PART_INDICATOR | LV_STATE_DEFAULT);
    lv_obj_set_style_arc_opa(arc_inner, 255, LV_PART_INDICATOR| LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(arc_inner, lv_color_hex(0xFFFFFF), LV_PART_KNOB | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(arc_inner, 0, LV_PART_KNOB| LV_STATE_DEFAULT);

    label_inner = lv_label_create(panel1);
    lv_obj_set_width(label_inner, LV_SIZE_CONTENT);
    lv_obj_set_height(label_inner, LV_SIZE_CONTENT);
    lv_obj_set_x(label_inner, 40);
    lv_obj_set_y(label_inner, 18);
    strncpy(ram_buf, "R: 0.0%%", sizeof(ram_buf));
    lv_label_set_text_static(label_inner, ram_buf);

    /* register netdata entry */
    netdata_add_entry(NETDATA_DATA_CPU, &cpu);
    netdata_add_entry(NETDATA_DATA_RAM, &ram);
}

void ui_panel1_data_update() {
    lv_arc_set_value(arc_outer, cpu);
    snprintf(cpu_buf+3, sizeof(cpu_buf)-3, "%.2f%%", cpu);
    lv_label_set_text_static(label_outer, NULL);
    lv_arc_set_value(arc_inner, ram);
    snprintf(ram_buf+3, sizeof(ram_buf)-3, "%.1f%%", ram);
    lv_label_set_text_static(label_inner, NULL);
}
