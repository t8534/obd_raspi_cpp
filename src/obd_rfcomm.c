/*
 * obd_rfcomm.c
 *
 *  Created on: 11 paŸ 2025
 *      Author: arek1
 */

//
// ChatGPT:
//
// Generated file nr 2
//
//
// Below is a C code example that uses raw RFCOMM sockets via the Bluetooth API (BlueZ stack)
// instead of accessing /dev/rfcomm0 like a regular serial port.
//
// This means:
//
// You don’t need to bind the device manually to /dev/rfcommX beforehand.
//
// Your code connects directly to the Bluetooth address of the OBD adapter using RFCOMM protocol (like Bluetooth serial).
//
// Requirements:
//
// Your V-LINK OBD adapter is discoverable or already paired.
//
// You know its Bluetooth MAC address (e.g., 00:1D:A5:68:98:8B).
//
// Linux with libbluetooth-dev installed (Debian/Ubuntu: sudo apt install libbluetooth-dev).
//
// Compile and Run
// ===============
// gcc obd_rfcomm.c -o obd_rfcomm -lbluetooth
// ./obd_rfcomm
//
// Example Output
// ==============
// Response: V-LINK 1.5 ELM327 compatible
//
// Notes
// =====
//
// You must pair the device first using bluetoothctl or GUI tools.
//
// If you're unsure about the RFCOMM channel, use sdptool:
//
// sdptool browse 00:1D:A5:68:98:8B
//
// If the connection fails, double-check:
//
// MAC address format (should be XX:XX:XX:XX:XX:XX)
//
// Channel number (try 1–3)
//
// Device is powered and within range
//
// Device is paired (try bluetoothctl > pair + trust)
//
//
// [251018]
// Tests result: OK 
//
//
// Notes:
// Use this file for next steps.
//


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

#include <sys/socket.h>
#include <bluetooth/bluetooth.h>
#include <bluetooth/rfcomm.h>

#define BT_ADDR "10:21:3E:4A:0C:8F"  // Replace with your V-LINK MAC address
#define RFCOMM_CHANNEL 1             // V-LINK typically uses channel 1
#define CMD "AT I\r"                 // AT command with carriage return

int main() {
    struct sockaddr_rc addr = { 0 };
    int sock = 0;
    int status = 0;
    char buf[1024] = { 0 };

    // Allocate socket
    sock = socket(AF_BLUETOOTH, SOCK_STREAM, BTPROTO_RFCOMM);
    if (sock < 0) {
        perror("Error: socket not allocated");
        return 1;
    }

    // Set the connection parameters (BT address and channel)
    addr.rc_family = AF_BLUETOOTH;
    addr.rc_channel = RFCOMM_CHANNEL;
    str2ba(BT_ADDR, &addr.rc_bdaddr);

    // Connect to server (V-LINK)
    status = connect(sock, (struct sockaddr *)&addr, sizeof(addr));
    if (status < 0) {
        perror("Error: connect failed");
        close(sock);
        return 1;
    } else {
        printf("OK: connected \n");
    }

    // Send AT command
    status = write(sock, CMD, strlen(CMD));
    if (status < 0) {
        perror("Error: write failed");
        close(sock);
        return 1;
    } else {
        printf("Sent bytes = %d \n", status);    
    }

    // Read response
    status = 0;
    usleep(500000);  // wait 500ms, any delay is necessary, check how much
    status = read(sock, buf, sizeof(buf));
    if (status < 0) {
        perror("Error: read failed");
        close(sock);
        return 1;
    }

    printf("Received bytes = %d \n", status);
    printf("Response: %s\n", buf);
    

    close(sock);
    return 0;
}











