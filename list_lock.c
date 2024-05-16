#include "list_lock.h"

#include <stdio.h>
#include <stdlib.h>

void listInit(list_lock_t* list) {
   list->head=NULL;
   pthread_mutex_init(&list->mutex,NULL);
   pthread_cond_init(&list->cond,NULL);
}

void producer(list_lock_t* list, DataType value) {
  Lnode* buf=malloc(Lnode*)(sizeof(Lnode));
  buf.next=NULL;
  buf.value=value
  
  pthread_mutex_lock(&list->mutex);
  buf.next=list.head;
  list.head=buf;
  pthread_cond_signal(&list->cond);
  pthread_mutex_unlock(&list->mutex);
}

void consumer(list_lock_t* list) {
   perror("This function is not implemented");
}

int getListSize(list_lock_t* list) {
  perror("This function is not implemented");
}