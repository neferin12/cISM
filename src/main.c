#include <stdio.h>
#include <stdlib.h>
#include "fileInterface.h"
#include "organization.h"




int main(int argc, char* argv[]) {
    if (argc < 3) {
        fprintf(stderr, "Benutzung: ism <Wahldatei> <Seminardatei>\n");
        exit(1);
    }
    printf("Wahlen: %d\n", countlines(argv[1]));
    printf("Seminare: %d\n", countlines(argv[2]));

    return 0;
}


