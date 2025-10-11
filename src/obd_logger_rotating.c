/*
 * obd_logger_rotating.c
 *
 *  Created on: 11 paü 2025
 *      Author: arek1
 */

//
// ChatGPT:
//
//
// Generated file nr 10
//
//
// Prompt:
// Please add rotation/retention for logs, and in second example please add USB storage logging.
//
// Perfect ó letís extend your embedded OBD-II logging system into a self-managing, long-term logger,
// with two separate production-grade examples:
//
// Log rotation and retention (auto-clean old logs)
//
// Logging directly to USB storage (auto-detect & mount safe)
//
// Both build on your previous obd_logger_dtc foundation.
//
// Example 1: OBD-II Logger with Log Rotation and Retention
// ========================================================
//
// Features
//
// Keeps N days of logs (default: 7 days)
//
// Automatically removes older log files from the log directory
//
// Keeps OBD and DTC logs separate
//
// Runs continuously as before
//
//
// Compile & Run
// =============
//
// gcc obd_logger_rotating.c -o obd_logger_rotating -lbluetooth
// ./obd_logger_rotating
//
// This will:
//
// Create /home/pi/obd_logs
//
// Auto-remove logs older than 7 days
//
// Rotate each run automatically
//


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <dirent.h>
#include <signal.h>
#include <errno.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <bluetooth/bluetooth.h>
#include <bluetooth/rfcomm.h>

#define BT_ADDR "00:1D:A5:68:98:8B"
#define RFCOMM_CHANNEL 1
#define LOG_DIR "/home/pi/obd_logs"
#define RETENTION_DAYS 7

volatile sig_atomic_t keep_running = 1;

void int_handler(int dummy) { keep_running = 0; }

void ensure_directory(const char* path) {
    struct stat st = {0};
    if (stat(path, &st) == -1)
        mkdir(path, 0755);
}

void cleanup_old_logs(const char* dir, int days) {
    DIR* d = opendir(dir);
    if (!d) return;

    struct dirent* entry;
    time_t now = time(NULL);

    while ((entry = readdir(d)) != NULL) {
        if (entry->d_name[0] == '.') continue;

        char fullpath[512];
        snprintf(fullpath, sizeof(fullpath), "%s/%s", dir, entry->d_name);

        struct stat st;
        if (stat(fullpath, &st) == 0) {
            double age_days = difftime(now, st.st_mtime) / (60*60*24);
            if (age_days > days) {
                remove(fullpath);
                printf("Removed old log: %s\n", fullpath);
            }
        }
    }
    closedir(d);
}

char* generate_filename(const char* prefix, const char* ext) {
    static char filename[512];
    time_t now = time(NULL);
    char ts[64];
    strftime(ts, sizeof(ts), "%Y%m%d_%H%M%S", localtime(&now));
    snprintf(filename, sizeof(filename), "%s/%s_%s.%s", LOG_DIR, prefix, ts, ext);
    return filename;
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
        char first = 'P';
        switch ((data[i] & 0xC0) >> 6) {
            case 1: first = 'C'; break;
            case 2: first = 'B'; break;
            case 3: first = 'U'; break;
        }
        snprintf(dtc, sizeof(dtc), "%c%01X%02X", first, (data[i] & 0x3F) >> 4, ((data[i] & 0x0F) << 4) | (data[i+1] >> 4));
        fprintf(dtc_log, "%s,DTC,%s\n", timestamp, dtc);
    }
}

int main() {
    struct sockaddr_rc addr = {0};
    int sock;
    char response[256];
    unsigned char data[8];
    int len, dtc_timer = 0;

    signal(SIGINT, int_handler);
    ensure_directory(LOG_DIR);
    cleanup_old_logs(LOG_DIR, RETENTION_DAYS);

    char* obd_path = generate_filename("obd_log", "csv");
    char* dtc_path = generate_filename("dtc_log", "csv");
    FILE* log = fopen(obd_path, "w");
    FILE* dtc_log = fopen(dtc_path, "w");

    if (!log || !dtc_log) {
        perror("fopen");
        return 1;
    }

    fprintf(log, "Timestamp,RPM,Speed,Coolant,Intake,Throttle,MAP,Load,FuelPress,Timing,MAF\n");

    sock = socket(AF_BLUETOOTH, SOCK_STREAM, BTPROTO_RFCOMM);
    addr.rc_family = AF_BLUETOOTH;
    addr.rc_channel = RFCOMM_CHANNEL;
    str2ba(BT_ADDR, &addr.rc_bdaddr);

    if (connect(sock, (struct sockaddr *)&addr, sizeof(addr)) < 0) {
        perror("connect");
        return 1;
    }

    send_obd_command(sock, "AT Z", response, sizeof(response));
    send_obd_command(sock, "AT E0", response, sizeof(response));
    send_obd_command(sock, "AT L0", response, sizeof(response));
    send_obd_command(sock, "AT SP 0", response, sizeof(response));

    printf("Logging OBD data (rotating every %d days)... Press Ctrl+C to stop.\n", RETENTION_DAYS);

    while (keep_running) {
        time_t now = time(NULL);
        char ts[64];
        strftime(ts, sizeof(ts), "%Y-%m-%d %H:%M:%S", localtime(&now));

        int rpm=-1, spd=-1, cool=-1, intake=-1, thr=-1, map=-1, load=-1, fuel=-1, timing=-1;
        float maf=-1.0;

        // Collect key PIDs
        send_obd_command(sock, "010C", response, sizeof(response)); if (parse_response(response, "41 0C", &len, data)==0&&len>=2) rpm=((data[0]<<8)+data[1])/4;
        send_obd_command(sock, "010D", response, sizeof(response)); if (parse_response(response, "41 0D", &len, data)==0) spd=data[0];
        send_obd_command(sock, "0105", response, sizeof(response)); if (parse_response(response, "41 05", &len, data)==0) cool=data[0]-40;
        send_obd_command(sock, "010F", response, sizeof(response)); if (parse_response(response, "41 0F", &len, data)==0) intake=data[0]-40;
        send_obd_command(sock, "0111", response, sizeof(response)); if (parse_response(response, "41 11", &len, data)==0) thr=(int)(data[0]*100.0/255.0);
        send_obd_command(sock, "010B", response, sizeof(response)); if (parse_response(response, "41 0B", &len, data)==0) map=data[0];
        send_obd_command(sock, "0104", response, sizeof(response)); if (parse_response(response, "41 04", &len, data)==0) load=(int)(data[0]*100.0/255.0);
        send_obd_command(sock, "010A", response, sizeof(response)); if (parse_response(response, "41 0A", &len, data)==0) fuel=data[0]*3;
        send_obd_command(sock, "010E", response, sizeof(response)); if (parse_response(response, "41 0E", &len, data)==0) timing=data[0]/2-64;
        send_obd_command(sock, "0110", response, sizeof(response)); if (parse_response(response, "41 10", &len, data)==0&&len>=2) maf=((data[0]<<8)+data[1])/100.0;

        fprintf(log, "%s,%d,%d,%d,%d,%d,%d,%d,%d,%d,%.2f\n", ts, rpm, spd, cool, intake, thr, map, load, fuel, timing, maf);
        fflush(log);

        if (++dtc_timer >= 60) {
            dtc_timer = 0;
            send_obd_command(sock, "03", response, sizeof(response));
            if (parse_response(response, "43", &len, data) == 0 && len > 1) {
                decode_dtc(data, len, dtc_log, ts);
                fflush(dtc_log);
            }
        }

        sleep(1);
    }

    fclose(log); fclose(dtc_log); close(sock);
    printf("Logger stopped.\n");
    return 0;
}


