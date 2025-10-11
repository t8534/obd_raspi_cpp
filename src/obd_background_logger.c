/*
 * obd_background_logger.c
 *
 *  Created on: 11 paü 2025
 *      Author: arek1
 */

//
// ChatGPT:
//
// Generated file nr 8
//
//
//
// Prompt:
// Please extend it with all possible PIDs and make it run continuously as a background logger.
//
// Features:
// =========
//
// Connects to your V-LINK Bluetooth OBD-II adapter.
//
// Initializes the interface.
//
// Continuously reads and logs a wide set of OBD-II sensor PIDs.
//
// Appends results to a timestamped CSV file.
//
// Runs indefinitely (until killed with Ctrl+C or via signal).
//
// Logs cleanly every second.
//
//
// Included PIDs (Mode 01: Live data):
//
// PID    Description                Formula
// 010C   Engine RPM                 ((A*256)+B)/4
// 010D   Vehicle Speed               A
// 0105   Coolant Temperature         A - 40
// 010F   Intake Air Temperature      A - 40
// 0111   Throttle Position           A * 100 / 255
// 010B   Intake Manifold Pressure    A (kPa)
// 0104   Engine Load                 A * 100 / 255
// 010A   Fuel Pressure               A * 3 (kPa)
// 010E   Timing Advance              (A / 2) - 64
// 0110   MAF Air Flow Rate           ((A*256)+B)/100 (g/s)
//
// Compile & Run
// =============
//
// gcc obd_background_logger.c -o obd_background_logger -lbluetooth
// ./obd_background_logger
//
// This will log live data every second into a file like: obd_log_20251011_153320.csv
//
// CSV Sample Header
//
// Timestamp,RPM,Speed(km/h),Coolant(C),Intake(C),Throttle(%),MAP(kPa),Load(%),FuelPressure(kPa),TimingAdvance(deg),MAF(g/s)
// 2025-10-11 15:33:21,801,0,85,40,11,32,45,270,6,2.50


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <signal.h>
#include <errno.h>

#include <sys/socket.h>
#include <bluetooth/bluetooth.h>
#include <bluetooth/rfcomm.h>

#define BT_ADDR "00:1D:A5:68:98:8B"
#define RFCOMM_CHANNEL 1

volatile sig_atomic_t keep_running = 1;

void int_handler(int dummy) {
    keep_running = 0;
}

void send_obd_command(int sock, const char* cmd, char* response, int maxlen) {
    char full_cmd[64];
    snprintf(full_cmd, sizeof(full_cmd), "%s\r", cmd);
    write(sock, full_cmd, strlen(full_cmd));
    usleep(300000);
    memset(response, 0, maxlen);
    read(sock, response, maxlen);
}

int parse_response(const char* response, const char* expected_pid, int* bytes, unsigned char* out) {
    const char* p = strstr(response, expected_pid);
    if (!p) return -1;
    int hex_vals[8];
    int n = sscanf(p + strlen(expected_pid), "%x %x %x %x %x %x %x %x",
                   &hex_vals[0], &hex_vals[1], &hex_vals[2], &hex_vals[3],
                   &hex_vals[4], &hex_vals[5], &hex_vals[6], &hex_vals[7]);
    *bytes = n;
    for (int i = 0; i < n; ++i) out[i] = (unsigned char)hex_vals[i];
    return 0;
}

char* generate_filename() {
    static char filename[64];
    time_t now = time(NULL);
    strftime(filename, sizeof(filename), "obd_log_%Y%m%d_%H%M%S.csv", localtime(&now));
    return filename;
}

int main() {
    struct sockaddr_rc addr = { 0 };
    int sock;
    char response[256];
    unsigned char data[8];
    int len;

    signal(SIGINT, int_handler);

    FILE* log = fopen(generate_filename(), "w");
    if (!log) {
        perror("fopen");
        return 1;
    }

    fprintf(log,
        "Timestamp,RPM,Speed(km/h),Coolant(C),Intake(C),Throttle(%%),MAP(kPa),Load(%%),FuelPressure(kPa),TimingAdvance(deg),MAF(g/s)\n");

    sock = socket(AF_BLUETOOTH, SOCK_STREAM, BTPROTO_RFCOMM);
    addr.rc_family = AF_BLUETOOTH;
    addr.rc_channel = RFCOMM_CHANNEL;
    str2ba(BT_ADDR, &addr.rc_bdaddr);

    if (connect(sock, (struct sockaddr *)&addr, sizeof(addr)) < 0) {
        perror("connect");
        fclose(log);
        return 1;
    }

    // Init
    send_obd_command(sock, "AT Z", response, sizeof(response));
    send_obd_command(sock, "AT E0", response, sizeof(response));
    send_obd_command(sock, "AT L0", response, sizeof(response));
    send_obd_command(sock, "AT SP 0", response, sizeof(response));

    printf("Running background OBD logger... Press Ctrl+C to stop.\n");

    while (keep_running) {
        time_t now = time(NULL);
        char ts[64];
        strftime(ts, sizeof(ts), "%Y-%m-%d %H:%M:%S", localtime(&now));

        int rpm = -1, speed = -1, coolant = -1, intake = -1, throttle = -1;
        int map = -1, load = -1, fuel = -1, timing = -1;
        float maf = -1.0f;

        // RPM
        send_obd_command(sock, "010C", response, sizeof(response));
        if (parse_response(response, "41 0C", &len, data) == 0 && len >= 2)
            rpm = ((data[0] << 8) + data[1]) / 4;

        // Speed
        send_obd_command(sock, "010D", response, sizeof(response));
        if (parse_response(response, "41 0D", &len, data) == 0)
            speed = data[0];

        // Coolant Temp
        send_obd_command(sock, "0105", response, sizeof(response));
        if (parse_response(response, "41 05", &len, data) == 0)
            coolant = data[0] - 40;

        // Intake Temp
        send_obd_command(sock, "010F", response, sizeof(response));
        if (parse_response(response, "41 0F", &len, data) == 0)
            intake = data[0] - 40;

        // Throttle
        send_obd_command(sock, "0111", response, sizeof(response));
        if (parse_response(response, "41 11", &len, data) == 0)
            throttle = (int)((data[0] * 100.0) / 255.0);

        // MAP
        send_obd_command(sock, "010B", response, sizeof(response));
        if (parse_response(response, "41 0B", &len, data) == 0)
            map = data[0];

        // Engine Load
        send_obd_command(sock, "0104", response, sizeof(response));
        if (parse_response(response, "41 04", &len, data) == 0)
            load = (int)((data[0] * 100.0) / 255.0);

        // Fuel Pressure
        send_obd_command(sock, "010A", response, sizeof(response));
        if (parse_response(response, "41 0A", &len, data) == 0)
            fuel = data[0] * 3;

        // Timing Advance
        send_obd_command(sock, "010E", response, sizeof(response));
        if (parse_response(response, "41 0E", &len, data) == 0)
            timing = ((int)data[0] / 2) - 64;

        // MAF
        send_obd_command(sock, "0110", response, sizeof(response));
        if (parse_response(response, "41 10", &len, data) == 0 && len >= 2)
            maf = ((data[0] << 8) + data[1]) / 100.0f;

        // Log to file
        fprintf(log, "%s,%d,%d,%d,%d,%d,%d,%d,%d,%d,%.2f\n",
                ts, rpm, speed, coolant, intake, throttle, map, load, fuel, timing, maf);
        fflush(log);

        // Print to console
        printf("%s | RPM: %d | SPD: %d | Cool: %d∞C | Thr: %d%% | MAP: %d | Load: %d%% | FP: %d | Adv: %d | MAF: %.2f\n",
               ts, rpm, speed, coolant, throttle, map, load, fuel, timing, maf);

        sleep(1);
    }

    printf("\nStopping logger.\n");
    fclose(log);
    close(sock);
    return 0;
}












