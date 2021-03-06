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

struct student {
    char *name;
    int mimiPoints;
    seminar wVotes[3];
    seminar pVotes[3];
    seminar wSeminar;
    seminar pSeminar;
};
typedef struct student student;

typedef struct studentArray{
    int size;
    student *students;
} studentArray;

void freeSeminars(seminarArray seminars);
void freeStudents(studentArray schuelers);

#endif //CISM_ORGANIZATION_H
