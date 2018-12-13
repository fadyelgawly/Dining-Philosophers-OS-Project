#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>
#include <unistd.h>
#include <string.h>
#include <time.h>


pthread_t           philosophers[5];
pthread_attr_t      attributes[5];
pthread_mutex_t     chopsticks[5];

void *philosopher(int i) {
    while (1) {
        
        int sleepTime = rand() % 3 + 1;
        printf("philosopher %d will think for %d seconds\n", i, sleepTime);
        sleep(sleepTime);
        
        int first  = (i + 1) % 5;
        int second = (i + 5) % 5;
        
        if ((i % 2) == 0) {
            int temp = first;
            first = second;
            second = temp;
        }
        
        printf("philosopher %d is waiting to pick up his first chopstick%d\n", i, first);
        pthread_mutex_lock(&chopsticks[first]);
        printf("philosopher %d picked up chopstick%d\n", i, first);
        printf("philosopher %d is waiting to pick up his second chopstick%d\n", i, second);
        pthread_mutex_lock(&chopsticks[second]);
        printf("philosopher %d picked up chopstick%d\n", i, second);
        
        sleepTime = rand() % 3 + 1;
        printf("philosopher %d will eat for %d seconds\n", i, sleepTime);
        sleep(sleepTime);
        
        printf("philosopher %d will will put down her chopsticks\n", i);
        pthread_mutex_unlock(&chopsticks[(i + 1) % 5]);
        pthread_mutex_unlock(&chopsticks[(i + 5) % 5]);
        
    }
}

int main() {
    int i;
    srand(time(NULL));
    for (i = 0; i < 5; ++i) {
        pthread_mutex_init(&chopsticks[i], NULL);
    }
    
    for (i = 0; i < 5; ++i) {
        pthread_attr_init(&attributes[i]);
    }
    
    for (i = 0; i < 5; ++i) {
        pthread_create(&philosophers[i], &attributes[i], philosopher,i);
    }
    
    for (i = 0; i < 5; ++i) {
        pthread_join(philosophers[i], NULL);
    }
    return 0;
}
