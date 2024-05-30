#include<iostream>
#include<sys/socket.h>
#include<sys/types.h>
int main(){
    int sfd;
    sfd=socket(AF_UNIX,SOCK_STREAM,0);
}