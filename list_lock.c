#include "list_lock.h"

#include <stdio.h>
#include <stdlib.h>


typedef int DataType;

typedef struct node {
    DataType value;
    struct node* next;
} LNode, *LinkList;

typedef struct {
    LinkList head;
    pthread_mutex_t mutex;
    pthread_cond_t cond;
} list_lock_t;

void listInit(list_lock_t* list) {
    list->head = NULL;
    pthread_mutex_init(&list->mutex, NULL);
    pthread_cond_init(&list->cond, NULL);
}

void producer(list_lock_t* list, DataType value) {
    LNode* newNode = (LNode*)malloc(sizeof(LNode));
    if (newNode == NULL) {
        printf("内存分配失败\n");
        return;
    }
    newNode->value = value;
    newNode->next = NULL;

    pthread_mutex_lock(&list->mutex);
    newNode->next = list->head;
    list->head = newNode;
    pthread_cond_signal(&list->cond); // 唤醒等待的消费者线程
    pthread_mutex_unlock(&list->mutex);
}

void consumer(list_lock_t* list) {
    pthread_mutex_lock(&list->mutex);
    while (list->head == NULL) {
        // 等待生产者产生数据
        pthread_cond_wait(&list->cond, &list->mutex);
    }

    LNode* toDelete = list->head;
    list->head = list->head->next;
    printf("消费者消费了一个数据：%d\n", toDelete->value);
    free(toDelete);

    pthread_mutex_unlock(&list->mutex);
}

int getListSize(list_lock_t* list) {
    int count = 0;
    pthread_mutex_lock(&list->mutex);
    LNode* current = list->head;
    while (current != NULL) {
        count++;
        current = current->next;
    }
    pthread_mutex_unlock(&list->mutex);
    return count;
}

int main() {
    list_lock_t list;
    listInit(&list);

    pthread_t producerThread, consumerThread;

    // 生产者线程
    if (pthread_create(&producerThread, NULL, (void* (*)(void*))producer, (void*)&list) != 0) {
        perror("pthread_create");
        exit(EXIT_FAILURE);
    }

    // 消费者线程
    if (pthread_create(&consumerThread, NULL, (void* (*)(void*))consumer, (void*)&list) != 0) {
        perror("pthread_create");
        exit(EXIT_FAILURE);
    }

    // 等待线程结束
    pthread_join(producerThread, NULL);
    pthread_join(consumerThread, NULL);

    pthread_mutex_destroy(&list.mutex);
    pthread_cond_destroy(&list.cond);

    return 0;
}
