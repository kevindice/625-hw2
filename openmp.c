#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <unistd.h>

#define NUM_ITER 1000000000

// timing and info
struct timeval t1, t2;
double elapsedTime;
char hostname[1024];

int i;
double sum = 0.0;
double x = 0.0;
double st = 1.0/NUM_ITER;

void eulers_method()
{
    for (i = 0; i < NUM_ITER; i++)
    {
        x = (i + 0.25)*st;
        sum += 4.0/(x*x+1);
    }
}

void print_results()
{
    printf("DATA\t%s\t%f\t%f\n", hostname, elapsedTime, sum);
}

int main(int argc, char *argv[])
{
    gethostname(hostname, 1023);

    printf("DEBUG: starting on %s\n", hostname);

    gettimeofday(&t1, NULL);

    eulers_method();

    gettimeofday(&t2, NULL);

    elapsedTime = (t2.tv_sec - t1.tv_sec) * 1000.0; //sec to ms
    elapsedTime += (t2.tv_usec - t1.tv_usec) / 1000.0; // us to ms

    print_results();

    return 0;
}
