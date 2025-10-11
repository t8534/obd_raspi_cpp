/*
 * obd_logger.c
 *
 *  Created on: 11 paü 2025
 *      Author: arek1
 */

//
// ChatGPT:
//
// Generated file nr 6
//
//
// Logging OBD-II Data to File
//
// This version connects, initializes the adapter, and logs RPM and speed every
// second to a file obd_log.csv.
//
//
// Build and Run
// =============
//
// gcc obd_logger.c -o obd_logger -lbluetooth
// ./obd_logger
//
// Sample Output
// =============
//
// Logging RPM and speed to obd_log.csv...
// 2025-10-11 15:30:10 | RPM: 801 | Speed: 0 km/h
// 2025-10-11 15:30:11 | RPM: 813 | Speed: 1 km/h
//
// Sample CSV: obd_log.csv
// =======================
//
// Timestamp,RPM,Speed(km/h)
// 2025-10-11 15:30:10,801,0
// 2025-10-11 15:30:11,813,1
//


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <errno.h>

#include <sys/socket.h>
#include <bluetooth/bluetooth.h>
#include <bluetooth/rfcomm.h>

#define BT_ADDR "00:1D:A5:68:98:8B"
#define RFCOMM_CHANNEL 1
#define LOG_FILE "obd_log.csv"

void send_obd_command(int sock, const char* cmd, char* response, int maxlen) {
    char full_cmd[64];
    snprintf(full_cmd, sizeof(full_cmd), "%s\r", cmd);
    write(sock, full_cmd, strlen(full_cmd));
    usleep(300000);
    memset(response, 0, maxlen);
    read(sock, response, maxlen);
}

int parse_rpm(const char* response) {
    int A, B;
    if (sscanf(response, "41 0C %x %x", &A, &B) == 2) {
        return ((A * 256) + B) / 4;
    }
    return -1;
}

int parse_speed(const char* response) {
    int A;
    if (sscanf(response, "41 0D %x", &A) == 1) {
        return A;
    }
    return -1;
}

int main() {
    struct sockaddr_rc addr = { 0 };
    int sock;
    char response[128];
    FILE* log = fopen(LOG_FILE, "w");

    if (!log) {
        perror("fopen");
        return 1;
    }

    fprintf(log, "Timestamp,RPM,Speed(km/h)\n");

    sock = socket(AF_BLUETOOTH, SOCK_STREAM, BTPROTO_RFCOMM);
    addr.rc_family = AF_BLUETOOTH;
    addr.rc_channel = RFCOMM_CHANNEL;
    str2ba(BT_ADDR, &addr.rc_bdaddr);

    if (connect(sock, (struct sockaddr *)&addr, sizeof(addr)) < 0) {
        perror("connect");
        fclose(log);
        return 1;
    }

    // Init adapter
    send_obd_command(sock, "AT Z", response, sizeof(response));
    send_obd_command(sock, "AT E0", response, sizeof(response));
    send_obd_command(sock, "AT L0", response, sizeof(response));
    send_obd_command(sock, "AT SP 0", response, sizeof(response));

    printf("Logging RPM and speed to %s...\n", LOG_FILE);

    for (int i = 0; i < 30; ++i) {  // Collect data for 30 seconds
        time_t now = time(NULL);
        char timebuf[64];
        strftime(timebuf, sizeof(timebuf), "%Y-%m-%d %H:%M:%S", localtime(&now));

        send_obd_command(sock, "010C", response, sizeof(response));
        int rpm = parse_rpm(response);

        send_obd_command(sock, "010D", response, sizeof(response));
        int speed = parse_speed(response);

        printf("%s | RPM: %d | Speed: %d km/h\n", timebuf, rpm, speed);
        fprintf(log, "%s,%d,%d\n", timebuf, rpm, speed);
        fflush(log);

        sleep(1);
    }

    fclose(log);
    close(sock);
    return 0;
}



