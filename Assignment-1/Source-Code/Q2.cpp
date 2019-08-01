/**
* @file         Q2.c
* @brief        Q2
* @detail       This program is for printing the MAC address of computer
* @author       Prateek
*/

#include <iostream>
#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <net/if.h>
#include <unistd.h>

using namespace std;

/**
* @brief        Main Function
* @return       Int
*/

int main()
{
	unsigned char uc_Mac[32]={0};

	int fd;
	
	struct ifreq ifr;
	char *iface = "enp1s0";
	char *mac;
	
	fd = socket(AF_INET, SOCK_DGRAM, 0);

	ifr.ifr_addr.sa_family = AF_INET;
	strncpy((char *)ifr.ifr_name , (const char *)iface , IFNAMSIZ-1);

	ioctl(fd, SIOCGIFHWADDR, &ifr);

	close(fd);

	 printf("> Successfully received Local MAC Address : %02x:%02x:%02x:%02x:%02x:%02x\n",
	  (unsigned char) ifr.ifr_hwaddr.sa_data[0],
	  (unsigned char) ifr.ifr_hwaddr.sa_data[1],
	  (unsigned char) ifr.ifr_hwaddr.sa_data[2],
	  (unsigned char) ifr.ifr_hwaddr.sa_data[3],
	  (unsigned char) ifr.ifr_hwaddr.sa_data[4],
	  (unsigned char) ifr.ifr_hwaddr.sa_data[5]);
	
	return 0;
}