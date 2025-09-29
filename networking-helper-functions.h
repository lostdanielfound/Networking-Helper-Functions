#ifndef HELPER_FUNC 
#define HELPER_FUNC

void get_broadcast_address(char *ip_addr, char mask, char *output_buffer);

unsigned int get_ip_integeral_equivalent(char *ip_address);

void get_abcd_ip_format(unsigned int ip_address, char *output_buffer);

void get_network_id(char *ip_addr, char mask, char *output_buffer);

unsigned int get_subnet_cardinality(char mask);

int check_ip_subnet_membership(char *network_id, char mask, char *check_ip);

unsigned int get_mask_integeral_equivalent(char mask);

#endif
