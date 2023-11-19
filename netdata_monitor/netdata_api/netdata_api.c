#include "../config.h"
#include "../net/net.h"
#include "netdata_api.h"

void netdata_get_loads(double *loads) {
    const char *uri = "/api/v1/data?chart=system.load&points=1";
    char buf[128] = {0};
    // TODO: parse json data
    int len = net_http_request_block(NETDATA_HOST, NETDATA_PORT, uri, buf, 128);
    printf("%d: %s\n\r", len, buf);
}
