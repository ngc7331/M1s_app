/* FreeRTOS */
#include <FreeRTOS.h>
#include <task.h>

#include "../config.h"
#include "../ui/ui.h"
#include "net.h"

#define NET_PRINT_BUFSIZE 128
static char net_print_buf[NET_PRINT_BUFSIZE];

static int net_ready = 0;

static void net_init_wait_for_ip() {
    uint32_t ip;
    while (1) {
        if (net_get_ip_block(&ip, NULL, NULL)) {
            ui_alert_send(UI_ALERT_ERROR, "Get IP failed");
            continue;
        }
        if (ip != 0) break;
        vTaskDelay(1000);
    }
    snprintf(net_print_buf, NET_PRINT_BUFSIZE, "Get IP success: %d.%d.%d.%d", ip & 0xff, (ip >> 8) & 0xff, (ip >> 16) & 0xff, (ip >> 24) & 0xff);
    ui_alert_send(UI_ALERT_INFO, net_print_buf);
    net_ready = 1;
    vTaskDelete(NULL);
}

void net_init() {
    m1s_xram_wifi_init();
    int ret = m1s_xram_wifi_connect(WLAN_SSID, WLAN_PSWD);

    snprintf(net_print_buf, NET_PRINT_BUFSIZE, "Trying to connect to %s: %s", WLAN_SSID, ret ? "failed" : "success");
    ui_alert_send(ret ? UI_ALERT_ERROR : UI_ALERT_INFO, net_print_buf);

    xTaskCreate(net_init_wait_for_ip, (char *)"net init wait for ip", 512, NULL, 10, NULL);
}

int net_http_request_block(const char *host, uint16_t port, const char *uri, char *buf, int *len) {
    if (!net_ready) return -1;
    int code;
    m1s_xram_wifi_http_request(host, port, uri);
    do {
        vTaskDelay(1);
    } while ((code = m1s_xram_wifi_http_response(buf, len)) == 0);
    return code;
}

int net_get_ip_block(uint32_t *ip, uint32_t *mask, uint32_t *gw) {
    int code;
    m1s_xram_wifi_get_ip_request();
    do {
        vTaskDelay(1);
    } while ((code = m1s_xram_wifi_get_ip_response(ip, mask, gw)) == 0); // -1 fail, 1 succ, 0 not ready
    return code == 1 ? 0 : code; // -1 fail, 0 succ
}
