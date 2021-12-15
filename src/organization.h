#ifndef CISM_ORGANIZATION_H
#define CISM_ORGANIZATION_H
struct seminar {
    char *name;
    char seminarType;
    int size;
    int members;
};
typedef struct seminar seminar;

typedef struct seminarArray{
    int size;
    seminar *seminars;
} seminarArray;

struct schueler {
    char *name;
    int mimiPoints;
    seminar wVotes[3];
    seminar pVotes[3];
    seminar wSeminar;
    seminar pSeminar;
};
typedef struct schueler schueler;

#endif //CISM_ORGANIZATION_H
