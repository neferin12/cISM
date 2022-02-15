#include "headers/organization.h"
#include <stdlib.h>

void freeSeminars(seminarArray seminars){
    for(int i = 0; i<seminars.size;i++){
        free(seminars.seminars[i].name);
    }

    free(seminars.seminars);
}