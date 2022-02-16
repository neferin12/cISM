#include <stdio.h>
#include <stdlib.h>
#include "headers/fileInterface.h"
#include "headers/organization.h"

int main(int argc, char* argv[]) {
    if (argc < 3) {
        fprintf(stderr, "Benutzung: ism <Wahldatei> <Seminardatei>\n");
        exit(1);
    }
    printf("Schüler: %d\n", countlines(argv[1]));
    printf("Seminare: %d\n", countlines(argv[2]));

    seminarArray w_seminars = getSeminars(argv[2], 'W');
    seminarArray p_seminars = getSeminars(argv[2], 'P');

    printf("W-Seminare:\n");
    for(int i = 0; i < w_seminars.size; i++){
        printf("    %d: %s\n", i, w_seminars.seminars[i].name);
    }

    printf("P-Seminare:\n");
    for(int i = 0; i < p_seminars.size; i++){
        printf("    %d: %s\n", i, p_seminars.seminars[i].name);
    }

    freeSeminars(w_seminars);
    freeSeminars(p_seminars);

    return 0;
}


