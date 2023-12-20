#ifndef __NETDATA_API_H__
#define __NETDATA_API_H__

#define NETDATA_API_OK 0
#define NETDATA_API_ERR -1

int netdata_get_loads(double *loads);
int netdata_get_cpu(double *guest_nice, double *guest, double *steal, double *softirq, double *irq, double *user, double *system, double *nice, double *iowait);
int netdata_get_ram(double *free, double *used, double *buffers, double *cached);

#endif
