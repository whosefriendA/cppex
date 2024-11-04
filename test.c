#include<stdio.h>
int main(){
    int a[]={1,2,3};
    int* c=a;
    int *b=a+1;
    printf("%p %p %p %d %d %d",a,b,c,c-a,c-b,b-c);
}