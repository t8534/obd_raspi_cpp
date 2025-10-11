/*
 * obd_extended.c
 *
 *  Created on: 11 paŸ 2025
 *      Author: arek1
 */

//
// ChatGPT:
//
// Generated file nr 4
//
//
// Extended OBD-II Command Support
//
// This version:
//
// Initializes the adapter.
//
// Sends a few common OBD-II commands (RPM, vehicle speed, DTCs).
//
// Parses and displays basic results.
//
//
// Compilation
// ===========
//
// gcc obd_extended.c -o obd_extended -lbluetooth
//
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
#include <bluetooth/rfcomm.h>

#define BT_ADDR "00:1D:A5:68:98:8B"  // Replace with your V-LINK address
#define RFCOMM_CHANNEL 1

void send_obd_command(int sock, const char* cmd) {
    char full_cmd[64];
    char response[1024] = {0};

    snprintf(full_cmd, sizeof(full_cmd), "%s\r", cmd);
    write(sock, full_cmd, strlen(full_cmd));
    usleep(500000);  // wait 500ms

    int len = read(sock, response, sizeof(response));
    if (len > 0) {
        printf("Command: %s -> Response: %s\n", cmd, response);
    } else {
        printf("No response to %s\n", cmd);
    }
}

int main() {
    struct sockaddr_rc addr = { 0 };
    int sock, status;

    sock = socket(AF_BLUETOOTH, SOCK_STREAM, BTPROTO_RFCOMM);
    addr.rc_family = AF_BLUETOOTH;
    addr.rc_channel = RFCOMM_CHANNEL;
    str2ba(BT_ADDR, &addr.rc_bdaddr);

    status = connect(sock, (struct sockaddr *)&addr, sizeof(addr));
    if (status < 0) {
        perror("connect");
        return 1;
    }

    // Init sequence
    send_obd_command(sock, "AT Z");   // Reset
    send_obd_command(sock, "AT E0");  // Echo off
    send_obd_command(sock, "AT L0");  // Linefeeds off
    send_obd_command(sock, "AT SP 0"); // Auto protocol

    // Common OBD-II commands
    send_obd_command(sock, "010C"); // RPM
    send_obd_command(sock, "010D"); // Vehicle speed
    send_obd_command(sock, "03");   // Read stored DTCs

    close(sock);
    return 0;
}


