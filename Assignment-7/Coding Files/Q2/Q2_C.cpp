#include <bits/stdc++.h>
#include <stdio.h> 
#include <sys/socket.h> 
#include <arpa/inet.h> 
#include <unistd.h> 
#include <string.h> 
#define PORT 8000

using namespace std;

int main(int argc, char const *argv[]) 
{ 

    int dsize;
    cout << "Enter the size of the data word: ";
    cin >> dsize;
    int dword[dsize];
    for(int i=0; i<dsize; i++) cin >> dword[i];

    int r = 1;
    while(int(pow(2, r)) - 1 - r < dsize) {
        r++;
    }
    cout << "The number of redundancy bits is: " << r << endl;


    int i, j, k;
    int temp[30];
    for (i=dsize-1,j=0;i>=0;i--,j++)
    {
        temp[j]=dword[i];
    }
    for (i=0;i<dsize;i++)
    {
        dword[i]=temp[i];
    }
 
    int nrb=0;     
    int rb[8];     
 
    int l=0;     
    int df[30];     
 

    k=1;
    for(i=1,j=0;j<dsize;i++)
    {
        if(i==k)
        {
            df[i]=-1;
            k=k*2;
            nrb++;
        }
        else
        {
            df[i]=dword[j];
            j++;
        }
        l++;
    }
 
    int i1,i2,i3,i4,i5,i6,i7;
    int a1[4],a2[4];
     
    i5=0;
 
    for(i1=1;i1<=l;i1++)
    {
        if(df[i1]==-1)
        {

            i4 = -1;             
            i7=i1;
            while (i7>0)
            {
                i4++;
                if(i7==1)
                {
                    break;
                }
                else
                {
                    i7=i7/2;
                }
            }
 
            i3=0;
 
            for(i2=1;i2<=l;i2++)
            {
                for(i6=0;i6<4;i6++)
                {
                    a1[i6]=-1;
                }
 
                i7=i2;
                i6=0;
                while(i7>0)
                {
                    if(i7==1)
                    {
                        a1[i6]=1;
                        break;
                    }
                    else if(i7==0)
                    {
                        a1[i6]=0;
                    }
                    else
                    {
                        a1[i6]=i7%2;
                        i7=i7/2;
                    }
                    i6++;
                }
                 
                if(a1[i4]==1)
                {
                    if(df[i2]==1)
                    {
                        i3++;
                    }
                }
                 
            }
 
            if(i3%2==0)
            {
                df[i1]=0;
                rb[i5]=0;
            }
            else
            {
                df[i1]=1;
                rb[i5]=1;
            }
            i5++;
        }
     
    }
 
    cout << "The encoded code word is: ";
    for(i=l; i>0; i--) cout << df[i] << " ";
    cout << endl;

    int err_size;
    cout << "Enter the number of errors ( we can correct only one error ): ";
    cin >> err_size;
    for(i=0; i<err_size; i++) {
        cout << "Enter the location of the erroneous bit: ";
        int loc;
        cin >> loc;
        cout << "Flipping the "  << loc << " bit" << endl;
        df[loc] = (df[loc]==0)? 1:0;
        for(j=l; j>0; j--) cout << df[j] << " ";
        cout << endl;
    } 

    string cword = "";
    for(i=l; i>0; i--) cword += char(df[i] + int('0'));
    cword += "\n";

    int sock = 0, 
    valread;
    struct sockaddr_in serv_addr; 
    char buffer[1024] = {0}; 
    sock = socket(AF_INET, SOCK_STREAM, 0); 
    if(sock < 0) 
    { 
        cout << "Unable to create a socket" << endl;
        exit(1);
    } 
   
    serv_addr.sin_family = AF_INET; 
    serv_addr.sin_port = htons(PORT);
       
    if(inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr)<=0)  
    { 
        cout << "Invalid address" << endl;
        exit(1);
    } 
    
    int connect_status = connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr));
    if (connect_status < 0) 
    { 
        cout << "Connection failed" << endl;
        exit(1);
    } 

    cout << "Client : Sending the code word\n";
    send(sock , cword.c_str() , cword.size(), 0 ); 

    valread = read(sock , buffer, 1024); 
    if(valread < 0) {
        cout << "read error" << endl;
        exit(1);
    }

    cout << "Message from server : " << buffer << endl;
    return 0; 
} 