/*
 * obd_logger_merged.c
 *
 *  Created on: 11 paü 2025
 *      Author: arek1
 */

//
// ChatGPT:
//
// Generated file nr 12
//
//
// Prompt:
// Please add rotation/retention for logs, and in second example please add USB storage logging.
//
// Merged obd_logger_rotating.c and obd_logger_usb.c
//
// Features
// ========
//
// USB logging: uses USB if mounted at /media/pi/OBD_USB, otherwise defaults to /home/pi/obd_logs
//
// Log rotation: deletes log files older than 7 days automatically
//
// OBD-II live sensor logging (RPM, speed, coolant temp, MAF, etc.)
//
// DTC scan every 60 seconds
//
// Runs continuously as a background logger
//
// Organized log files:
//
//    Sensor data: obd_log_YYYYMMDD_HHMMSS.csv
//
//    DTCs: dtc_log_YYYYMMDD_HHMMSS.csv
//
// Compile & Run
// =============
//
// gcc obd_logger_merged.c -o obd_logger_merged -lbluetooth
// ./obd_logger_merged
//
// Summary:
// ========
// Feature	Description:
//
// USB support    Logs to USB at /media/pi/OBD_USB if present
// Rotation       Automatically removes log files older than 7 days
// DTCs           Scans and logs DTCs every 60 seconds
// Directory      Stores logs in timestamped CSV files
// Background     Suitable for systemd service setup
//
//
// Would you like a ready-made .service file for this merged version to install as a boot-time daemon?
// Here's a complete Systemd service file to run the merged OBD-II logger at boot as a background
// daemon on your Raspberry Pi (or other Linux device).
//
// 1. Move the compiled logger
//
// First, ensure your merged logger is compiled and stored in a permanent location:
//
// sudo cp obd_logger_merged /usr/local/bin/obd_logger_merged
// sudo chmod +x /usr/local/bin/obd_logger_merged
//
// 2. Create the systemd service file
//
// Create a new file:
//
// sudo nano /etc/systemd/system/obdlogger.service
//
// Paste the following:
//
// [Unit]
// Description=OBD-II Data Logger with USB and Log Rotation
// After=network.target bluetooth.target
// Requires=bluetooth.target
//
// [Service]
// ExecStart=/usr/local/bin/obd_logger_merged
// WorkingDirectory=/home/pi
// User=pi
// Restart=always
// RestartSec=5
// StandardOutput=journal
// StandardError=journal
//
// [Install]
// WantedBy=multi-user.target
//
// 3. Enable and start the service
//
// Run these commands:
//
// sudo systemctl daemon-reload
// sudo systemctl enable obdlogger.service
// sudo systemctl start obdlogger.service
//
// 4. Monitor the service
//
// To check that itís running and logging:
//
// sudo systemctl status obdlogger.service
//
// To follow live logs:
//
// journalctl -u obdlogger.service -f
//
// 5. To stop or disable
//
// sudo systemctl stop obdlogger.service
// sudo systemctl disable obdlogger.service
//
// Tips
//
// If you want to test the service logs without rebooting, you can:
//
// You can always log to a USB flash drive by inserting one and naming the mount point /media/pi/OBD_USB.
//


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <dirent.h>
#include <signal.h>
#include <errno.h>
#include <sys/stat.h>
#include <sys/socket.h>
#include <bluetooth/bluetooth.h>
#include <bluetooth/rfcomm.h>

#define BT_ADDR "00:1D:A5:68:98:8B"
#define RFCOMM_CHANNEL 1
#define DEFAULT_DIR "/home/pi/obd_logs"
#define USB_DIR "/media/pi/OBD_USB"
#define RETENTION_DAYS 7

volatile sig_atomic_t keep_running = 1;

void int_handler(int dummy) {
    keep_running = 0;
}

int usb_available() {
    struct stat st;
    return (stat(USB_DIR, &st) == 0 && S_ISDIR(st.st_mode));
}

const char* get_log_dir() {
    if (usb_available()) {
        printf("USB storage found at %s\n", USB_DIR);
        return USB_DIR;
    } else {
        printf("USB not found, using fallback: %s\n", DEFAULT_DIR);
        mkdir(DEFAULT_DIR, 0755);
        return DEFAULT_DIR;
    }
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
            double age_days = difftime(now, st.st_mtime) / (60 * 60 * 24);
            if (age_days > days) {
                remove(fullpath);
                printf("Removed old log: %s\n", fullpath);
            }
        }
    }
    closedir(d);
}

char* make_log_path(const char* dir, const char* prefix, const char* ext) {
    static char path[512];
    time_t now = time(NULL);
    char ts[64];
    strftime(ts, sizeof(ts), "%Y%m%d_%H%M%S", localtime(&now));
    snprintf(path, sizeof(path), "%s/%s_%s.%s", dir, prefix, ts, ext);
    return path;
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
        snprintf(dtc, sizeof(dtc), "%c%01X%02X", first, (data[i] & 0x3F) >> 4,
                 ((data[i] & 0x0F) << 4) | (data[i+1] >> 4));
        fprintf(dtc_log, "%s,DTC,%s\n", timestamp, dtc);
    }
}

int main() {
    signal(SIGINT, int_handler);

    const char* log_dir = get_log_dir();
    cleanup_old_logs(log_dir, RETENTION_DAYS);

    struct sockaddr_rc addr = { 0 };
    int sock, dtc_timer = 0;
    char response[256];
    unsigned char data[8];
    int len;

    char* obd_path = make_log_path(log_dir, "obd_log", "csv");
    char* dtc_path = make_log_path(log_dir, "dtc_log", "csv");

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
        fclose(log); fclose(dtc_log);
        return 1;
    }

    send_obd_command(sock, "AT Z", response, sizeof(response));
    send_obd_command(sock, "AT E0", response, sizeof(response));
    send_obd_command(sock, "AT L0", response, sizeof(response));
    send_obd_command(sock, "AT SP 0", response, sizeof(response));

    printf("Logging OBD-II data. Press Ctrl+C to stop.\n");

    while (keep_running) {
        time_t now = time(NULL);
        char ts[64];
        strftime(ts, sizeof(ts), "%Y-%m-%d %H:%M:%S", localtime(&now));

        int rpm = -1, spd = -1, cool = -1, intake = -1, thr = -1;
        int map = -1, load = -1, fuel = -1, timing = -1;
        float maf = -1.0f;

        send_obd_command(sock, "010C", response, sizeof(response)); if (parse_response(response, "41 0C", &len, data)==0&&len>=2) rpm=((data[0]<<8)+data[1])/4;
        send_obd_command(sock, "010D", response, sizeof(response)); if (parse_response(response, "41 0D", &len, data)==0) spd=data[0];
        send_obd_command(sock, "0105", response, sizeof(response)); if (parse_response(response, "41 05", &len, data)==0) cool=data[0]-40;
        send_obd_command(sock, "010F", response, sizeof(response)); if (parse_response(response, "41 0F", &len, data)==0) intake=data[0]-40;
        send_obd_command(sock, "0111", response, sizeof(response)); if (parse_response(response, "41 11", &len, data)==0) thr=(int)(data[0]*100.0/255.0);
        send_obd_command(sock, "010B", response, sizeof(response)); if (parse_response(response, "41 0B", &len, data)==0) map=data[0];
        send_obd_command(sock, "0104", response, sizeof(response)); if (parse_response(response, "41 04", &len, data)==0) load=(int)(data[0]*100.0/255.0);
        send_obd_command(sock, "010A", response, sizeof(response)); if (parse_response(response, "41 0A", &len, data)==0) fuel=data[0]*3;
        send_obd_command(sock, "010E", response, sizeof(response)); if (parse_response(response, "41 0E", &len, data)==0) timing=(int)(data[0]/2)-64;
        send_obd_command(sock, "0110", response, sizeof(response)); if (parse_response(response, "41 10", &len, data)==0&&len>=2) maf=((data[0]<<8)+data[1])/100.0f;

        fprintf(log, "%s,%d,%d,%d,%d,%d,%d,%d,%d,%d,%.2f\n", ts, rpm, spd, cool, intake, thr, map, load, fuel, timing, maf);
        fflush(log);

        if (++dtc_timer >= 60) {
            dtc_timer = 0;
            send_obd_command(sock, "03", response, sizeof(response));
            if (parse_response(response, "43", &len, data)==0 && len > 1) {
                decode_dtc(data, len, dtc_log, ts);
                fflush(dtc_log);
            }
        }

        sleep(1);
    }

    fclose(log);
    fclose(dtc_log);
    close(sock);
    printf("Logger stopped.\n");
    return 0;
}

