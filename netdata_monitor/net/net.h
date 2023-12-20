#ifndef __NET_H__
#define __NET_H__

#include <m1s_c906_xram_wifi.h>

void net_init();
int net_http_request_block(const char *host, uint16_t port, const char *uri, char *buf, int *len);
int net_get_ip_block(uint32_t *ip, uint32_t *mask, uint32_t *gw);

#endif
