#define NUM_ITER 1000000000

int i;
double sum = 0.0;
double x = 0.0;

double st = 1.0/NUM_ITER;

int main() {
    for (i = 0; i < NUM_ITER; i++)
    {
        x = (i + 0.25)*st;
        sum += 4.0/(x*x+1);
    }

    return 0;
}

