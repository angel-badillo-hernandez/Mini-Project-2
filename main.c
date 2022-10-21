#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
pthread_mutex_t the_mutex;
const int NUM_THREADS = 5;
const int A_SIZE = 10000;
int A[A_SIZE];
int total = 0;
int part = 0;

void* add_elements(void* arg)
{

	// Each thread computes sum of 1/4th of array
	int thread_part = part++;

    pthread_mutex_lock(&the_mutex);
	for (int i = thread_part * (A_SIZE / 5); i < (thread_part + 1) * (A_SIZE / 5); i++)
		total += A[i];
    printf("sum is %d\n",total);
    pthread_mutex_unlock(&the_mutex);
}


// t1 = 250172
// t2 = 503736
// Result: 1277309
int main()
{
    for (int i = 0; i < A_SIZE; i++)
        A[i] = i % 257;
    

   pthread_t threads[NUM_THREADS];

	// Creating 4 threads
	for (int i = 0; i < NUM_THREADS; i++)
		pthread_create(&threads[i], NULL, add_elements, (void*)NULL);

	// joining 4 threads i.e. waiting for all 4 threads to complete
	for (int i = 0; i < NUM_THREADS; i++)
		pthread_join(threads[i], NULL);

    printf("sum is %d\n",total);
	return 0;
}