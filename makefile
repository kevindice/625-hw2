all: serial pthreads openmp

serial: serial.c
	cc serial.c -o serial

pthreads: pthreads.c
	cc pthreads.c -o pthreads

openmp: openmp.c
	cc openmp.c -o openmp