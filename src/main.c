#include <stdio.h>
#include <stdlib.h>
#include "headers/fileInterface.h"
#include "headers/organization.h"
#include "headers/algorithm.h"

int main(int argc, char *argv[]) {
    if (argc < 3) {
        fprintf(stderr, "Benutzung: ism <Wahldatei> <Seminardatei>\n");
        exit(1);
    }

    GArray *w_seminars = getSeminars(argv[2], 'W');
    GArray *p_seminars = getSeminars(argv[2], 'P');

    printf("W-Seminare:\n");
    for (int i = 0; i < w_seminars->len; i++) {
        printf("    %d: %s\n", i, g_array_index(w_seminars, seminar, i).name);
    }

    printf("P-Seminare:\n");
    for (int i = 0; i < p_seminars->len; i++) {
        printf("    %d: %s\n", i, g_array_index(p_seminars, seminar, i).name);
    }

    GArray *students = getStudents(argv[1], w_seminars, p_seminars);

    printf("Schüler: %i\n", students->len);
    printf("Seminare: %d\n", p_seminars->len + w_seminars->len);

    GArray *finished = runAlgorithm(students, w_seminars, p_seminars);

    printf("---------|%i|---------\n", accumulatePoints(finished));

    for (int i = 0; i < finished->len; i++) {
        student s = g_array_index(finished, student, i);
        printf("(%i) %s, %i, (W: %s | P: %s)\n", i + 1, s.name, s.mimiPoints, s.wSeminar.name, s.pSeminar.name);
    }

    //free(finished.students);
    freeStudents(students);
    freeSeminars(w_seminars);
    freeSeminars(p_seminars);

    return 0;
}


