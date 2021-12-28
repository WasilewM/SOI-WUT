/**
 * @file main.cpp 
 * @author Mateusz Wasilewski
 * @version 1.1
 * @date 2021-12-28
 * 
 * @copyright Copyright (c) 2021
 * 
*/

#include <iostream>
#include <stdlib.h>
#include <unistd.h>
#include <semaphore.h>
#include <pthread.h>
#include "smartbuffer.h"

#define BUFFER_SIZE 10
#define PRINT_SLEEP_TIME 1
#define P1_VALUE 0
#define P2_VALUE 1
#define WORK_TIME  (30 * PRINT_SLEEP_TIME)

using namespace std;

// SmartBuffers
SmartBuffer smartbuffer_A(BUFFER_SIZE);
SmartBuffer smartbuffer_B(BUFFER_SIZE);
SmartBuffer smartbuffer_C(BUFFER_SIZE);

// producers threads
pthread_t p1, p2;

// consumers pthreads
pthread_t k1, k2, k3;

// thread that will close the program
pthread_t cpth;


// function handles producent p1 thread
// producet p1 has 2 buffers to operate on alternately -
// smartbuffer_A and smartbuffer_B
void* p1_thread(void* arg) {
    pthread_detach(pthread_self());

    while(true) {
        smartbuffer_A.addItemToBuffer(P1_VALUE);
        cout << "P1 added item " << P1_VALUE << " to smartbuffer_A" << endl;
        sleep(PRINT_SLEEP_TIME);

        smartbuffer_B.addItemToBuffer(P1_VALUE);
        cout << "P1 added item " << P1_VALUE << " to smartbuffer_B" << endl;
        sleep(PRINT_SLEEP_TIME);
    }

    pthread_exit(NULL);
}

// function handles producent p2 thread
// producet p2 has 2 buffers to operate on alternately -
// smartbuffer_B and smartbuffer_C
void* p2_thread(void* arg) {
    pthread_detach(pthread_self());

    while(true) {
        smartbuffer_B.addItemToBuffer(P2_VALUE);
        cout << "P2 added item " << P2_VALUE << " to smartbuffer_B" << endl;
        sleep(PRINT_SLEEP_TIME);

        smartbuffer_C.addItemToBuffer(P2_VALUE);
        cout << "P2 added item " << P2_VALUE << " to smartbuffer_C" << endl;
        sleep(PRINT_SLEEP_TIME);
    }

    pthread_exit(NULL);
}

// function handles consumer k1 thread
// producet k1 has 1 buffer to operate on - smartbuffer_A
void* k1_thread(void* arg) {
    pthread_detach(pthread_self());

    while(true) {
        int consumed_item = smartbuffer_A.removeItemFromBuffer();
        cout << "K1 consumed item " << consumed_item << " from smartbuffer_A" << endl;
        sleep(PRINT_SLEEP_TIME);
    }

    pthread_exit(NULL);
}

// function handles consumer k2 thread
// producet k2 has 1 buffer to operate on - smartbuffer_B
void* k2_thread(void* arg) {
    pthread_detach(pthread_self());

    while(true) {
        int consumed_item = smartbuffer_B.removeItemFromBuffer();
        cout << "K2 consumed item " << consumed_item << " from smartbuffer_B" << endl;
        sleep(PRINT_SLEEP_TIME);
    }

    pthread_exit(NULL);
}

// function handles consumer k3 thread
// producet k3 has 1 buffer to operate on - smartbuffer_C
void* k3_thread(void* arg) {
    pthread_detach(pthread_self());

    while(true) {
        int consumed_item = smartbuffer_C.removeItemFromBuffer();
        cout << "K3 consumed item " << consumed_item << " from smartbuffer_C" << endl;
        sleep(PRINT_SLEEP_TIME);
    }

    pthread_exit(NULL);
}

// function closes the program
void* close_program(void* arg) {
    smartbuffer_A.enter();
    smartbuffer_B.enter();
    smartbuffer_C.enter();
    cout << "Bocked access to all critical sections." << endl;
    cout << "Closing the program ..." << endl;

    // exit the program with code 0
    exit(0);

    pthread_exit(NULL);
}

int main() {
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