#include<stdio.h>
#include<string.h>    //strlen
#include<sys/socket.h>
#include<arpa/inet.h> //inet_addr
#include<unistd.h>    //write
 
int main(int argc, char *argv[])
{
    int sock, client_sock, read_size;
    int a, b = 0, c;
    struct sockaddr_in server, client;
    char client_message[2000], temp;
     
    //create socket
    sock = socket(AF_INET, SOCK_STREAM, 0);

    if (sock == -1)
    {
        printf("Couldn't create socket!");
    }
    puts("\nDone! Socket created");
     
    //prepare the sockaddr_in structure
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(8888);
     
    //bind
    if(bind(sock, (struct sockaddr *)&server, sizeof(server)) < 0)
    {
        //print the error message
        perror("Error! Bind failed");
        return 1;
    }
    puts("Done! Bind succeed");
     
    //listen
    listen(sock, 3);
     
    //accept and incoming connection
    puts("Waiting for incoming connections...");
    c = sizeof(struct sockaddr_in);
     
    //accept connection from an incoming client
    client_sock = accept(sock, (struct sockaddr *)&client, (socklen_t*)&c);

    if (client_sock < 0)
    {
        perror("Error! Accept connection failed");
        return 1;
    }
    puts("Done! Connection accepted");
    
    //receive a message from client
    puts("\nClient's request (to the database):");

    while((read_size = recv(client_sock, client_message, 2000, 0)) > 0)
    {
	//output the client message
        puts(client_message);

	//Send the message back to client
        write(client_sock, "Request accepted", 100);
    }

    if(read_size == 0)
    {
        puts("\nClient disconnected\n");
        fflush(stdout);
    }
    else if(read_size == -1)
    {
        perror("recv failed");
    }
     
    return 0;
}