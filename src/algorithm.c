#include "headers/algorithm.h"
#include "headers/errorHandling.h"
#include <stdlib.h>
#include <sys/time.h>

static void shuffle(student *array, int n) {
    struct timeval tv;
    gettimeofday(&tv, NULL);
    long usec = tv.tv_usec;
    srand48(usec);

    if (n > 1) {
        int i;
        for (i = n - 1; i > 0; i--) {
            size_t j = (unsigned int) (drand48() * (i + 1));
            student t = array[j];
            array[j] = array[i];
            array[i] = t;
        }
    }
}

static studentArray copyStudents(const studentArray students) {
    student *lStudents = malloc(sizeof(student) * students.size);
    failIfNull(lStudents, "could not create copy of lStudents (malloc)");
    for (int i = 0; i < students.size; i++) {
        student *h = &students.students[i];
        student t = {.mimiPoints = 0, .name=h->name, .pSeminar=NULL, .wSeminar = NULL, .pVotes = h->pVotes, .wVotes = h->wVotes};
        lStudents[i] = t;
    }
    studentArray ret = {.size = students.size, .students = lStudents};
    return ret;
}

studentArray runAlgorithm(const studentArray students, const seminarArray w_seminars, const seminarArray p_seminars) {
    shuffle(students.students, students.size);
    studentArray cStudents = copyStudents(students);
    return cStudents;
}
