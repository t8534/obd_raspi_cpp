// Example C Code to Connect via RFCOMM (SPP)
//
//
// gcc -o obd_connect obd_connect.c -lbluetooth
// 
// Make sure your adapter is powered on and paired.
// You can verify pairing with: bluetoothctl paired-devices
//
//
// sudo stty -F /dev/rfcomm0 cs8 9600 ignbrk -brkint -icrnl -imaxbel -opost -onlcr -isig -icanon -iexten -echo -echoe -echok -echoctl -echoke noflsh -ixon -crtscts  
//
// [251018]
// Tests result: OK
//
// Notes:
// This example is a bit worse than obd_rfcomm.c, use this second one finally.
//

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <bluetooth/bluetooth.h>
#include <bluetooth/rfcomm.h>


int main(int argc, char **argv) {

    struct sockaddr_rc addr = { 0 };
    int s, status;
    char dest[] = "10:21:3E:4A:0C:8F"; // V-LINK adapter MAC address

    // Create RFCOMM socket
    s = socket(AF_BLUETOOTH, SOCK_STREAM, BTPROTO_RFCOMM);

    // Set connection parameters (RFCOMM channel = usually 1 for OBD)
    addr.rc_family = AF_BLUETOOTH;
    addr.rc_channel = (uint8_t) 1;
    str2ba(dest, &addr.rc_bdaddr);

    // Connect to OBD adapter
    status = connect(s, (struct sockaddr *)&addr, sizeof(addr));

    if (status == 0) {
        printf("Connected to OBD adapter\n");

        // Send an OBD command (e.g., "010C\r" for RPM)
        //char cmd[] = "010C\r";
        char cmd[] = "AT I\r";
        write(s, cmd, sizeof(cmd));

        usleep(500000);  // wait 500ms, any delay is necessary, check how much
        // Read response
        char buf[1024] = { 0 };
        int bytes_read = read(s, buf, sizeof(buf));
        if (bytes_read >= 0) {
            printf("Received bytes = %d \n", bytes_read);
            printf("Response: %s\n", buf);
        } else {
            perror("Error: read failed");
        }
        
    } else {
        perror("Failed to connect");
    }

    close(s);
    
    return 0;
}

