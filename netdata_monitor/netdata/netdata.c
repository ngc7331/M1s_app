#include <stdio.h>

/* FreeRTOS */
#include <FreeRTOS.h>
#include <task.h>

#include "../config.h"
#include "../net/net.h"
#include "api.h"
#include "netdata.h"

static netdata_entry_t entry[NETDATA_MAX_ENTRY];
static int entry_count = 0;

static struct {
    struct {
        double _1, _5, _15;
    } loads;
    struct {
        double guest_nice, guest, steal, softirq, irq, user, system, nice, iowait;
    } cpu;
    struct {
        double free, used, buffers, cached;
    } ram;
} data;

int netdata_add_entry(netdata_data_t type, double *buf) {
    if (entry_count >= NETDATA_MAX_ENTRY) {
        return -1;
    }
    entry[entry_count].type = type;
    entry[entry_count].buf = buf;
    entry_count++;
    return 0;
}

static void netdata_task_handler() {
    // update data
    if (netdata_get_loads(&data.loads._1) != NETDATA_API_OK) {
        printf("netdata_get_loads failed\r\n");
    }
    if (netdata_get_cpu(&data.cpu.guest_nice, &data.cpu.guest, &data.cpu.steal, &data.cpu.softirq,
                        &data.cpu.irq, &data.cpu.user, &data.cpu.system, &data.cpu.nice, &data.cpu.iowait) != NETDATA_API_OK) {
        printf("netdata_get_cpu failed\r\n");
    }
    if (netdata_get_ram(&data.ram.free, &data.ram.used, &data.ram.buffers, &data.ram.cached) != NETDATA_API_OK) {
        printf("netdata_get_ram failed\r\n");
    }
    // update entry
    for (int i = 0; i < entry_count; i++) {
        switch (entry[i].type) {
        case NETDATA_DATA_LOAD1: {
            *entry[i].buf = data.loads._1;
            break;
        }
        case NETDATA_DATA_LOAD5: {
            *entry[i].buf = data.loads._5;
            break;
        }
        case NETDATA_DATA_LOAD15: {
            *entry[i].buf = data.loads._15;
            break;
        }
        case NETDATA_DATA_CPU: {
            *entry[i].buf = data.cpu.guest_nice + data.cpu.guest + data.cpu.steal + data.cpu.softirq +
                            data.cpu.irq + data.cpu.user + data.cpu.system + data.cpu.nice + data.cpu.iowait;
            break;
        }
        case NETDATA_DATA_RAM: {
            double total = data.ram.free + data.ram.used + data.ram.buffers + data.ram.cached;
            if (total != 0)
                *entry[i].buf = data.ram.used * 100 / total;
            else
                *entry[i].buf = 0;
            break;
        }
        }
    }
}

void netdata_task() {
    while (1) {
        netdata_task_handler();
        vTaskDelay(NETDATA_REFRESH_PERIOD);
    }
    vTaskDelete(NULL);
}
