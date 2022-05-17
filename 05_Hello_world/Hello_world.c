#include <stdio.h>
// #include <errno.h>
#include <stdlib.h>
#include <pthread.h>
// #include <sys/syscall.h>

#define NUM_THREADS 4

void *thread_hello_world(void *arg);

int main(int argc, char *argv[]) {
    
    int i, tmp;

    pthread_t thread[NUM_THREADS];
    pthread_attr_t attr;

    pthread_attr_init(&attr);
    
    // creating threads
    for (i = 0; i < NUM_THREADS; i++) {
        tmp = pthread_create(&thread[i], &attr, thread_hello_world, NULL);

        if (tmp != 0) {
            printf("Creating thread %d failed!\n", i);
            return 1;
        }
    }

    // joining threads
    for (i = 0; i < NUM_THREADS; i++) {
        tmp = pthread_join(thread[i], NULL);
        if (tmp != 0) {
            printf ("Joing thread %d failed!\n", i);
            return 1;
        }
    }
    
    return 0;
}


void *thread_hello_world(void *arg) {
    int id = pthread_self();
    
//     int id = 0;
//     errno = 0;
//     id = syscall(SYS_gettid);
//     if(0 != errno) {
//         perror("syscall(SYS_gettid) failed");
//         abort();
//     }
    
    printf("Hello wold from thread %d!\n", id );
    pthread_exit(NULL);
}
