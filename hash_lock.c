#include "hash_lock.h"

#include <stdio.h>
#include <stdlib.h>

void hashInit(hash_lock_t* bucket) {
  for(int i=0;i<HASHNUM;i++){
    ///bucket->table[i].head=NULL;
    pthread_mutex_init(&bucket->table[i].mutex,NULL);
  }
}

int getValue(hash_lock_t* bucket, int key) {
  pthread_mutex_lock(&bucket->table[HASH(key)].mutex);
  if(bucket->table[HASH(key)].head.next==NULL){
    printf("%d",bucket->table[HASH(key)].head.value)
  };else{

  }
  pthread_mutex_unlock(&bucket->table[HASH(key)].mutex);
}

void insert(hash_lock_t* bucket, int key, int value) {
  perror("This function is not implemented");
}

int setKey(hash_lock_t* bucket, int key, int new_key) {
  perror("This function is not implemented");
}