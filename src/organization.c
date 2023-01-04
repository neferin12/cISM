#include "headers/organization.h"
#include <stdlib.h>

void freeSeminars(seminarArray seminars){
    for(int i = 0; i<seminars.size;i++){
        free(seminars.seminars[i].name);
    }

    free(seminars.seminars);
}

void freeStudents(studentArray schuelers){
    for (int i = 0; i < schuelers.size; i++) {
        free(schuelers.students[i].name);
        free(schuelers.students[i].wVotes);
        free(schuelers.students[i].pVotes);
    }

    free(schuelers.students);
}
