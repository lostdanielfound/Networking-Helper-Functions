#include <stdio.h>
#include <stdlib.h>
#include "networking-helper-functions.h"
#define MAX_BUFFER 16

/* 
void get_broadcast_address(char *ip_addr, char mask, char *output_buffer);

unsigned int get_ip_integeral_equivalent(char *ip_address);

void get_abcd_ip_format(unsigned int ip_address, char *output_buffer);

void get_network_id(char *ip_addr, char mask, char *output_buffer);

unsigned int get_subnet_cardinality(char mask);

int check_ip_subnet_membership(char *network_id, char mask, char *check_ip);
*/

int main() {
    
    // Setting up pretesting variables
    char IP_address[][MAX_BUFFER] = {"192.168.0.2", "164.281.32.3", "10.10.10.0", "172.168.0.1", "255.32.0.1"};
    char mask[] = {24, 16, 8, 6, 30};


    // Testing get_broadcast_address()
    for (int i = 0; i < 5; i++) {
        char *output_buffer = (char*)malloc(MAX_BUFFER * sizeof(char));
        if (output_buffer == NULL) {
            perror("Failed to allocate memory\n");
            return(-1);
        }

        get_broadcast_address(IP_address[i], mask[i], output_buffer);
        printf("%d. IP address = %s, subnet mask = %d, Broadcast Address = %s", i, IP_address[i], (unsigned)mask[i], output_buffer);

        free(output_buffer);

    }


	return(0);
}
