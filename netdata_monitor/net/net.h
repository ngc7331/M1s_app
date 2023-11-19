#ifndef __NET_H__
#define __NET_H__

#include <m1s_c906_xram_wifi.h>

void net_init();
int net_http_request_block(const char *host, uint16_t port, const char *uri, char *buf, int bufsize);

#endif
