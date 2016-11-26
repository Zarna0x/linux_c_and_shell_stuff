#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <pthread.h>

void* connection_handler(void*);

int main () {
  int sock, *new_sock_ptr;
  struct sockaddr_in server,client;
  char *message;

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

        message = "Hello Client , I have received your connection. And now I will assign a handler for you\n";
        write(new_sock , message , strlen(message));

       pthread_t sniffer_thread; //thread ID tid

        new_sock_ptr = malloc(1);//void pointer
       *new_sock_ptr = new_sock;
      // create thread;
     if (pthread_create(&sniffer_thread,NULL,connection_handler, (void*)new_sock_ptr ) < 0) {

            perror("could not create thread");
            return 1;
     }


  }

  if (new_sock<0)
    {
        perror("accept failed");
    }


  //


  return 0;
}


void* connection_handler(void* sock_arg) {
   // get socket descriptor
   int sock_t = *(int *)sock_arg;
   int read_size;
   char* msg, client_message[2000];

   // Send some message;
   msg = "Hello, I am your connection handler";
   write(sock_t,msg,strlen(msg));

    msg = "Its my duty to communicate with you";
    write(sock_t , msg , strlen(msg));


     // Receive message from client
    while ((read_size = recv(sock_t,client_message,2000,0)) > 0) {
           // be tutiyushi ;d

           write(sock_t,client_message,strlen(client_message));
    }

   if(read_size == 0)
    {
        puts("Client disconnected");
        fflush(stdout);
    }
    else if(read_size == -1)
    {
        perror("recv failed");
    }
    //Free the socket pointer
    free(sock_arg);
}
