/*
 * obd_discovery.c
 *
 *  Created on: 11 paŸ 2025
 *      Author: arek1
 */

//
// ChatGPT:
//
// Generated file nr 3
//
//
// Automatic Device Discovery via Bluetooth Inquiry
//
// This version:
//
// Scans for nearby Bluetooth devices.
//
// Displays the found devices and names.
//
// Automatically tries to connect to the first matching device with “V-LINK” in its name.
//
// Compilation
// ===========
//
// gcc obd_discovery.c -o obd_discovery -lbluetooth
//
// Optional Output Example
// =======================
//
// Found 00:1D:A5:68:98:8B - V-LINK OBD
// Connecting to V-LINK at 00:1D:A5:68:98:8B...
// Response: V-LINK 1.5 ELM327 compatible
//
// Command: 010C -> Response: 41 0C 1A F8
// Command: 010D -> Response: 41 0D 28
// Command: 03   -> Response: 43 01 33 00 00
//
//
// OBD-II Decoder Example (optional)
// =================================
//
// RPM = ((A * 256) + B) / 4
// Speed = A (in km/h)
// DTCs = Each pair of bytes decoded per SAE J1979
//




#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

#include <sys/socket.h>
#include <bluetooth/bluetooth.h>
#include <bluetooth/hci.h>
#include <bluetooth/hci_lib.h>
#include <bluetooth/rfcomm.h>

#define CMD "AT I\r"
#define RFCOMM_CHANNEL 1

int discover_vlink_device(bdaddr_t *bdaddr_out) {
    inquiry_info *ii = NULL;
    int max_rsp, num_rsp;
    int dev_id, sock, len, flags;
    char addr[19] = { 0 };
    char name[248] = { 0 };

    dev_id = hci_get_route(NULL);
    sock = hci_open_dev(dev_id);
    if (dev_id < 0 || sock < 0) {
        perror("opening socket");
        return -1;
    }

    len = 8;  // ~10 seconds
    max_rsp = 255;
    flags = IREQ_CACHE_FLUSH;
    ii = (inquiry_info*)malloc(max_rsp * sizeof(inquiry_info));

    printf("Scanning for devices...\n");
    num_rsp = hci_inquiry(dev_id, len, max_rsp, NULL, &ii, flags);
    if (num_rsp < 0) {
        perror("hci_inquiry");
        free(ii);
        close(sock);
        return -1;
    }

    for (int i = 0; i < num_rsp; i++) {
        ba2str(&(ii+i)->bdaddr, addr);
        memset(name, 0, sizeof(name));
        if (hci_read_remote_name(sock, &(ii+i)->bdaddr, sizeof(name), name, 0) < 0)
            strcpy(name, "[unknown]");

        printf("Found %s - %s\n", addr, name);

        if (strstr(name, "V-LINK") != NULL || strstr(name, "OBD") != NULL) {
            *bdaddr_out = (ii+i)->bdaddr;
            free(ii);
            close(sock);
            return 0;
        }
    }

    free(ii);
    close(sock);
    return -1;
}

int main() {
    struct sockaddr_rc addr = { 0 };
    int sock, status;
    char buf[1024] = { 0 };
    bdaddr_t target_bdaddr;

    if (discover_vlink_device(&target_bdaddr) != 0) {
        fprintf(stderr, "V-LINK device not found.\n");
        return 1;
    }

    char bt_addr_str[19] = {0};
    ba2str(&target_bdaddr, bt_addr_str);
    printf("Connecting to V-LINK at %s...\n", bt_addr_str);

    sock = socket(AF_BLUETOOTH, SOCK_STREAM, BTPROTO_RFCOMM);
    addr.rc_family = AF_BLUETOOTH;
    addr.rc_channel = RFCOMM_CHANNEL;
    addr.rc_bdaddr = target_bdaddr;

    status = connect(sock, (struct sockaddr *)&addr, sizeof(addr));
    if (status < 0) {
        perror("connect");
        return 1;
    }

    write(sock, CMD, strlen(CMD));
    usleep(500000);  // wait
    read(sock, buf, sizeof(buf));
    printf("Response: %s\n", buf);

    close(sock);
    return 0;
}

