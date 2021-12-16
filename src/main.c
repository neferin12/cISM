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

    seminarArray seminars = getSeminars("Seminare.csv", 'W');

    for(int i = 0; i<seminars.size;i++){
        printf("%d: %s\n", i, seminars.seminars[i].name);
    }

    freeSeminars(seminars);

    return 0;
}


