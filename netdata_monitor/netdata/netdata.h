#ifndef __NETDATA_H__
#define __NETDATA_H__

typedef enum {
    NETDATA_DATA_LOAD1,
    NETDATA_DATA_LOAD5,
    NETDATA_DATA_LOAD15,
    NETDATA_DATA_CPU,
    NETDATA_DATA_RAM,
} netdata_data_t;

#define NETDATA_REFRESH_PERIOD 5000 // ms
#define NETDATA_MAX_ENTRY 64
typedef struct {
    netdata_data_t type;
    double *buf;
} netdata_entry_t;

int netdata_add_entry(netdata_data_t type, double *buf);
void netdata_task();

#endif
