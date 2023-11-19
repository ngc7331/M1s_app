/* FreeRTOS */
#include <FreeRTOS.h>
#include <task.h>

/* lvgl */
#include <lvgl.h>

/* project */
#include "config.h"
#include "ui/ui.h"
#include "net/net.h"

static void lvgl_task(void *param) {
    while (1) {
        lv_task_handler();
        vTaskDelay(1);
    }
    vTaskDelete(NULL);
}

void main() {
    lv_init();
    lv_port_disp_init();
    lv_port_indev_init();

    ui_init();
    net_init();

    xTaskCreate(lvgl_task, (char *)"lvgl task", 512, NULL, 15, NULL);
}
