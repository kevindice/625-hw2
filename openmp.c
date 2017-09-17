#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <unistd.h>
#include <omp.h>


#define NUM_ITER 1000000000

// timing and info
struct timeval t1, t2;
double elapsedTime;
char hostname[1024];

int i, num_threads_requested;
double st = 1.0/NUM_ITER;
double sum = 0.0;
double x = 0.0;


void print_results()
{
    printf("DATA\t%s\t%d\t%f\t%f\tomp\n", hostname, num_threads_requested, elapsedTime, sum);
}

int main(int argc, char *argv[])
{
    if(argc != 2){
        printf("Usage: %s <number of threads>\n\n", argv[0]);
        exit(1);
    }

    num_threads_requested = atoi(argv[1]);


    gethostname(hostname, 1023);

    printf("DEBUG: starting on %s\n", hostname);

    gettimeofday(&t1, NULL);

    omp_set_dynamic(0);
    omp_set_num_threads(num_threads_requested);
    #pragma omp parallel for \
        default(shared) private(i,x) \
        reduction(+:sum)

        for(i = 0; i < NUM_ITER; i++)
        {
            x = (i + 0.25)*st;
            sum += 4.0/(x*x+1);
        }

    gettimeofday(&t2, NULL);

    elapsedTime = (t2.tv_sec - t1.tv_sec) * 1000.0; //sec to ms
    elapsedTime += (t2.tv_usec - t1.tv_usec) / 1000.0; // us to ms

    print_results();

    return 0;
}
