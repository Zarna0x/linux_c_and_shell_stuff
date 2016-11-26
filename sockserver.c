#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <stdlib.h>
#include <arpa/inet.h>
int main () {
  int sock;
  struct sockaddr_in server,client;

  sock = socket(AF_INET,SOCK_STREAM,0);

  if (sock == -1) {
     perror("WTF error1: ");
     exit(1);
  }

  server.sin_family      = AF_INET;
  server.sin_addr.s_addr = INADDR_ANY;
  server.sin_port        = htons(8888);


  if (bind (sock,(struct sockaddr*)&server,sizeof(server)) < 0 ) {
      perror("WTF error2: ");
      exit(1);

  }

  printf("bind done\n");

  listen(sock,5);

  //Accept incoming connections

  printf("Waiting incoming connections...\n\n\n\n");

  int c = sizeof(struct sockaddr_in);
  //server socket;

  int new_sock;

  while ( new_sock = accept(sock,(struct sockaddr *)&client,(socklen_t*)&c) ) {
    puts("Connection accepted");

     char *client_ip = inet_ntoa(client.sin_addr);
     int client_port = ntohs(client.sin_port);

    printf("%s connected from port %d\n\n\n\n\n",client_ip,client_port);
    int * messg = "Hello Client, you have received your connection\n\n\n";
    write(new_sock,messg,strlen(messg));


  }

  if (new_sock<0)
    {
        perror("accept failed");
    }


  //


  return 0;
}
