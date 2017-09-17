#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <unistd.h>

#define NUM_ITER 1000000000
int num_threads;

// timing and info
struct timeval t1, t2;
double elapsedTime;
char hostname[1024];

// pthread stuff
int thread_counter = 0;
pthread_mutex_t mutexsum;
pthread_mutex_t thread_counter_lock;
pthread_t *thread;

// Global vars
double sum = 0.0;
double st = 1.0/NUM_ITER;

int new_thread_id() {
    int rv;
    pthread_mutex_lock(&thread_counter_lock);
    rv = thread_counter++;
    pthread_mutex_unlock(&thread_counter_lock);
    return rv;
}

void *eulers_method(void *tid)
{
    int i, start, *mytid, end;
    double x = 0.0;
    double local_sum = 0.0;
    int blockid = new_thread_id();

    start = blockid * (NUM_ITER/num_threads);
    end = (blockid + 1) * (NUM_ITER/num_threads);
    if(blockid == num_threads - 1) end = NUM_ITER;

    printf("My thread id is %d, and I'm working on %d thru %d\n", blockid, start, end);

    for (i = start; i < end; i++)
    {
        x = (i + 0.25)*st;
        local_sum += 4.0/(x*x+1);
        if(!(i%100000000)) printf("Prog\tThread %d\tIteration %d\n", blockid, i);
    }

    pthread_mutex_lock(&mutexsum);
    sum += local_sum;
    pthread_mutex_unlock(&mutexsum);
    pthread_exit(NULL);
}

void print_results()
{
    printf("DATA\t%s\t%f\t%f\n", hostname, elapsedTime, sum);
}

int main(int argc, char *argv[])
{
    if(argc != 2){
        printf("Usage: %s <number of threads>\n", argv[0]);
        exit(1);
    }

    int i;
    num_threads = atoi(argv[1]);

    thread = malloc(num_threads * sizeof(pthread_t));
    pthread_mutex_init(&mutexsum, NULL);
    pthread_mutex_init(&thread_counter_lock, NULL);

    gethostname(hostname, 1023);
    printf("DEBUG: starting on %s\n", hostname);

    gettimeofday(&t1, NULL);

    for(i = 0; i < num_threads; i++)
    {
        if(pthread_create(&thread[i], NULL, eulers_method, NULL))
            fprintf(stderr, "Thread creation failed on %s for thread %d", hostname, i);
    }

    for(i = 0; i < num_threads; i++)
    {
        if(pthread_join(thread[i], NULL))
            fprintf(stderr, "Thread joining failed on %s for thread %d", hostname, i);
    }

    gettimeofday(&t2, NULL);

    elapsedTime = (t2.tv_sec - t1.tv_sec) * 1000.0; //sec to ms
    elapsedTime += (t2.tv_usec - t1.tv_usec) / 1000.0; // us to ms

    print_results();

    pthread_mutex_destroy(&mutexsum);
    pthread_mutex_destroy(&thread_counter_lock);
    free(thread);

    pthread_exit(NULL);
}
