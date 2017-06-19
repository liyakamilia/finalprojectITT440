#include<stdio.h> //printf
#include<string.h>    //strlen
#include<sys/socket.h>    //socket
#include<arpa/inet.h> //inet_addr
#include <fcntl.h> // for open
#include <unistd.h> // for close
#include <netdb.h>
#include <sys/types.h>

#define MAX_HOSTNAME      255
 
int main(int argc, char *argv[])
{
    int sock;
    struct sockaddr_in server;
    struct in_addr in;
    char message[1000], hostbuffer[MAX_HOSTNAME+1];
    char server_reply[2000];
    
    //create socket
    sock = socket(AF_INET, SOCK_STREAM, 0);

    if (sock == -1)
    {
        printf("\nCouldn't create socket!");
    }
    puts("\nDone! Socket created");
     
    server.sin_addr.s_addr = inet_addr("192.168.8.131");
    server.sin_family = AF_INET;
    server.sin_port = htons(8888);
 
    //connect to remote server
    if(connect(sock, (struct sockaddr *)&server, sizeof(server)) < 0)
    {
        perror("Error! Connection failed");
        return 1;
    }
    puts("Connected\n");

    //keep communicating with server
    while(1) {
        printf("Enter input (to be requested): ");
        scanf("%s", message);
        
        //send data
        if(send(sock, message, strlen(message), 0) < 0) {
            puts("Error! Send input failed");
            return 1;
        }
         
        //receive a reply from the server
        if(recv(sock, server_reply, 2000, 0) < 0)
        {
            puts("recv failed");
            break;
        }
        puts("Server's reply:");
        puts(server_reply);
    }

    close(sock);
    return 0;
}