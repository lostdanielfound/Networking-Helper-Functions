# Networking-Helper-Functions
The following are functions that I've created to test my knowledge of C. 

'''{c}
void get_broadcast_address(char *ip_addr, char mask, char *output_buffer);
'''

'''{c}
unsigned int get_ip_integeral_equivalent(char *ip_adderss);
'''

'''{c}
get_abcd_ip_format(unsigned int ip_address, char *output_buffer);
'''

'''{c}
get_network_id(char *ip_addr, char mask, char *output_buffer);
'''

'''{c}
unsigned int get_subnet_cardinality(char mask);
'''

'''{c}
check_ip_subnet_membership(char *network_id, char mask, char *check_ip);
'''
