#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define NUM_THREADS 8
#define SUMMATION_NUMBER 12345
pthread_mutex_t mutex;

void *thread_summ(int* rank);

int main(int argc, char** argv) {
    
    // Summation range
    int summ = 0 ;
    
    int i, tmp;

    pthread_t thread[NUM_THREADS];
    pthread_attr_t attr;

    pthread_attr_init(&attr);
    
    int rank[NUM_THREADS];
    // creating threads
    for (i = 0; i < NUM_THREADS - 1; i++) {
        rank[i] = i + 1;
        tmp = pthread_create(&thread[i], &attr, thread_summ, &(rank[i]));

        if (tmp != 0) {
            printf("Creating thread %d failed!\n", i);
            return 1;
        }
        
    }
    
    // joining threads
    for (i = 0; i < NUM_THREADS - 1; i++) {
        int *data ;
        pthread_join(thread[i], (void**)&data);
        summ += *data;
        free(data);
    }
    
    printf("Sum of numbers from 1 to %i = %i\n", SUMMATION_NUMBER, summ);
    
    pthread_mutex_destroy(&mutex);
    return 0;
}

void *thread_summ(int *rank) {
    int *summ = malloc(sizeof(int));
    // divide the range from 1 to SUMMATION_NUMBER into NUM_THREADS - 1 parts
    if (*rank ==  NUM_THREADS - 1){ // last rank gets the range modulo
        for (int i = (*rank - 1) * SUMMATION_NUMBER / (NUM_THREADS - 1) + 1; i <= SUMMATION_NUMBER; ++i) {
            pthread_mutex_lock(&mutex);
            *summ += i;
            pthread_mutex_unlock(&mutex);
        }
    } else {
        for (int i = (*rank - 1) * SUMMATION_NUMBER / (NUM_THREADS - 1) + 1; 
             i <= *rank * SUMMATION_NUMBER / (NUM_THREADS - 1); ++i) {
            pthread_mutex_lock(&mutex);
            *summ += i;
            pthread_mutex_unlock(&mutex);
        }
    }
 //   printf ("rank = %d\t summ = %d\n", *rank, *summ);
    pthread_exit((void*)summ);
}
