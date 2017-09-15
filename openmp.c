const int NUM_ITER = 100000000;
int i;
double sum = 0.0, x = 0.0;
double st = 1.0/((double) NUM_ITER);

for(i = 0; i < NUM_ITER; i++)
{
    x = (i + 0.25)*st;
    sum += 4.0/(x*x+1);
}
