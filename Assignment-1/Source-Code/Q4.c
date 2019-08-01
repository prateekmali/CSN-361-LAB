/**
* @file         Q4.c
* @brief        Q4
* @detail       This program is for printing IP address of the computer
* @author       Prateek
*/

#include <stdlib.h>
#include <errno.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <netinet/in.h>
#include <net/if.h>
#include <unistd.h>
#include <arpa/inet.h>

void check_host_name(int hostname) { // This function returns host name for local computer
   if (hostname == -1) {
      perror("gethostname");
      exit(1);
   }
}

void check_host_entry(struct hostent * hostentry) { // Find host info from host name
   if (hostentry == NULL) {
      perror("gethostbyname");
      exit(1);
   }
} 

/**
* @brief        Main Function
* @return      Int
*/
int main() {

   int n;
   struct ifreq ifr;
   char array[] = "enp3s0";
   char host[256];
   struct hostent *host_entry;
   int hostname;

   hostname = gethostname(host, sizeof(host)); // Find the host name
   check_host_name(hostname);
   host_entry = gethostbyname(host); // Find host information
   check_host_entry(host_entry);

   n = socket(AF_INET, SOCK_DGRAM, 0);

   // Type of address to retrieve - IPv4 IP address
   ifr.ifr_addr.sa_family = AF_INET;

   // Copy the interface name in the ifreq structure
   strncpy(ifr.ifr_name , array , IFNAMSIZ - 1);

   ioctl(n, SIOCGIFADDR, &ifr);
   close(n);

   // Results
   printf("Hostname: %s\n", host);
   printf("The IP Address is = %s\n" , inet_ntoa(( (struct sockaddr_in *)&ifr.ifr_addr )->sin_addr) );

   return 0;

}