#include "errorHandling.h"
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
void dieWithErrno(char *msg){
    perror(msg);
    exit(errno);
}
void dieWithoutErrno(char *msg){
    fprintf(stderr, "%s", msg);
    exit(EXIT_FAILURE);
}

void failIfNull(void *anyPointer, char *msg){
    if (anyPointer == NULL) {
        dieWithoutErrno(msg);
    }
}