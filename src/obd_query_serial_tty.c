/*
 * obd_query_serial_tty.c
 *
 *  Created on: 11 paü 2025
 *      Author: arek1
 */

// ChatGPT:
//
// Generated file nr 1
//
//
// Here's a C language code example that opens your Bluetooth serial port (e.g. /dev/rfcomm0 or similar),
// sends the "AT I" command to your V-LINK OBD adapter, and prints the response.
//
// Assumptions:
//
// Your V-LINK is already paired and bound to a serial port like /dev/rfcomm0.
//
// Youíve tested with minicom and verified that typing AT I returns expected info (like device model).
//
// Your Raspberry Pi is running Linux.
//
// You have basic build tools installed (gcc, etc).
//
//
// Compile and Run
// ===============
//
// gcc obd_query.c -o obd_query
// ./obd_query
//
// You should see output like:
//
// Response: V-LINK XYZ Model 1.2
//
// Troubleshooting
// ===============
//
// If you get no response:
//
// Check the baud rate (some adapters use 38400 or 115200).
//
// Try increasing VTIME to 20 (2 seconds timeout).
//
// Make sure you're sending \r (carriage return) and not newline \n.
//
// Double-check your port name with ls /dev/rfcomm*.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <termios.h>
#include <errno.h>

#define SERIAL_PORT "/dev/rfcomm0"  // Change if your device uses another port
#define CMD "AT I\r"                // AT command with carriage return

int configure_serial_port(int fd) {
    struct termios tty;

    if (tcgetattr(fd, &tty) != 0) {
        perror("tcgetattr");
        return -1;
    }

    cfsetospeed(&tty, B9600);  // V-LINK typically uses 9600 or 38400 baud
    cfsetispeed(&tty, B9600);

    tty.c_cflag = (tty.c_cflag & ~CSIZE) | CS8;  // 8-bit chars
    tty.c_iflag &= ~IGNBRK;         // disable break processing
    tty.c_lflag = 0;                // no signaling chars, no echo, no canonical processing
    tty.c_oflag = 0;                // no remapping, no delays
    tty.c_cc[VMIN]  = 0;            // read doesn't block
    tty.c_cc[VTIME] = 10;           // 1 second read timeout

    tty.c_iflag &= ~(IXON | IXOFF | IXANY); // shut off xon/xoff ctrl

    tty.c_cflag |= (CLOCAL | CREAD);    // ignore modem controls, enable reading
    tty.c_cflag &= ~(PARENB | PARODD);  // shut off parity
    tty.c_cflag &= ~CSTOPB;
    tty.c_cflag &= ~CRTSCTS;

    if (tcsetattr(fd, TCSANOW, &tty) != 0) {
        perror("tcsetattr");
        return -1;
    }

    return 0;
}

int main() {
    int serial_fd = open(SERIAL_PORT, O_RDWR | O_NOCTTY | O_SYNC);
    if (serial_fd < 0) {
        perror("open");
        return 1;
    }

    if (configure_serial_port(serial_fd) != 0) {
        close(serial_fd);
        return 1;
    }

    // Write command
    int n_written = write(serial_fd, CMD, strlen(CMD));
    if (n_written < 0) {
        perror("write");
        close(serial_fd);
        return 1;
    }

    // Read response
    char buf[256];
    memset(buf, 0, sizeof(buf));
    int n_read = read(serial_fd, buf, sizeof(buf) - 1);
    if (n_read < 0) {
        perror("read");
        close(serial_fd);
        return 1;
    }

    printf("Response: %s\n", buf);

    close(serial_fd);
    return 0;
}


