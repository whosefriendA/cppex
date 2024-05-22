#include "hash_lock.h"

#include <stdio.h>
#include <stdlib.h>

void hashInit(hash_lock_t* bucket) {
  for(int i=0;i<HASHNUM;i++){
    bucket->table[i].head=NULL;
    pthread_mutex_init(&bucket->table[i].mutex,NULL);
  }
}

int getValue(hash_lock_t* bucket, int key) {
    int hashIndex = HASH(key);
    pthread_mutex_lock(&bucket->table[hashIndex].mutex);

    Hlist node = bucket->table[hashIndex].head;
    while (node != NULL) {
        if (node->key == key) {
            int value = node->value;
            pthread_mutex_unlock(&bucket->table[hashIndex].mutex);
            return value;
        }
        node = node->next;
    }
    
    pthread_mutex_unlock(&bucket->table[hashIndex].mutex);
    return -1; 
}


void insert(hash_lock_t* bucket, int key, int value) {
    Hlist newnode = (Hlist)malloc(sizeof(Hnode));
    newnode->key = key;
    newnode->value = value;
    newnode->next = NULL;

    int hashIndex = HASH(key);
    pthread_mutex_lock(&bucket->table[hashIndex].mutex);

    Hlist cur = bucket->table[hashIndex].head;
    if (cur == NULL) {
        bucket->table[hashIndex].head = newnode;
    } else {
      while (cur->next != NULL) {
        if (cur->key == key) {
          cur->value = value; 
          pthread_mutex_unlock(&bucket->table[hashIndex].mutex);
          free(newnode); 
          return;
        }
            cur = cur->next;
        }
        cur->next = newnode;
    }

    pthread_mutex_unlock(&bucket->table[hashIndex].mutex);
}

int setKey(hash_lock_t* bucket, int key, int new_key) {
    int oldHashIndex = HASH(key);
    int newHashIndex = HASH(new_key);

    if (oldHashIndex == newHashIndex) {
        pthread_mutex_lock(&bucket->table[oldHashIndex].mutex);
    } else {
        if (oldHashIndex < newHashIndex) {
            pthread_mutex_lock(&bucket->table[oldHashIndex].mutex);
            pthread_mutex_lock(&bucket->table[newHashIndex].mutex);
        } else {
            pthread_mutex_lock(&bucket->table[newHashIndex].mutex);
            pthread_mutex_lock(&bucket->table[oldHashIndex].mutex);
        }
    }
    Hlist prev = NULL;
    Hlist node = bucket->table[oldHashIndex].head;
    while (node != NULL) {
        if (node->key == key) {
          if (prev == NULL) {
            bucket->table[oldHashIndex].head = node->next;
          } else {
            prev->next = node->next;
          }
          node->key = new_key;
          node->next = bucket->table[newHashIndex].head;
          bucket->table[newHashIndex].head = node;
          if (oldHashIndex != newHashIndex) {
             pthread_mutex_unlock(&bucket->table[newHashIndex].mutex);
          }
          pthread_mutex_unlock(&bucket->table[oldHashIndex].mutex);
          return 0;
        }
        prev = node;
        node = node->next;
    }
    if (oldHashIndex != newHashIndex) {
        pthread_mutex_unlock(&bucket->table[newHashIndex].mutex);
    }
    pthread_mutex_unlock(&bucket->table[oldHashIndex].mutex);
    return -1; 
}

