/*
____ _______ ______ _    _ __________________ _____  
 |  _ \__   __|  ____| |  | |___  /___  /  ____|  __ \ 
 | |_) | | |  | |__  | |  | |  / /   / /| |__  | |__) |
 |  _ <  | |  |  __| | |  | | / /   / / |  __| |  _  / 
 | |_) | | |  | |    | |__| |/ /__ / /__| |____| | \ \ 
 |____/  |_|  |_|     \____//_____/_____|______|_|  \_\
                                      by Michel Barnich
 Copyright © 2021 Michel Barnich
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <bluetooth/bluetooth.h>
#include <bluetooth/hci.h>
#include <bluetooth/hci_lib.h>
#include <bluetooth/rfcomm.h>
#include <bluetooth/sdp.h>
#include <bluetooth/sdp_lib.h>
#include <bluetooth/sco.h>

struct bt_device {
    char name[248];
    char addr[19];
};

struct bt_device *get_bt_device_list();
void fuzz( char address[] );

int main(int argc, char **argv) {
    
    char header[] = "  ____ _______ ______ _    _ __________________ _____  \n |  _ \\__   __|  ____| |  | |___  /___  /  ____|  __ \\ \n | |_) | | |  | |__  | |  | |  / /   / /| |__  | |__) |\n |  _ <  | |  |  __| | |  | | / /   / / |  __| |  _  / \n | |_) | | |  | |    | |__| |/ /__ / /__| |____| | \\ \\ \n |____/  |_|  |_|     \\____//_____/_____|______|_|  \\_\\\n                                      by Michel Barnich\n";
    printf("%s", header);

    printf("[+] Scanning for Bluetooth Devices... \n");

    struct bt_device *bt_device_list = get_bt_device_list();
    int bt_device_list_length = 0;
    char user_input[3];

    // determining the number of elements in bt_device_list
    while (strcmp(bt_device_list[bt_device_list_length].name, "end")) {
        bt_device_list_length++;
    }

    // have to -1 for some reason, im not good enough in C to understand what is going on :P
    bt_device_list_length--;

    // showing table of Devices
    if(bt_device_list_length > 0) {
        printf("[+] Found %d Device(s): \n", bt_device_list_length);

        printf("\n|-----|--------------------------------|---------------------|\n");
        for (int i = 0; i < bt_device_list_length ; i++) {
            printf("| %3d | %30s | %19s | \n", i+1, bt_device_list[i].name, bt_device_list[i].addr);
        }
        printf("|-----|--------------------------------|---------------------|\n\n");
        
    } else {
        printf("[!] No Devices found! \n");
        return 1;
    }

    // seting target
    printf("[i] Please enter Target Device number: ");
    fgets(user_input, 3, stdin);

    int target_device = atoi(user_input) - 1;

    printf("[+] Launching Fuzzer for \"%s\"\n", bt_device_list[target_device].name);

    fuzz(bt_device_list[target_device].addr);
    
    return 0;

}

/* 
 * stolen code from https://people.csail.mit.edu/albert/bluez-intro/c404.html
 * if you would like more explainations fo this code, the linked website explained it pretty well!
*/
struct bt_device *get_bt_device_list() {
    
    inquiry_info *ii = NULL;
    int max_rsp, num_rsp;
    int dev_id, sock, len, flags;
    int i = 0;
    char addr[19] = { 0 };
    char name[248] = { 0 };

    // Choosing Bluetooth Adapter to use (first available adapter) and opening socket
    dev_id = hci_get_route(NULL);
    sock = hci_open_dev( dev_id );
    if (dev_id < 0 || sock < 0) {
        perror("opening socket");
        exit(1);
    }

    len  = 8; // inquery time * 1.28 seconds
    max_rsp = 255; // max devices to be returned by inquiry_info
    flags = IREQ_CACHE_FLUSH; // flushing cache of previously detected devices
    ii = (inquiry_info*)malloc(max_rsp * sizeof(inquiry_info));
    
    num_rsp = hci_inquiry(dev_id, len, max_rsp, NULL, &ii, flags); // detecting devices nerby
    if( num_rsp < 0 ) perror("hci_inquiry");

    struct bt_device * bt_device_list = (struct bt_device * )malloc(num_rsp * sizeof(struct bt_device));

    for (i = 0; i < num_rsp; i++) {
        ba2str(&(ii+i)->bdaddr, addr);
        memset(name, 0, sizeof(name));

        // get user-friendly name of devices
        if (hci_read_remote_name(sock, &(ii+i)->bdaddr, sizeof(name), name, 0) < 0) {
            strcpy(name, "[unknown]");
        }
        
        strcpy(bt_device_list[i].name, name);
        strcpy(bt_device_list[i].addr, addr);

    }

    strcpy(bt_device_list[i+1].name, "end");
    strcpy(bt_device_list[i+1].addr, "end");

    free( ii );
    close( sock );
    return bt_device_list;

}

void fuzz( char dest[] ) {

    struct sockaddr_rc address = { 0 };
    int dev_id, sock, s;
    int i = 0;
    char addr[19] = { 0 };

    s = socket(AF_BLUETOOTH, SOCK_STREAM, BTPROTO_RFCOMM);
    str2ba( dest, &address.rc_bdaddr );

    // Choosing Bluetooth Adapter to use (first available adapter) and opening socket
    dev_id = hci_get_route(NULL);
    sock = hci_open_dev( dev_id );
    if (dev_id < 0 || sock < 0) {
        perror("opening socket");
        exit(1);
    }

    while(1) {

        printf("[i] Trying to send data to \"%s\"", dest);
        write(s, "a", 6);
        
    }


    return;
}