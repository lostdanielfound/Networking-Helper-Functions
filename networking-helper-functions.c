#include <stdio.h>
#include <string.h> 
#include <stdlib.h>
#include <math.h>
#include "networking-helper-functions.h"


void get_network_id(char *ip_addr, char mask, char *output_buffer) {

	// Convert ip address into integeral equivalent
	unsigned int ip_addr_int = get_ip_integeral_equivalent(ip_addr);
	
	if ((unsigned int)mask < 0 && (unsigned int)mask > 32) { 
		perror("Warning in get_network_id(): mask is out of range");
		output_buffer = NULL;
		return;	
	}	
	
	/* Convert mask into integeral equalivalent	*/
	unsigned int mask_int = get_mask_integeral_equivalent(mask);

	// Perform the logical AND operation between the integer IP address and the mask
	unsigned int network_id_int = ip_addr_int & mask_int;

    // Convert intergral format of network ID to C-string to return
	get_abcd_ip_format(network_id_int, output_buffer);
}

/* 
 * Given the ip address in "123.123.123.123" format, network mask in 
 * hexidecimal format and output buffer. This function will store the
 * broadcast address for the respective subnet in output_buffer in 
 * "123.123.123.123" format
 *
 * */
void get_broadcast_address(char *ip_addr, char mask, char *output_buffer) {
	// Obtain the network ID in integer format
	const int BUFFER_SIZE = 16;
    char network_id_str[BUFFER_SIZE];
    get_network_id(ip_addr, mask, network_id_str);
    unsigned int network_id_uint = get_ip_integeral_equivalent(network_id_str);

	// Find the complement of Mask M'
    unsigned int complement_mask_uint = !get_mask_integeral_equivalent(mask);

    // Obtain broadcast address in integeral format by perform OR operation
    // on network ID address with mask complement. 
    unsigned int broadcast_addr_uint = network_id_uint | complement_mask_uint;
    
    // Convert the Broadcast address from Integeral form to C-String
    get_abcd_ip_format(broadcast_addr_uint, output_buffer);
}

/*
 * Given the ip address in "123.123.123.123" format, this 
 * functions converts it into the interger equivalent.
 *
 * */
unsigned int get_ip_integeral_equivalent(char *ip_address) {
	const int OCTET_AMOUNT = 4;
	unsigned int octet_array[OCTET_AMOUNT];
	unsigned int result = 0;

	// Getting the first octet in integer format
	octet_array[0] = atoi(strtok(ip_address, "."));
	for (int i = 1; i < OCTET_AMOUNT; i++) {
		octet_array[i] = atoi(strtok(NULL, ".")); // Individual Octet portion converted into integer format	
	}

	// Shift the first Octet array element 24 times and perform a logical OR with the result variable
	octet_array[0] = octet_array[0] << 24;
	result = result | octet_array[0];

	// Shift the second Octet array element 16 times.
	octet_array[1] = octet_array[1] << 16;
	result = result | octet_array[1];
	
	// Shift the third octet array element only 8 times.
	octet_array[2] = octet_array[2] << 8;
	result = result | octet_array[2];	
	
	// Finish it off by perform an Bitwise OR with the last array element
	result = result | octet_array[3];	
	
	return(result);	
}

/*
 * Given ip address in intergral format, this function will fill in the
 * output_buffer variable with C-string of the IP address in a.b.c.d format
 *
 * */
void get_abcd_ip_format(unsigned int ip_address, char *output_buffer) {
	const int OCTET_AMOUNT = 4;
	unsigned int octet_array[OCTET_AMOUNT];

	// Insert each set of 4 bytes of the ip address into a array of octet respectivly.
	octet_array[0] = ((ip_address & (0xff << 24)) >> 24);
	octet_array[1] = ((ip_address & (0xff << 16)) >> 16);
	octet_array[2] = ((ip_address & (0xff << 8)) >> 8);
	octet_array[3] = ip_address & 0xff;
	
    // Begin building c-string with IP address.
	const int STR_BUFFER = 20;	
	char octet_string[STR_BUFFER];
	for (int i = 0; i < OCTET_AMOUNT; i++) {
		sprintf(octet_string, "%u", octet_array[i]); // Converting integer to str
		output_buffer = strcat(output_buffer, octet_string);
		if (i != 3) {
			output_buffer = strcat(output_buffer, ".");	
		}
	}
}

/*
 * Given a subnet mask, this function will calculate the number of available hosts
 * that are possible excluding the network id and broadcast address
 * 
 * */
unsigned int get_subnet_cardinality(char mask) {
    unsigned cardinality; 

    if ((unsigned)mask <= 0) {
		perror("Warning in get_subnet_cardinality(): mask is less than or equal to 0");
        return 0;
    }

    switch(((unsigned)mask)) {
        case 1: cardinality = 1;
        case 2: cardinality = 2;
        default: cardinality = pow(2, (unsigned)mask) - 2; 
    }

    return cardinality;
}

/*
 * Given the network ID, subnet mask, and Ip address to check against,
 * this function will validate whether the Ip address is a member of that
 * subnet by returning 1 for valid membership and 0 for not valid membership.
 *
 * */
int check_ip_subnet_membership(char *network_id, char mask, char *check_ip) {
    unsigned mask_uint = get_mask_integeral_equivalent(mask);
    unsigned mask_complement = !mask_uint;
    unsigned network_id_uint = get_ip_integeral_equivalent(network_id);
    unsigned upper_limit = network_id_uint + mask_complement;
    unsigned check_ip_uint = get_ip_integeral_equivalent(check_ip);
    
    return check_ip_uint > network_id_uint && check_ip_uint < upper_limit ? 1 : 0; 
}

unsigned int get_mask_integeral_equivalent(char mask) {

	/* Convert mask into integeral equalivalent	Shift enough bits into the integer mask */
	unsigned int mask_int = 0;
	for (int i = 0; i < (unsigned int)mask; i++) {
		mask_int = (mask_int << 1) | 1;
	} 

	// Shift the bits into the right position of the integer
	for (int i = 0; i < (32 - (unsigned int)mask); i++) {
		mask_int = mask_int << 1;
	}

    return(mask_int);
}
