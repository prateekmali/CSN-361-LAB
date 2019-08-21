/**
* @file         Q1.c
* @brief        Q1
* @detail       Socket program to determine class, Network and Host ID of an IPv4 address
* @author       Prateek
*/

#include<stdio.h> 
#include<string.h> 

/**
* @param       Ipv4 address
* @return      Class
*/
// finding class
char findClass(char S[]) 
{ 
	// storing first octet in A[] variable 
	char A[4]; 
	int i = 0; 
	while (S[i] != '.') 
	{ 
		A[i] = S[i]; 
		i++; 
	} 
	i--; 

	// converting S[] variable into number for comparisons
	int ip = 0, j = 1; 
	while (i >= 0) 
	{ 
		ip = ip + (S[i] - '0') * j; 
		j = j * 10; 
		i--; 
	} 

	// Class A 
	if (ip >=1 && ip <= 126) 
		return 'A'; 

	// Class B 
	else if (ip >= 128 && ip <= 191) 
		return 'B'; 

	// Class C 
	else if (ip >= 192 && ip <= 223) 
		return 'C'; 

	// Class D 
	else if (ip >= 224 && ip <= 239) 
		return 'D'; 

	// Class E 
	else
		return 'E'; 
} 

/**
* @param       Ipv4 address 
* @param       Class
* @return      NULL
*/
// Function to separate Network ID as well as Host ID and print them 
void separate(char S[], char ipClass) 
{ 
	// Initializing network and host array to NULL 
	char network[12], host[12]; 
	for (int k = 0; k < 12; k++) 
		network[k] = host[k] = '\0'; 

	// for class A, only first octet is Network ID and rest are Host ID 
	if (ipClass == 'A') 
	{ 
		int i = 0, j = 0; 
		while (S[j] != '.') 
			network[i++] = S[j++]; 
		i = 0; 
		j++; 
		while (S[j] != '\0') 
			host[i++] = S[j++]; 
		printf("Network ID is %s\n", network); 
		printf("Host ID is %s\n", host); 
	} 

	// for class B, first two octet are Network ID and rest are Host ID  	
	else if (ipClass == 'B') 
	{ 
		int i = 0, j = 0, dotCount = 0; 

		// storing in network[] up to 2nd dot 
		// dotCount keeps track of number of dots passed
		while (dotCount < 2) 
		{ 
			network[i++] = S[j++]; 
			if (S[j] == '.') 
				dotCount++; 
		} 
		i = 0; 
		j++; 

		while (S[j] != '\0') 
			host[i++] = S[j++]; 

		printf("Network ID is %s\n", network); 
		printf("Host ID is %s\n", host); 
	} 

	// for class C, first three octet are Network ID and rest are Host ID 
	else if (ipClass == 'C') 
	{ 
		int i = 0, j = 0, dotCount = 0; 
        
		// storing in network[] up to 3rd dot 
		// dotCount keeps track of number of dots passed
		while (dotCount < 3) 
		{ 
			network[i++] = S[j++]; 
			if (S[j] == '.') 
				dotCount++; 
		} 

		i = 0; 
		j++; 

		while (S[j] != '\0') 
			host[i++] = S[j++]; 

		printf("Network ID is %s\n", network); 
		printf("Host ID is %s\n", host); 
	} 

	// Class D and E are not divided in Network and Host ID 
	else
		printf("In this Class, IP address is not"
		" divided into Network and Host ID\n"); 
} 


/**
* @brief        Main Function
* @return       Int
*/
// Main function 
int main() 
{ 
	char S[] = "192.226.12.11"; 
	char ipClass = findClass(S); 
	printf("Class of the given IP address is %c\n", ipClass); 
	separate(S, ipClass); 
	return 0; 
} 
