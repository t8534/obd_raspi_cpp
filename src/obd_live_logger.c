/*
 * obd_live_logger.c
 *
 *  Created on: 11 paü 2025
 *      Author: arek1
 */

//
// ChatGPT:
//
// Generated file nr 7
//
//
// Prompt:
// Please generate example to decode all sensors live values and write it to the file.
//
// Here is a complete C code example for your Raspberry Pi with a V-LINK OBD-II Bluetooth adapter, which:
//
// Features:
//
//     Connects via Bluetooth RFCOMM.
//
//     Initializes the OBD-II adapter.
//
//     Requests multiple live sensor PIDs every second:
//
//         Engine RPM (010C)
//
//         Vehicle speed (010D)
//
//         Coolant temperature (0105)
//
//         Throttle position (0111)
//
//         Intake air temperature (010F)
//
//         Mass air flow (0110)
//
//     Parses and decodes raw responses into real sensor values.
//
//     Logs the values to a CSV file (obd_live_log.csv).
//
// Compile & Run
// =============
//
// gcc obd_live_logger.c -o obd_live_logger -lbluetooth
// ./obd_live_logger
//
// CSV Output (obd_live_log.csv)
// =============================
//
// Timestamp,RPM,Speed(km/h),CoolantTemp(C),Throttle(%),IntakeTemp(C),MAF(g/s)
// 2025-10-11 15:30:10,801,0,75,12,43,2.35
// 2025-10-11 15:30:11,850,1,75,13,44,2.50




#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <errno.h>

#include <sys/socket.h>
#include <bluetooth/bluetooth.h>
#include <bluetooth/rfcomm.h>

#define BT_ADDR "00:1D:A5:68:98:8B"  // Replace with your V-LINK MAC
#define RFCOMM_CHANNEL 1
#define LOG_FILE "obd_live_log.csv"

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

int main() {
    struct sockaddr_rc addr = { 0 };
    int sock;
    char response[256];
    FILE* log = fopen(LOG_FILE, "w");

    if (!log) {
        perror("fopen");
        return 1;
    }

    fprintf(log, "Timestamp,RPM,Speed(km/h),CoolantTemp(C),Throttle(%%),IntakeTemp(C),MAF(g/s)\n");

    sock = socket(AF_BLUETOOTH, SOCK_STREAM, BTPROTO_RFCOMM);
    addr.rc_family = AF_BLUETOOTH;
    addr.rc_channel = RFCOMM_CHANNEL;
    str2ba(BT_ADDR, &addr.rc_bdaddr);

    if (connect(sock, (struct sockaddr *)&addr, sizeof(addr)) < 0) {
        perror("connect");
        fclose(log);
        return 1;
    }

    // Init sequence
    send_obd_command(sock, "AT Z", response, sizeof(response));
    send_obd_command(sock, "AT E0", response, sizeof(response));
    send_obd_command(sock, "AT L0", response, sizeof(response));
    send_obd_command(sock, "AT SP 0", response, sizeof(response));

    printf("Logging live OBD-II data to %s...\n", LOG_FILE);

    for (int i = 0; i < 30; ++i) {  // Log for 30 seconds
        time_t now = time(NULL);
        char timebuf[64];
        strftime(timebuf, sizeof(timebuf), "%Y-%m-%d %H:%M:%S", localtime(&now));

        int rpm = -1, speed = -1, coolant = -1, throttle = -1, intake = -1;
        float maf = -1.0f;

        // RPM
        send_obd_command(sock, "010C", response, sizeof(response));
        unsigned char rpm_bytes[2];
        int rpm_len;
        if (parse_response(response, "41 0C", &rpm_len, rpm_bytes) == 0 && rpm_len >= 2)
            rpm = ((rpm_bytes[0] << 8) + rpm_bytes[1]) / 4;

        // Speed
        send_obd_command(sock, "010D", response, sizeof(response));
        unsigned char speed_byte;
        int speed_len;
        if (parse_response(response, "41 0D", &speed_len, &speed_byte) == 0)
            speed = speed_byte;

        // Coolant Temp
        send_obd_command(sock, "0105", response, sizeof(response));
        unsigned char coolant_byte;
        int coolant_len;
        if (parse_response(response, "41 05", &coolant_len, &coolant_byte) == 0)
            coolant = coolant_byte - 40;

        // Throttle
        send_obd_command(sock, "0111", response, sizeof(response));
        unsigned char throttle_byte;
        int throttle_len;
        if (parse_response(response, "41 11", &throttle_len, &throttle_byte) == 0)
            throttle = (int)((throttle_byte * 100.0) / 255.0);

        // Intake Air Temp
        send_obd_command(sock, "010F", response, sizeof(response));
        unsigned char intake_byte;
        int intake_len;
        if (parse_response(response, "41 0F", &intake_len, &intake_byte) == 0)
            intake = intake_byte - 40;

        // MAF
        send_obd_command(sock, "0110", response, sizeof(response));
        unsigned char maf_bytes[2];
        int maf_len;
        if (parse_response(response, "41 10", &maf_len, maf_bytes) == 0 && maf_len >= 2)
            maf = ((maf_bytes[0] << 8) + maf_bytes[1]) / 100.0f;

        printf("%s | RPM: %d | Speed: %d | Coolant: %d∞C | Throttle: %d%% | Intake: %d∞C | MAF: %.2f g/s\n",
               timebuf, rpm, speed, coolant, throttle, intake, maf);

        fprintf(log, "%s,%d,%d,%d,%d,%d,%.2f\n",
                timebuf, rpm, speed, coolant, throttle, intake, maf);
        fflush(log);

        sleep(1);
    }

    fclose(log);
    close(sock);
    return 0;
}











