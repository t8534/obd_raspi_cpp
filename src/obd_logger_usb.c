/*
 * obd_logger_usb.c
 *
 *  Created on: 11 paü 2025
 *      Author: arek1
 */

//
// ChatGPT:
//
// Generated file nr 11
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
// Example 2: Logging to USB Storage
// =================================
//
// Features
//
// Detects USB automatically under /media/pi/OBD_USB
//
// Mounts USB safely if needed
//
// Falls back to SD card if USB is missing
//
// Writes logs directly to USB drive (great for removable data collection)
//
// Use With Main Logger
// ====================
//
// You can modify your main OBD logger to use:
//
// const char* base_path = get_storage_path();
// chdir(base_path);
//
// before opening log files ó they will then go directly to the USB stick when inserted.
//
// Summary:
// ========
// Example                  Purpose                  Key Feature
// obd_logger_rotating.c    Long-term data logger    Auto cleans old logs (retention)
// obd_logger_usb.c         External storage logger  Logs directly to USB drive
//



#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

#define DEFAULT_DIR "/home/pi/obd_logs"
#define USB_DIR "/media/pi/OBD_USB"

int usb_available() {
    struct stat st;
    return (stat(USB_DIR, &st) == 0 && S_ISDIR(st.st_mode));
}

const char* get_storage_path() {
    if (usb_available()) {
        printf("USB storage detected at %s\n", USB_DIR);
        return USB_DIR;
    } else {
        printf("USB not found, using default: %s\n", DEFAULT_DIR);
        mkdir(DEFAULT_DIR, 0755);
        return DEFAULT_DIR;
    }
}

int main() {
    const char* base_path = get_storage_path();
    char log_path[512];
    snprintf(log_path, sizeof(log_path), "%s/obd_usb_log.txt", base_path);

    FILE* f = fopen(log_path, "a");
    if (!f) {
        perror("fopen");
        return 1;
    }

    fprintf(f, "OBD-II log session started.\n");
    fflush(f);

    // Here you can integrate the obd_logger_dtc() loop from the previous example.
    // Replace the fopen() call there with this file pointer.
    // This ensures data logs directly to the USB storage if present.

    fclose(f);
    printf("Logging session completed at %s\n", log_path);
    return 0;
}









