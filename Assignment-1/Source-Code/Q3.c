/**
* @file         Q3.c
* @brief        Q3
* @detail       This program is used to ping a server
* @author       Prateek
*/

#include <stdio.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <fcntl.h>
#include <unistd.h>
#include <netdb.h>
#include <string.h> 

/**
* @param       address address of the website to ping
* @return      IP address
*/

char *dns_lookup(char *addr_host, struct sockaddr_in *addr_con) 
{ 
    printf("\nResolving DNS..\n"); 
    struct hostent *host_entity; 
    char *ip=(char*)malloc(NI_MAXHOST*sizeof(char)); 
    int i; 
  
    if ((host_entity = gethostbyname(addr_host)) == NULL) 
    { 
    // No IP found
        return NULL; 
    } 
      
    //Filling up the address structure 
    strcpy(ip, inet_ntoa(*(struct in_addr *) 
                          host_entity->h_addr)); 
  
    (*addr_con).sin_family = host_entity->h_addrtype; 
    (*addr_con).sin_port = htons (0); 
    (*addr_con).sin_addr.s_addr  = *(long*)host_entity->h_addr; 
  
    return ip; 
      
} 

/**
* @brief        Main Function
* @return      Int
*/
  
int main(int argc, char *argv[]) {

    int sockfd; 
    char *ip_addr, *reverse_hostname; 
    struct sockaddr_in addr_con; 
  
    if(argc!=2) 
    { 
        printf("\nIncorrect Format %s <address>\n", argv[0]); 
        return 0; 
    } 
  
    ip_addr = dns_lookup(argv[1], &addr_con); 
    // PING google.com (172.217.167.46) 56(84) bytes of data.

    printf("\nPING '%s' IP: %s\n", argv[1], ip_addr); 
    
    // Creating Socket

    int s = socket(PF_INET, SOCK_RAW, 1);

    // Exit if the socket failed to be created
    
    if(s <= 0)
    {
        perror("Socket Error");
        exit(0);
    }


    // Create the ICMP Struct Header

    typedef struct {
        uint8_t type;
        uint8_t code;
        uint16_t chksum;
        uint32_t data;
    } icmp_hdr_t;


    //Use the newly created struct to make a variable.

    icmp_hdr_t pckt;


    // Set the appropriate values to our struct, which is our ICMP header

    pckt.type = 8;          
    pckt.code = 0;         
    pckt.chksum = 0xfff7;   
    pckt.data = 0;         


    // Creating a IP Header from a struct that exists in another library


    printf("%d\n", sizeof(pckt));
    
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = 0;
    addr.sin_addr.s_addr = inet_addr(h_addr);

 
    // Send our PING

    int actionSendResult = sendto(s, &pckt, sizeof(pckt),
                                  0, (struct sockaddr*)&addr, sizeof(addr));

 
    // Exit the app if the option failed to be set

    if(actionSendResult < 0)
    {
        perror("Ping Error");
        exit(0);
    }


    // Prepare all the necessary variable to handle the response

    unsigned int resAddressSize;
    unsigned char res[30] = "";
    struct sockaddr resAddress;

    //  Read the response from the remote host

    int ressponse = recvfrom(s, res, sizeof(res), 0, &resAddress,
                             &resAddressSize);


    //Display the response in its raw form (hex)

    if( ressponse > 0)
    {

        printf("%d bytes from %s : %s\n", ressponse, ip_addr, argv[1]);

        exit(0);
    }
    else
    {
        perror("Response Error");
        exit(0);
    }

    return 0;
}