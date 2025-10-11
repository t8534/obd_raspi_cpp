/*
 * obd_dtc_decoder.c
 *
 *  Created on: 11 paü 2025
 *      Author: arek1
 */

//
// ChatGPT:
//
// Generated file nr 5
//
//
//
// Prompt:
// Please generate example with dynamic DTC decoding
//
// Dynamic DTC Decoding
//
// This version connects to the OBD-II adapter, sends mode 03 to read stored Diagnostic Trouble Codes,
// and decodes them according to SAE J2012 / ISO 15031-6.
//
// Build and Run
// =============
//
// gcc obd_dtc_decoder.c -o obd_dtc_decoder -lbluetooth
// ./obd_dtc_decoder
//
// Example Output
// ==============
//
// Raw DTC response: 43 01 33 02 10 00 00
// DTCs:
//  P0133
//  P0210
//


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>

#include <sys/socket.h>
#include <bluetooth/bluetooth.h>
#include <bluetooth/rfcomm.h>

#define BT_ADDR "00:1D:A5:68:98:8B"  // Replace with your adapter MAC
#define RFCOMM_CHANNEL 1

void decode_dtc(const unsigned char* data, int len) {
    int i = 0;
    if (len < 3 || data[0] != 0x43) {
        printf("Unexpected response or no DTCs.\n");
        return;
    }

    printf("DTCs:\n");

    for (i = 1; i+1 < len && data[i] != 0x00 && data[i+1] != 0x00; i += 2) {
        unsigned char A = data[i];
        unsigned char B = data[i+1];

        char dtc[6];
        char first_char;

        switch ((A & 0xC0) >> 6) {
            case 0: first_char = 'P'; break;
            case 1: first_char = 'C'; break;
            case 2: first_char = 'B'; break;
            case 3: first_char = 'U'; break;
        }

        snprintf(dtc, sizeof(dtc), "%c%01X%02X", first_char, (A & 0x3F) >> 4, ((A & 0x0F) << 4) | (B >> 4));
        printf("  %s\n", dtc);
    }

    if (i == 1) {
        printf("  No DTCs found.\n");
    }
}

int main() {
    struct sockaddr_rc addr = { 0 };
    int sock, status;
    char buf[1024] = { 0 };
    unsigned char response[1024] = { 0 };

    sock = socket(AF_BLUETOOTH, SOCK_STREAM, BTPROTO_RFCOMM);
    addr.rc_family = AF_BLUETOOTH;
    addr.rc_channel = RFCOMM_CHANNEL;
    str2ba(BT_ADDR, &addr.rc_bdaddr);

    if (connect(sock, (struct sockaddr *)&addr, sizeof(addr)) < 0) {
        perror("connect");
        return 1;
    }

    write(sock, "AT E0\r", 6); usleep(300000);
    read(sock, buf, sizeof(buf));
    write(sock, "03\r", 3); // Request DTCs
    usleep(500000);

    int len = read(sock, response, sizeof(response));
    if (len > 0) {
        printf("Raw DTC response: ");
        for (int i = 0; i < len; i++) printf("%02X ", response[i]);
        printf("\n");

        decode_dtc(response, len);
    } else {
        printf("No data received.\n");
    }

    close(sock);
    return 0;
}





