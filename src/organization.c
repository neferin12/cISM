#include "organization.h"
#include <stdio.h>

struct seminar {
    char *name;
    int seminarType;
    int size;
    int members;
};

struct schueler {
    char *name;
    int mimiPoints;
    struct seminar *wVotes;
    struct seminar *pVotes;
    struct seminar wSeminar;
    struct seminar pSeminar;
};