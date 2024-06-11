
#include<iostream>
#include<sys/socket.h>
#include<sys/types.h>
#include<sys/un.h>

int main(){
    int sfd;
    sfd=socket(AF_UNIX,SOCK_STREAM,0);
    
}