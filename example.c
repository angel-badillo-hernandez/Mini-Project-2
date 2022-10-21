#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

const int NUM_THREADS = 10;


void *print_hello_world(void *tid) {
  // This function prints the thread's identifier and then exits.
  printf("Hello World. Greetings from thread %d\n", tid);
  pthread_exit(NULL);
}

int main(void) {
  // The main program creates 10 threads and then exits.
  pthread_t threads[NUM_THREADS];
  int status, i;

  for (i = 0; i < NUM_THREADS; i++) {
    printf("Main here. Creating thread %d\n", i);
    status = pthread_create(&threads[i], NULL, print_hello_world, (void*)i);

    if(status != 0)
    {
      printf("Oops. pthread_create returned error code %d", status);
      exit(-1);
    }
    
  }

  return EXIT_SUCCESS;
}