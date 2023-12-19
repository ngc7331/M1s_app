#include "../config.h"
#include "../net/net.h"
#include "../ui/ui.h"
#include "api.h"

#define CONCAT(A, B) A##B

#define NETDATA_ENDPOINT "/api/v1/data"

#define NETDATA_CHART_LOAD   "system.load"

#define NETDATA_POINTS "1"
#define NETDATA_FORMAT "csv"

#define NETDATA_URI(X) NETDATA_ENDPOINT "?chart=" CONCAT(NETDATA_CHART_, X) "&points=" NETDATA_POINTS "&format=" NETDATA_FORMAT

static char api_buf[256] = {0};

#define NETDATA_REQUEST(X, n, fmt, ...) { \
    int len = sizeof(api_buf); \
    int code = net_http_request_block(NETDATA_HOST, NETDATA_PORT, NETDATA_URI(X), api_buf, &len); \
    if (code != 200) { \
        printf("netdata_get_" #X ": http request failed, code: %d\r\n", code); \
        return NETDATA_API_ERR; \
    } \
    if (sscanf(api_buf, "%*[^\n]\n%*[^,]," fmt, __VA_ARGS__) != n) { \
        printf("netdata_get_" #X ": sscanf failed, raw: %s\r\n", api_buf); \
        return NETDATA_API_ERR; \
    } \
    return NETDATA_API_OK; \
}

// params: loads[3]
int netdata_get_loads(double *loads) {
    NETDATA_REQUEST(LOAD, 3, "%lf,%lf,%lf", &loads[0], &loads[1], &loads[2]);
}
