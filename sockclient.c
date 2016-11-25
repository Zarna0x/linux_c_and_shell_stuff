#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>

/* Socket programming Zarna0x*/
/* client socket */
int main () {

  int sock;
  struct sockaddr_in server;

  // create socket
  sock = socket(AF_INET,SOCK_STREAM,0);

  if (sock == -1) {
     perror("Hey WTF");
  }

  server.sin_addr.s_addr = inet_addr("172.217.22.46");//unsigned long
  server.sin_family      = AF_INET; //TCP SOCKET
  server.sin_port        = htons(80);
   //puts("wtf");
  if (connect (sock,(struct sockaddr *)&server,sizeof(server)) < 0) {
     perror("Problem during connect: ");
     exit(1);
  }

   puts("Connected\n");

   // Lets send some fuckin data

   char *message ="GET / HTTP/1.1\r\n\r\n";
   char server_reply[2000];


   if ( send(sock,message,strlen(message),0) < 0 ) {
      printf("Send failed");
      exit(1);
   }

   printf("Data Sent succesfully\n\n");


   //Receive info from fuck'n server

    if (recv (sock,server_reply,2000,0) < 0 ) {
      perror("Receive response from server failed: ");
      exit(1);
    }
    //read(sock, server_reply , 2000);
     printf("reply received^^\n\n %s",server_reply);
  //printf("%d %d %d %d",sock,server.sin_addr.s_addr,server.sin_family);

    close(sock);

  return 0;
}
