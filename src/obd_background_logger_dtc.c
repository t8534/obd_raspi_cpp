/*
 * obd_background_logger_dtc.c
 *
 *  Created on: 11 paü 2025
 *      Author: arek1
 */
//
// ChatGPT:
//
// Generated file nr 9
//
//
// Prompt: Please add DTC scan every 60 seconds, in separate example please turn this into a service on boot.
//
// Part 1: DTC Scan Every 60 Seconds
// =================================
// This extends the previous live logger (obd_background_logger.c) with:
//
// DTC scan using mode 03 every 60 seconds
//
// Dynamic DTC decoding (SAE J2012 format)
//
// Appends decoded DTCs to a separate file
//
// Compile & Run:
// ==============
//
// gcc obd_background_logger_dtc.c -o obd_logger_dtc -lbluetooth
// ./obd_logger_dtc
//
// Output:
// =======
//
// obd_log_*.csv: sensor data
//
// dtc_log_*.csv: decoded DTCs like:
//
// 2025-10-11 15:35:00,DTC,P0133
// 2025-10-11 15:36:00,DTC,P0455
//
// Part 2: Running as a Service on Boot (Systemd)
// ==============================================
//
// To run your logger on boot:
//
// 1. Create Executable
//
// Ensure logger is compiled and stored, e.g.:
//
// sudo cp obd_logger_dtc /usr/local/bin/
// sudo chmod +x /usr/local/bin/obd_logger_dtc
//
// 2. Create Systemd Unit File
//
// sudo nano /etc/systemd/system/obdlogger.service
//
// Paste:
//
// [Unit]
// Description=OBD-II Background Logger
// After=network.target bluetooth.target
//
// [Service]
// ExecStart=/usr/local/bin/obd_logger_dtc
// Restart=always
// User=pi
// WorkingDirectory=/home/pi
// StandardOutput=journal
// StandardError=journal
//
// [Install]
// WantedBy=multi-user.target
//
// 3. Enable and Start Service
//
// sudo systemctl daemon-reexec
// sudo systemctl daemon-reload
// sudo systemctl enable obdlogger.service
// sudo systemctl start obdlogger.service
//
// Check logs
//
// journalctl -u obdlogger.service -f
//
// To Stop or Disable
//
// sudo systemctl stop obdlogger.service
// sudo systemctl disable obdlogger.service
//


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

void decode_dtc(const unsigned char* data, int len, FILE* dtc_log, const char* timestamp) {
    if (len < 3 || data[0] != 0x43) return;

    for (int i = 1; i + 1 < len && (data[i] != 0x00 || data[i+1] != 0x00); i += 2) {
        char dtc[6];
        char first;

        switch ((data[i] & 0xC0) >> 6) {
            case 0: first = 'P'; break;
            case 1: first = 'C'; break;
            case 2: first = 'B'; break;
            case 3: first = 'U'; break;
        }

        snprintf(dtc, sizeof(dtc), "%c%01X%02X", first, (data[i] & 0x3F) >> 4, ((data[i] & 0x0F) << 4) | (data[i+1] >> 4));
        fprintf(dtc_log, "%s,DTC,%s\n", timestamp, dtc);
    }
}

char* generate_filename(const char* prefix) {
    static char filename[64];
    time_t now = time(NULL);
    strftime(filename, sizeof(filename), prefix, localtime(&now));
    return filename;
}

int main() {
    struct sockaddr_rc addr = { 0 };
    int sock;
    char response[256];
    unsigned char data[8];
    int len;
    int dtc_counter = 0;

    signal(SIGINT, int_handler);

    FILE* log = fopen(generate_filename("obd_log_%Y%m%d_%H%M%S.csv"), "w");
    FILE* dtc_log = fopen(generate_filename("dtc_log_%Y%m%d_%H%M%S.csv"), "w");
    if (!log || !dtc_log) {
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
        fclose(log); fclose(dtc_log);
        return 1;
    }

    // Init
    send_obd_command(sock, "AT Z", response, sizeof(response));
    send_obd_command(sock, "AT E0", response, sizeof(response));
    send_obd_command(sock, "AT L0", response, sizeof(response));
    send_obd_command(sock, "AT SP 0", response, sizeof(response));

    printf("Logging live data + DTC every 60s. Press Ctrl+C to stop.\n");

    while (keep_running) {
        time_t now = time(NULL);
        char ts[64];
        strftime(ts, sizeof(ts), "%Y-%m-%d %H:%M:%S", localtime(&now));

        int rpm = -1, speed = -1, coolant = -1, intake = -1, throttle = -1;
        int map = -1, load = -1, fuel = -1, timing = -1;
        float maf = -1.0f;

        // Live data
        send_obd_command(sock, "010C", response, sizeof(response)); if (parse_response(response, "41 0C", &len, data) == 0 && len >= 2) rpm = ((data[0]<<8)+data[1])/4;
        send_obd_command(sock, "010D", response, sizeof(response)); if (parse_response(response, "41 0D", &len, data) == 0) speed = data[0];
        send_obd_command(sock, "0105", response, sizeof(response)); if (parse_response(response, "41 05", &len, data) == 0) coolant = data[0] - 40;
        send_obd_command(sock, "010F", response, sizeof(response)); if (parse_response(response, "41 0F", &len, data) == 0) intake = data[0] - 40;
        send_obd_command(sock, "0111", response, sizeof(response)); if (parse_response(response, "41 11", &len, data) == 0) throttle = (int)((data[0] * 100.0) / 255.0);
        send_obd_command(sock, "010B", response, sizeof(response)); if (parse_response(response, "41 0B", &len, data) == 0) map = data[0];
        send_obd_command(sock, "0104", response, sizeof(response)); if (parse_response(response, "41 04", &len, data) == 0) load = (int)((data[0] * 100.0) / 255.0);
        send_obd_command(sock, "010A", response, sizeof(response)); if (parse_response(response, "41 0A", &len, data) == 0) fuel = data[0] * 3;
        send_obd_command(sock, "010E", response, sizeof(response)); if (parse_response(response, "41 0E", &len, data) == 0) timing = (data[0] / 2) - 64;
        send_obd_command(sock, "0110", response, sizeof(response)); if (parse_response(response, "41 10", &len, data) == 0 && len >= 2) maf = ((data[0] << 8) + data[1]) / 100.0f;

        // Log live data
        fprintf(log, "%s,%d,%d,%d,%d,%d,%d,%d,%d,%d,%.2f\n",
                ts, rpm, speed, coolant, intake, throttle, map, load, fuel, timing, maf);
        fflush(log);

        // DTC scan every 60 seconds
        if (++dtc_counter >= 60) {
            dtc_counter = 0;
            send_obd_command(sock, "03", response, sizeof(response));
            if (parse_response(response, "43", &len, data) == 0 && len > 1) {
                decode_dtc(data, len, dtc_log, ts);
                fflush(dtc_log);
            }
        }

        sleep(1);
    }

    fclose(log);
    fclose(dtc_log);
    close(sock);
    return 0;
}


