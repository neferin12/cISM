#include "organization.h"
#ifndef CISM_FILEINTERFACE_H
#define CISM_FILEINTERFACE_H
int countlines(char *filename);
seminarArray getSeminars(const char *filename, char type);
studentArray getStudents(const char *filename, seminarArray wSeminars, seminarArray pSeminars);
#endif //CISM_FILEINTERFACE_H
