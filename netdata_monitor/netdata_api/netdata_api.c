#include "../config.h"
#include "../net/net.h"
#include "netdata_api.h"

void netdata_get_loads(double *loads) {
    const char *uri = "/api/v1/data?chart=system.load&points=1";
    char buf[512] = {0};
    int len = sizeof(buf);
    // TODO: parse json data
    int code = net_http_request_block(NETDATA_HOST, NETDATA_PORT, uri, buf, &len);
    printf("%d: %s\n\r", code, buf);
}
