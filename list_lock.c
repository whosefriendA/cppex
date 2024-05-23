#include "list_lock.h"

#include <stdio.h>
#include <stdlib.h>

void listInit(list_lock_t* list) {
   list->head=NULL;
   pthread_mutex_init(&list->mutex,NULL);
   pthread_cond_init(&list->cond,NULL);
}

void producer(list_lock_t* list, DataType value) {
  LNode* buf=(LNode*)malloc(sizeof(LNode));
  buf->next=NULL;
  buf->value=value;
  
  pthread_mutex_lock(&list->mutex);
  buf->next=list->head;
  list->head=buf;
  pthread_cond_signal(&list->cond);
  pthread_mutex_unlock(&list->mutex);
}

void consumer(list_lock_t* list) {
  pthread_mutex_lock(&list->mutex);
  while(list->head==NULL){
    pthread_cond_wait(&list->cond,&list->mutex);
  }
   LNode* usedvalue=list->head;
   list->head=list->head->next;
   free(usedvalue);
   pthread_mutex_unlock(&list->mutex);

}

int getListSize(list_lock_t* list) {
  pthread_mutex_lock(&list->mutex);
  int count=0;
  LNode *current=list->head;
  for(int i=0;current!=NULL;i++){
    current=current->next;
    count++;
  }
  pthread_mutex_unlock(&list->mutex);
  return count;
}