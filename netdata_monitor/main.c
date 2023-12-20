/* FreeRTOS */
#include <FreeRTOS.h>
#include <task.h>

/* project */
#include "config.h"
#include "ui/ui.h"
#include "net/net.h"
#include "netdata/netdata.h"

void main() {
    ui_init();
    net_init();

    xTaskCreate(ui_task, (char *)"ui", 4096, NULL, 15, NULL);
    xTaskCreate(netdata_task, (char *)"netdata", 1024, NULL, 14, NULL);
}
