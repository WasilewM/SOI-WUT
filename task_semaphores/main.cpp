/**
 * @file main.cpp 
 * @author Mateusz Wasilewski
 * @version 1.0
 * @date 2021-12-14
 * 
 * @copyright Copyright (c) 2021
 * 
*/

/*
Compile program with the command presented below:
g++ -o prog main.cpp -Wall -fsanitize=thread,undefined -fsanitize=thread,undefined -lpthread -lm
Launch program with command:
./prog
*/

#include <iostream>
#include <stdlib.h>
#include <unistd.h>
#include <semaphore.h>
#include <pthread.h>
#include <queue>

#define BUFFER_SIZE 10
#define PRINT_SLEEP_TIME 1
#define P1_VALUE 0
#define P2_VALUE 1
#define WORK_TIME  (10 * PRINT_SLEEP_TIME)

using namespace std;

// init buffers
queue <int> buffer_A;
queue <int> buffer_B;
queue <int> buffer_C;

// semaphores
static sem_t mutex_A;       // mutex for buffer_A access
static sem_t mutex_B;       // mutex for buffer_B access
static sem_t mutex_C;       // mutex for buffer_C access
int mutex_pshared = 1;      // for semaphores initialization
int mutex_value = 1;        // initial value for "mutex_" semaphores

static sem_t full_A;        // semaphore that provides that the size of the buffer_A won't be exceeded 
static sem_t empty_A;       // semaphore that provides that items won't be consumed from buffer_A when it is empty  
static sem_t full_B;        // semaphore that provides that the size of the buffer_B won't be exceeded
static sem_t empty_B;       // semaphore that provides that items won't be consumed from buffer_B when it is empty
static sem_t full_C;        // semaphore that provides that the size of the buffer_C won't be exceeded
static sem_t empty_C;       // semaphore that provides that items won't be consumed from buffer_C when it is empty
int full_sem_value = 0;     // initial value for "full_" semphores

// producers threads
pthread_t p1, p2;

// consumers pthreads
pthread_t k1, k2, k3;

// thread that will close the program
pthread_t cpth;


// function handles producent p1 thread
// producet p1 has 2 buffers to operate on alternately - buffer_A and buffer_B
void* p1_thread(void* arg) {
    pthread_detach(pthread_self());

    while(true) {
        sem_wait(&empty_A);
        sem_wait(&mutex_A);

        cout << "P1: pushed to buffer_A" << endl;
        buffer_A.push(P1_VALUE);

        sleep(PRINT_SLEEP_TIME);
        sem_post(&full_A);
        sem_post(&mutex_A);

        sem_wait(&empty_B);
        sem_wait(&mutex_B);

        cout << "P1: pushed to buffer_B" << endl;
        buffer_B.push(P1_VALUE);

        sleep(PRINT_SLEEP_TIME);
        sem_post(&full_B);
        sem_post(&mutex_B);
    }

    pthread_exit(NULL);
}

// function handles producent p2 thread
// producet p2 has 2 buffers to operate on alternately - buffer_B and buffer_C
void* p2_thread(void* arg) {
    pthread_detach(pthread_self());

    while(true) {
        sem_wait(&empty_B);
        sem_wait(&mutex_B);

        cout << "P2: pushed to buffer_B" << endl;
        buffer_B.push(P2_VALUE);

        sleep(PRINT_SLEEP_TIME);
        sem_post(&full_B);
        sem_post(&mutex_B);

        sem_wait(&empty_C);
        sem_wait(&mutex_C);

        cout << "P2: pushed to buffer_C" << endl;
        buffer_C.push(P2_VALUE);

        sleep(PRINT_SLEEP_TIME);
        sem_post(&full_C);
        sem_post(&mutex_C);
    }

    pthread_exit(NULL);
}

// function handles consumer p1 thread
// producet k1 has 1 buffers to operate on - buffer_A
void* k1_thread(void* arg) {
    pthread_detach(pthread_self());

    while(true) {
        sem_wait(&full_A);
        sem_wait(&mutex_A);

        int val = buffer_A.front();
        buffer_A.pop();
        
        sem_post(&empty_A);
        sem_post(&mutex_A);

        cout << "K1: fetched " << val << " from buffer_A" << endl;
        sleep(PRINT_SLEEP_TIME);
    }

    pthread_exit(NULL);
}

// function handles consumer k2 thread
// producet k2 has 1 buffers to operate on - buffer_B
void* k2_thread(void* arg) {
    pthread_detach(pthread_self());

    while(true) {
        sem_wait(&full_B);
        sem_wait(&mutex_B);

        int val = buffer_B.front();
        buffer_B.pop();

        sem_post(&empty_B);
        sem_post(&mutex_B);

        sleep(PRINT_SLEEP_TIME);
        cout << "K2: fetched " << val << " from buffer_B" << endl;
    }

    pthread_exit(NULL);
}

// function handles consumer k3 thread
// producet k3 has 1 buffers to operate on - buffer_C
void* k3_thread(void* arg) {
    pthread_detach(pthread_self());

    while(true) {
        sem_wait(&full_C);
        sem_wait(&mutex_C);

        int val = buffer_C.front();
        buffer_C.pop();

        sem_post(&empty_C);
        sem_post(&mutex_C);

        sleep(PRINT_SLEEP_TIME);
        cout << "K3: fetched " << val << " from buffer_C" << endl;
    }

    pthread_exit(NULL);
}

// function initializes semaphores
void init_semaphores() {
    sem_init(&mutex_A, mutex_pshared, mutex_value);
    sem_init(&full_A, mutex_pshared, full_sem_value);
    sem_init(&empty_A, mutex_pshared, BUFFER_SIZE);

    sem_init(&mutex_B, mutex_pshared, mutex_value);
    sem_init(&full_B, mutex_pshared, full_sem_value);
    sem_init(&empty_B, mutex_pshared, BUFFER_SIZE);

    sem_init(&mutex_C, mutex_pshared, mutex_value);
    sem_init(&full_C, mutex_pshared, full_sem_value);
    sem_init(&empty_C, mutex_pshared, BUFFER_SIZE);

    cout << "Semaphores created" << endl;
}

// function closes semaphores
void close_semaphores() {
    sem_destroy(&mutex_A);
    sem_destroy(&full_A);
    sem_destroy(&empty_A);

    sem_destroy(&mutex_B);
    sem_destroy(&full_B);
    sem_destroy(&empty_B);

    sem_destroy(&mutex_C);
    sem_destroy(&full_C);
    sem_destroy(&empty_C);

    cout << "Semaphores closed" << endl;
}

// function closes the program
void* close_program(void* arg) {
    // get access to all buffers 
    sem_wait(&mutex_A);
    sem_wait(&mutex_B);
    sem_wait(&mutex_C);
    // call for function that closes semaphores
    close_semaphores();
    // exit the program with code 0
    exit(0);

    pthread_exit(NULL);
}

int main() {
    init_semaphores();

    // create producers
    pthread_create(&p1, NULL, &p1_thread, NULL);
    pthread_join(p1, NULL);
    pthread_create(&p2, NULL, &p2_thread, NULL);
    pthread_join(p2, NULL);

    // create consumers
    pthread_create(&k1, NULL, &k1_thread, NULL);
    pthread_join(k1, NULL);
    pthread_create(&k2, NULL, &k2_thread, NULL);
    pthread_join(k2, NULL);
    pthread_create(&k3, NULL, &k3_thread, NULL);
    pthread_join(k3, NULL);

    // close the program after 
    sleep(WORK_TIME);
    pthread_create(&cpth, NULL, &close_program, NULL);
    pthread_join(cpth, NULL);
    pthread_exit(NULL);
    
    return 0;
}