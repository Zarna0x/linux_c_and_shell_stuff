#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>


int main (int argc,char *argv[]) {
    char *hostname = "google.com";
    char ip[100];
    struct hostent *he;
    struct in_addr **addr_list;
    int i;

    if ( (he = gethostbyname( hostname ) ) == NULL)
    {
        //gethostbyname failed
        herror("gethostbyname");
        exit(1);
    }

    //Cast the h_addr_list to in_addr , since h_addr_list also has the ip address in long format only
    addr_list = (struct in_addr **)he->h_addr_list;

    //printf("%d %d %d",*addr_list,*&*addr_list,**addr_list);

      for(i = 0; addr_list[i] != NULL; i++)
    {
        //Return the first one;
        strcpy(ip , inet_ntoa(*addr_list[i]) );
    }

    printf("ip is %s",ip);
  return 0;
}
