
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
pthread_mutex_t the_mutex;
const int NUM_THREADS = 5;
const int A_SIZE = 10000;
int A[A_SIZE];
int total = 0;

void *add_elements(void *tid)
{
	// Each thread computes sum of 1/4th of array
	int threadIdx = (long)tid;
	for (int idx = threadIdx * (A_SIZE / NUM_THREADS); idx < (threadIdx + 1) * (A_SIZE / NUM_THREADS); idx++)
	{
		pthread_mutex_lock(&the_mutex);
		total += A[idx];
		pthread_mutex_unlock(&the_mutex);
	}
	pthread_exit(NULL);
}

// t1 = 250172
// t2 = 503736
// Result: 1277309
int main()
{
	// Array of threads
	pthread_t threads[NUM_THREADS];
	int status;

	// Intialize array to values
	for (int i = 0; i < A_SIZE; i++)
		A[i] = i % 257;

	// Creating 5 threads
	for (int i = 0; i < NUM_THREADS; i++)
	{
		status = pthread_create(&threads[i], NULL, add_elements, (void *)(intptr_t)i);
		if(status)
		{printf("Oops. pthread_create returned error code %d", status);
      	exit(EXIT_FAILURE);}
	}

	// joining all threads
	for (int i = 0; i < NUM_THREADS; i++)
		pthread_join(threads[i], NULL);

	printf("sum is %d\n", total);
	return EXIT_SUCCESS;
}