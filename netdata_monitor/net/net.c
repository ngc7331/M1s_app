#include "../config.h"
#include "../ui/ui.h"
#include "net.h"

void net_init() {
    m1s_xram_wifi_init();
    int ret = m1s_xram_wifi_connect(WLAN_SSID, WLAN_PSWD);

    char buf[64];
    sprintf(buf, "Connect to %s: %s", WLAN_SSID, ret ? "failed" : "success");
    ui_alert_send(ret ? UI_ALERT_ERROR : UI_ALERT_INFO, buf);
}

int net_http_request_block(const char *host, uint16_t port, const char *uri, char *buf, int *len) {
    int code;
    m1s_xram_wifi_http_request(host, port, uri);
    do {
        vTaskDelay(1);
    } while ((code = m1s_xram_wifi_http_response(buf, len)) == 0);
    return code;
}
