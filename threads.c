#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

void* proc1(void* args1) {
    int* flag1 = (int*) args1;
    printf("Proc1 started\n");
    while (*flag1 == 0) {
        printf("1\n");
        sleep(1);
    }
    printf("Proc1 ended\n");
    pthread_exit((void*)1);
}

void* proc2(void* args2) {
    int* flag2 = (int*) args2;
    printf("Proc2 started\n");
    while (*flag2 == 0) {
        printf("2\n");
        sleep(1);
    }
    printf("Proc2 ended\n");
    pthread_exit((void*)2);
}

void main() {
    printf("Start of the main programm\n");
    pthread_t id1,id2;
    int flag1 = 0;
    int flag2 = 0;
    int end1, end2;

    int detach_state1, detach_state2;
    pthread_attr_t attr1, attr2;

    pthread_attr_init(&attr1);
    pthread_attr_init(&attr2);

    pthread_create(&id1, &attr1, proc1, &flag1);
    pthread_create(&id2, &attr2, proc2, &flag2);

    pthread_attr_setdetachstate(&attr2, PTHREAD_CREATE_DETACHED);

    pthread_attr_getdetachstate(&attr1,&detach_state1);
    pthread_attr_getdetachstate(&attr2,&detach_state2);

    printf("Default detach state for proc1: %s\n", detach_state1 == PTHREAD_CREATE_JOINABLE ? "PTHREAD_CREATE_JOINABLE" : "PTHREAD_CREATE_DETACHED"); 
    printf("Default detach state for proc2: %s\n", detach_state2 == PTHREAD_CREATE_JOINABLE ? "PTHREAD_CREATE_JOINABLE" : "PTHREAD_CREATE_DETACHED"); 

    printf("Press a button\n");
    getchar();
    printf("Button pressed\n");

    flag1 = 1;
    flag2 = 1;

    pthread_join(id1, (void**) &end1);

    printf("Exit code for proc1: %d\n", end1);
    printf("Proc2 terminated and its resources were automatically released\n");

    printf("End of the main programm");

}