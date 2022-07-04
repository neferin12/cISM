#include "headers/algorithm.h"
#include <stdlib.h>
#include <sys/time.h>

static void shuffle(student *array, int n){
    struct timeval tv;
    gettimeofday(&tv, NULL);
    long usec = tv.tv_usec;
    srand48(usec);

    if (n > 1) {
        int i;
        for (i = n - 1; i > 0; i--) {
            size_t j = (unsigned int) (drand48()*(i+1));
            student t = array[j];
            array[j] = array[i];
            array[i] = t;
        }
    }
}

studentArray runAlgorithm(studentArray students){
    shuffle(students.students, students.size);
    return students;
}