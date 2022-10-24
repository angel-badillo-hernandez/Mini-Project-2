// ─── Mini Project 2 ──────────────────────────────────────────────────────────
// ─── Angel Badillo, Blake Gauna ──────────────────────────────────────────────
// Intializes a 10000 element array to i % 257 for each element, starting
// at i = 1 up to i = 10000. Then, 5 pthreads will calculate the sum of all
// elements in the array, and each thread processes from 
// idx = threadIdx * 2000 until idx < (threadIdx + 1) * 2000, where threadIdx
// ranges from 0 - 4.
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

pthread_mutex_t the_mutex;
const int NUM_THREADS = 5;
const int A_SIZE = 10000;
int A[A_SIZE];
int total = 0;

/**
 * @brief Adds 2000 elements from a portion of the array in
 *  a non-cyclic manner.
 *
 * @param tid thread id
 * @return void*
 */
void *add_elements(void *tid)
{
	int threadIdx = (long)tid;
	for (int idx = threadIdx * (A_SIZE / NUM_THREADS); 
	idx < (threadIdx + 1) * (A_SIZE / NUM_THREADS); idx++)
	{
		// get exclusive access to the "total" variable
		pthread_mutex_lock(&the_mutex);
		total += A[idx];
		// release access
		pthread_mutex_unlock(&the_mutex);
	}
	pthread_exit(NULL);
}

int main()
{
	// Array of threads
	pthread_t threads[NUM_THREADS];
	// Initialize mutex
	pthread_mutex_init(&the_mutex, NULL);
	// Status code for result of pthread_create
	int status;

	// Intialize array
	for (int i = 1; i <= A_SIZE; i++)
		A[i-1] = i % 257;

	// Creating 5 threads
	for (int i = 0; i < NUM_THREADS; i++)
	{
		status = pthread_create(&threads[i], NULL, add_elements, (void *)(long)i);
		
		// If status is not 0, error occured
		if (status != 0)
		{
			printf("Oops. pthread_create returned error code %d", status);
			exit(EXIT_FAILURE);
		}
	}

	// join threads
	for (int i = 0; i < NUM_THREADS; i++)
		pthread_join(threads[i], NULL);

	// Destroy mutex
	pthread_mutex_destroy(&the_mutex);
	
	// print the total
	printf("The sum is %d\n", total);
	return EXIT_SUCCESS;
}