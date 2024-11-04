// // 线程函数，打印一条消息
// void threadFunction() {
//     std::cout << "Hello from thread!\n";
// }

// int main() {
//     // 创建一个新线程，并将 threadFunction 作为线程函数
//     std::thread myThread(threadFunction);

//     // 主线程继续执行自己的任务
//     std::cout << "Hello from main!\n";

//     // 等待新线程执行结束
//     myThread.join();

//     return 0;
// }
// class task{
//     task(const int age,std::string& name ): age_(age),name_(name){}
// }
// sem_t semaphore_;
// sem_init(&semaphore_,0,1);
// sem_wait(&semaphore_);
// sem_post(&semaphore_);
// sem_destory(&semaphore);
// int main(){
//     fs::path directory=".";
//     std::cout<<directory.filename();
// }

// typedef struct {
//   int amount;
//   pthread_mutex_t mutex;
// }lock_t;

// void amountInit(lock_t* account);
// void Income(lock_t* account, int amount);
// void Expend(lock_t* account, int amount);

// void amountInit(lock_t* Account) {
//   pthread_mutex_init(&Account->mutex,NULL);
//   scanf("%d",&Account->amount);  
// }

// void Income(lock_t* Account, int amount) {
//   pthread_mutex_lock(&Account->mutex);
//   Account->amount+=amount;
//   pthread_mutex_unlock(&Account->mutex);
// }

// void Expend(lock_t* Account, int amount) {
//   pthread_mutex_lock(&Account->mutex);
//   Account->amount-=amount;
//   pthread_mutex_unlock(&Account->mutex);
// }

// int main(){
//     lock_t* Account = (lock_t*)malloc(sizeof(lock_t));
//     amountInit(Account);
//     Income(Account,10);
//     Expend(Account,20);
//     printf("%d",Account->amount);
// }

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
    pthread_cond_signal(&list->cond); 
    pthread_mutex_unlock(&list->mutex);
}

void consumer(list_lock_t* list) {
    pthread_mutex_lock(&list->mutex);
    while (list->head == NULL) {
        pthread_cond_wait(&list->cond, &list->mutex);
    }
    
    LNode* toDelete = list->head;
    list->head = list->head->next;
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
